/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

// Minimal HTTP/1.1 client over libcurl, optionally over TLS. Crow ships only a
// server, so the MST client needs one of its own.
//
// The server signs its own certificate, so there is no chain worth validating:
// identity comes from the public key, checked in verify_cb() below.

#ifndef MST_CURL_CLIENT_H
#define MST_CURL_CLIENT_H

#include <curl/curl.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

namespace msthttp
{

// Order is irrelevant: the server looks parameters up by key.
using Params = std::multimap<std::string, std::string>;

// Header names are case-insensitive per RFC 7230.
struct CaseInsensitiveLess
{
    bool operator()(const std::string& a, const std::string& b) const
    {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                            [](unsigned char c1, unsigned char c2)
                                            { return std::tolower(c1) < std::tolower(c2); });
    }
};
using Headers = std::multimap<std::string, std::string, CaseInsensitiveLess>;

// Percent-encode a query/form value per RFC 3986 (unreserved chars pass
// through, everything else becomes %XX). Crow url-decodes these on the server,
// so device names such as "/dev/mst/mt4125_pciconf0" round-trip correctly.
inline std::string url_encode(const std::string& value)
{
    static const char hex[] = "0123456789ABCDEF";
    std::string out;
    out.reserve(value.size());
    for (unsigned char c : value)
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-' || c == '_' ||
            c == '.' || c == '~')
        {
            out.push_back(static_cast<char>(c));
        }
        else
        {
            out.push_back('%');
            out.push_back(hex[c >> 4]);
            out.push_back(hex[c & 0xf]);
        }
    }
    return out;
}

inline std::string build_query(const Params& params)
{
    std::string q;
    for (const auto& kv : params)
    {
        if (!q.empty())
        {
            q.push_back('&');
        }
        q += url_encode(kv.first);
        q.push_back('=');
        q += url_encode(kv.second);
    }
    return q;
}

inline std::string append_query_params(const std::string& path, const Params& params)
{
    std::string q = build_query(params);
    return q.empty() ? path : path + "?" + q;
}

struct Response
{
    int status = 0;
    std::string body;
};

// `if (!res)` on failure; `res->status` / `res->body` on success.
class Result
{
public:
    Result() = default;
    explicit Result(Response resp) : resp_(std::make_shared<Response>(std::move(resp))) {}

    explicit operator bool() const { return resp_ != nullptr; }
    const Response* operator->() const { return resp_.get(); }
    Response* operator->() { return resp_.get(); }

private:
    std::shared_ptr<Response> resp_;
};

// Decides whether the server that answered is the one the caller meant to reach.
// Runs during the handshake, before any request byte leaves, so returning false
// is what keeps a passphrase from reaching an unvouched-for server.
using PeerVerifier = std::function<bool(X509* cert)>;

// curl_slist_append returns null on failure without freeing what it was handed,
// so add() keeps the old head rather than assigning the result over it, and the
// destructor frees whatever was built on every path out of a request.
class HeaderList
{
public:
    HeaderList() = default;
    ~HeaderList() { curl_slist_free_all(list_); }

    HeaderList(const HeaderList&) = delete;
    HeaderList& operator=(const HeaderList&) = delete;

    bool add(const std::string& line)
    {
        curl_slist* appended = curl_slist_append(list_, line.c_str());
        if (appended == nullptr)
        {
            return false;
        }
        list_ = appended;
        return true;
    }

    curl_slist* get() const { return list_; }

private:
    curl_slist* list_ = nullptr;
};

class Client
{
public:
    Client(const std::string& host, int port) : host_(host), port_(port)
    {
        static std::once_flag once;
        std::call_once(once, []() { curl_global_init(CURL_GLOBAL_DEFAULT); });
        curl_ = curl_easy_init();
    }

