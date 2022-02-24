#ifndef NO_OPEN_SSL

#include "mlxsign_signer_interface.h"

using namespace MlxSign;

MlxSignRSAViaOpenssl::MlxSignRSAViaOpenssl(string privPemFileStr): _privPemFileStr(privPemFileStr), _shaType(MlxSign::SHA512)
{}

ErrorCode MlxSignRSAViaOpenssl::Init()
{
    int keyLength = 0;
    int rc = _rsa.setPrivKeyFromFile(_privPemFileStr);
    if (rc) {
        printf("-E- Failed to set private key from file (rc = 0x%x)\n", rc);
        return MLX_SIGN_ERROR;
    }

    keyLength = _rsa.getPrivKeyLength();
    if (keyLength == 0x100) {
        _shaType = MlxSign::SHA256;
    } else if (keyLength == 0x200) {
        _shaType = MlxSign::SHA512;
    } else {
        printf("Unexpected length of key(%d bytes)", keyLength);
        return MLX_SIGN_ERROR;
    }

    return MLX_SIGN_SUCCESS;
}

ErrorCode MlxSignRSAViaOpenssl::Sign(const vector<u_int8_t>& data, vector<u_int8_t>& signature)
{
    vector<u_int8_t> sha;
    int rc;

    if (_shaType == MlxSign::SHA256) {
        MlxSignSHA256 mlxSignSHA;
        mlxSignSHA << data;
        mlxSignSHA.getDigest(sha);
    } else {
        MlxSignSHA512 mlxSignSHA;
        mlxSignSHA << data;
        mlxSignSHA.getDigest(sha);
    }

    rc = _rsa.sign(_shaType, sha, signature);
    if (rc) {
        printf("-E- Failed to encrypt the SHA (rc = 0x%x)\n", rc);
        return MLX_SIGN_ERROR;
    }

    return MLX_SIGN_SUCCESS;    
}

MlxSignRSAViaHSM::MlxSignRSAViaHSM(string opensslEngine, string opensslKeyID): 
_engineSigner(opensslEngine, opensslKeyID),
_opensslEngine(opensslEngine)
{}

ErrorCode MlxSignRSAViaHSM::Init()
{
    int rc = _engineSigner.init();
    if (rc) {
        printf("-E- Failed to initialize %s engine (rc = 0x%x)\n", _opensslEngine.c_str(), rc);
        return MLX_SIGN_ERROR;
    }
    int keySize = _engineSigner.getPrivateKeySize();
    if( keySize != KEY_SIZE_512 ) {
        printf("-E- The HSM key has to be 4096 bit!\n");
        return MLX_SIGN_ERROR;
    }
    return MLX_SIGN_SUCCESS;
}

ErrorCode MlxSignRSAViaHSM::Sign(const vector<u_int8_t>& data, vector<u_int8_t>& signature)
{
    int rc = _engineSigner.sign(data, signature);
    if (rc) {
        printf("-E- Failed to create secured FW signature (rc = 0x%x)", rc);
        return MLX_SIGN_ERROR;
    }
    return MLX_SIGN_SUCCESS;
}

#endif //ENABLE_OPENSSL