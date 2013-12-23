/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 */


#ifndef _OPT_PARSER_H_
#define _OPT_PARSER_H_


#include <stdlib.h>
#include <list>
#include <vector>
#include <map>
#include <string>
using namespace std;


/******************************************************/
typedef enum
{
    //Returns: 0 - OK / 1 - parsing error / 2 - OK but need to exit / 3 - some other error
    PARSE_OK = 0,
    PARSE_ERROR = 1,
    PARSE_OK_WITH_EXIT = 3,
    PARSE_ERROR_SHOW_USAGE = 4
} ParseStatus;

typedef struct option_ifc {
    string option_name;             //must be valid
    char   option_short_name;       //can be used as short option, if space than no short flag
    string option_value;            //if "" has no argument
    string description;             //will be display in usage
    bool hidden;                    //if hidden than will not be diaplayed in regular usage
    bool is_mandatory;
} option_ifc_t;

typedef vector < struct option_ifc > vec_option_t;


class CommandLineRequester {
protected:
    // members
    vec_option_t options;
    string name;
    string description;

    // methods
    string BuildOptStr(option_ifc_t &opt);

public:
    // methods
    CommandLineRequester(string req_name) : name(req_name) {}
    virtual ~CommandLineRequester() {}

    inline void AddOptions(option_ifc_t options[], int arr_size) {
        for (int i = 0; i < arr_size; ++i)
            this->options.push_back(options[i]);
    }
    inline void AddOptions(string option_name,
            char option_short_name,
            string option_value,
            string description,
	    bool hidden = false,
	    bool is_mandatory = false) {
        option_ifc_t opt;
        opt.option_name = option_name;
        opt.option_short_name = option_short_name;
        opt.option_value = option_value;
        opt.description = description;
        opt.hidden = hidden;
	opt.is_mandatory = is_mandatory;
        this->options.push_back(opt);
    }
    inline void AddDescription(string desc) { this->description = desc; }
    inline vec_option_t& GetOptions() { return this->options; }
    inline string& GetName() { return this->name; }

    string GetUsageSynopsis(bool hidden_options = false);
    string GetUsageDescription();
    string GetUsageOptions(bool hidden_options = false);

    virtual ParseStatus HandleOption(string name, string value) = 0;
};


/******************************************************/
typedef list < CommandLineRequester * > list_p_command_line_req;
typedef map < char, string > map_char_str;
typedef map < string, CommandLineRequester * > map_str_p_command_line_req;


class CommandLineParser {
private:
    // members
    list_p_command_line_req p_requesters_list;
    map_char_str short_opt_to_long_opt;
    map_str_p_command_line_req long_opt_to_req_map;

    string name;
    string last_error;
    string last_unknown_options;

    // methods
    void SetLastError(const char *fmt, ...);

public:
    // methods
    CommandLineParser(string parser_name) :
        name(parser_name), last_error(""), last_unknown_options("") {}
    ~CommandLineParser() {}

    inline const char * GetErrDesc() { return this->last_error.c_str(); }
    inline const char * GetUnknownOptions() { return this->last_unknown_options.c_str(); }

    int AddRequester(CommandLineRequester *p_req);      //if multiple option than fail

    ParseStatus ParseOptions(int argc, char **argv,
            bool to_ignore_unknown_options = false,
            list_p_command_line_req *p_ignored_requesters_list = NULL);

    string GetUsage(bool hidden_options = false);
};


#endif          /* not defined _OPT_PARSER_H_ */