    ~Client()
    {
        if (curl_)
        {
            curl_easy_cleanup(curl_);
        }
    }

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    // libcurl's own verification is switched off for this connection, so the
    // verifier is the only thing establishing identity. Without one there would
    // be nothing checking the peer at all: refuse up front rather than connect.
    void enable_tls(PeerVerifier verifier)
    {
        tls_ = true;
        verifier_ = std::move(verifier);
        if (!verifier_)
        {
            peer_rejected_ = true;
        }
    }

    void set_connect_timeout_ms(long ms) { connect_timeout_ms_ = ms; }
    // One budget for the whole exchange: libcurl has no separate read and write
    // deadline, so offering two would promise something it cannot do.
    void set_transfer_timeout_ms(long ms) { transfer_timeout_ms_ = ms; }
    void set_default_headers(Headers headers) { default_headers_ = std::move(headers); }

    // Status of the last response that arrived, 0 if none ever did. Lets a
    // caller tell "the server refused me" from "the server broke", which decide
    // whether retrying over another transport could possibly help.
    int last_status() const { return last_status_; }

    Result Get(const std::string& path) { return request("GET", path, "", ""); }

    Result Get(const std::string& path, const Params& params)
    {
        return request("GET", append_query_params(path, params), "", "");
    }

    Result Post(const std::string& path, const Params& params)
    {
        return request("POST", path, build_query(params), "application/x-www-form-urlencoded");
    }

    Result Post(const std::string& path, const std::string& body, const std::string& content_type)
    {
        return request("POST", path, body, content_type);
    }

private:
    // Index under which the Client is stashed on the SSL_CTX, so the verify
    // callback - which OpenSSL calls with no context of its own - can find it.
    static int client_ex_index()
    {
        static const int idx = SSL_CTX_get_ex_new_index(0, nullptr, nullptr, nullptr, nullptr);
        return idx;
    }

    // libcurl hands over the SSL_CTX before the handshake; with the OpenSSL
    // backend this is the only place a custom identity check can be installed.
    static CURLcode ssl_ctx_cb(CURL* /*curl*/, void* ssl_ctx, void* userdata)
    {
        SSL_CTX* ctx = static_cast<SSL_CTX*>(ssl_ctx);
        SSL_CTX_set_ex_data(ctx, client_ex_index(), userdata);
        // SSL_VERIFY_PEER is what makes OpenSSL call verify_cb at all. The chain
        // it walks on the way has no CA it could succeed against, which is why
        // verify_cb ignores preverify_ok and looks at the key instead.
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, &Client::verify_cb);
        return CURLE_OK;
    }

    static int verify_cb(int /*preverify_ok*/, X509_STORE_CTX* store_ctx)
    {
        // Only the leaf's key identifies the server; issuers above it are not
        // checked against anything, so they pass untouched.
        if (X509_STORE_CTX_get_error_depth(store_ctx) != 0)
        {
            return 1;
        }
        SSL* ssl = static_cast<SSL*>(X509_STORE_CTX_get_ex_data(store_ctx, SSL_get_ex_data_X509_STORE_CTX_idx()));
        X509* cert = X509_STORE_CTX_get_current_cert(store_ctx);
        if (!ssl || !cert)
        {
            return 0;
        }
        // Fail closed: reaching here without a verifier - an ex_data index that
        // could not be allocated, or an SSL_CTX that is not the one configured -
        // means nothing is left to establish identity, and libcurl's own checks
        // are off. Accepting would hand the passphrase to an unverified peer.
        Client* self = static_cast<Client*>(SSL_CTX_get_ex_data(SSL_get_SSL_CTX(ssl), client_ex_index()));
        if (!self || !self->verifier_)
        {
            return 0;
        }
        if (self->verifier_(cert))
        {
            return 1;
        }
        // Latched, so a refused server is not re-probed - and the user not
        // re-prompted - on every later request.
        self->peer_rejected_ = true;
        return 0;
    }

    static std::size_t write_cb(char* ptr, std::size_t size, std::size_t nmemb, void* userdata)
    {
        const std::size_t n = size * nmemb;
        static_cast<std::string*>(userdata)->append(ptr, n);
        return n;
    }

    Result request(const std::string& method,
                   const std::string& path,
                   const std::string& body,
                   const std::string& content_type)
    {
        if (!curl_ || peer_rejected_)
        {
            return Result();
        }

        // A POST body left configured would turn the next GET into a POST.
        // Connections and the DNS/TLS caches survive a reset, so reuse does not.
        curl_easy_reset(curl_);

        const std::string url = (tls_ ? "https://" : "http://") + host_ + ":" + std::to_string(port_) + path;
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        // Signals are how libcurl implements its own DNS timeout; installing a
        // handler is not this library's to do inside someone else's process.
        curl_easy_setopt(curl_, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(curl_, CURLOPT_CONNECTTIMEOUT_MS, connect_timeout_ms_);
        curl_easy_setopt(curl_, CURLOPT_TIMEOUT_MS, transfer_timeout_ms_);

        // A redirect would be followed to a host this client never vouched for,
        // while the trust decision stays pinned to the configured one. libcurl
        // already defaults to not following; say so, so it cannot drift.
        curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 0L);

        if (tls_)
        {
            // These are checked, unlike the options above, because between them
            // they are the whole identity check: the first two switch libcurl's
            // own verification off and the last two install what replaces it. An
            // option libcurl cannot honour - CURLE_NOT_BUILT_IN from a TLS
            // backend with no SSL_CTX hook, say - would otherwise leave the
            // handshake with neither.
            //
            // TLS 1.2 is the floor: everything below it is broken, and this link
            // carries a device's whole register space. The cast matters, the
            // option is read as a long.
            const CURLcode tls_setup[] = {
              curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L),
              curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L),
              curl_easy_setopt(curl_, CURLOPT_SSLVERSION, static_cast<long>(CURL_SSLVERSION_TLSv1_2)),
              curl_easy_setopt(curl_, CURLOPT_SSL_CTX_FUNCTION, &Client::ssl_ctx_cb),
              curl_easy_setopt(curl_, CURLOPT_SSL_CTX_DATA, this),
            };
            for (CURLcode setup_rc : tls_setup)
            {
                if (setup_rc != CURLE_OK)
                {
                    peer_rejected_ = true;
                    return Result();
                }
            }
        }

        std::string response;
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &Client::write_cb);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);

        HeaderList headers;
        for (const auto& h : default_headers_)
        {
            // A request that quietly lost its Authorization header returns 401,
            // which reads as a rejected passphrase rather than a local failure.
            if (!headers.add(h.first + ": " + h.second))
            {
                return Result();
            }
        }
        // libcurl labels a POST body form-urlencoded unless told otherwise, which
        // the server would then try to parse a raw cable page into parameters.
        if (!content_type.empty() && !headers.add("Content-Type: " + content_type))
        {
            return Result();
        }
        if (headers.get() != nullptr)
        {
            curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers.get());
        }

        if (method != "GET")
        {
            // Size first and explicit: a body may hold NULs, which libcurl would
            // otherwise cut short at the first one.
            curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE_LARGE, static_cast<curl_off_t>(body.size()));
            curl_easy_setopt(curl_, CURLOPT_COPYPOSTFIELDS, body.data());
        }

        // headers must outlive this call; ~HeaderList frees it on the way out.
        const CURLcode rc = curl_easy_perform(curl_);
        if (rc != CURLE_OK)
        {
            return Result();
        }

        long status = 0;
        curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status);
        last_status_ = static_cast<int>(status);

        Response resp;
        resp.status = last_status_;
        resp.body = std::move(response);
        return Result(std::move(resp));
    }

    CURL* curl_ = nullptr;
    std::string host_;
    int port_ = 0;
    bool tls_ = false;
    bool peer_rejected_ = false;
    PeerVerifier verifier_;
    Headers default_headers_;
    int last_status_ = 0;
    long connect_timeout_ms_ = 2000;
    long transfer_timeout_ms_ = 30000;
};

} // namespace msthttp

#endif // MST_CURL_CLIENT_H
