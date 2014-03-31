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


#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "my_getopt.h"
#include "cmdparser.h"


/****************************************************/
typedef vector < bool > vec_bool;


/****************************************************/
/************class CommandLineRequester**************/
/****************************************************/
/* private methods */
string CommandLineRequester::BuildOptStr(option_ifc_t &opt)
{
    string str;

    if (opt.option_short_name != ' ') {
        str += "-";
        str += opt.option_short_name;
        str += "|";
    }
    str += "--";
    str += opt.option_name;
    if (opt.option_value != "") {
        str += " ";
        str += opt.option_value;
    }
    return str;
}


/* public methods */
#define OPT_STR_LEN 40
#define OPT_DESC_LEN 40
#define PREFIX_SPACE "        "
#define PREFIX_SHORT_SPACE "    "


string CommandLineRequester::GetUsageSynopsis(bool hidden_options)
{
    string str = "";
    string curr_str = PREFIX_SPACE;

    for (vec_option_t::iterator it = this->options.begin(); it != this->options.end(); ++it) {
        if (hidden_options == false) {          //display only not hidden options
            if ((*it).hidden == true) {
                continue;
            }
        } else {                                //display only hidden options
            if ((*it).hidden == false) {
                continue;
            }
        }

        curr_str += (*it).is_mandatory ? "<" : "[";
        curr_str += this->BuildOptStr(*it);
        curr_str += (*it).is_mandatory ? ">" : "]";
        if (curr_str.size() < OPT_STR_LEN) {
            curr_str += " ";
        } else {
            str += curr_str;
            str += "\n";
            curr_str = PREFIX_SPACE;
        }
    }
    if (curr_str != PREFIX_SPACE) {
        str += curr_str;
        str += "\n";
    }

    if (str != "") {
        str = PREFIX_SHORT_SPACE + this->name + "\n" + str;
    }

    return str;
}


string CommandLineRequester::GetUsageDescription()
{
    if (this->description == "")
        return "";
    string str = this->description;

    int prev_found = 0;
    int found2 = str.find('\n', prev_found);
    int found = str.find(" ", prev_found);
    while (found != (int)string::npos) {
        if ((found2 != (int)string::npos) && (found2 < found)) {
            prev_found = found2;
        }
        if ((found - prev_found) > OPT_DESC_LEN + OPT_STR_LEN) {
            prev_found = found + 1;
            str.insert(found + 1, "\n");
        }
        found2 = str.find('\n', found + 1);
        found = str.find(" ", found + 1);
    }

    prev_found = 0;
    found = str.find('\n', prev_found);
    while (found != (int)string::npos) {
        str.insert(found + 1, PREFIX_SPACE);
        prev_found = found + strlen(PREFIX_SPACE);
        found = str.find('\n', prev_found);
    }

    str = PREFIX_SPACE + str;
    str = PREFIX_SHORT_SPACE + this->name + "\n" + str + "\n";

    return str;
}


string CommandLineRequester::GetUsageOptions(bool hidden_options)
{
    string str = "";
    string opt_str, desc_str;

    for (vec_option_t::iterator it = this->options.begin(); it != this->options.end(); ++it) {
        if (hidden_options == false) {          //display only not hidden options
            if ((*it).hidden == true) {
                continue;
            }
        } else {                                //display only hidden options
            if ((*it).hidden == false) {
                continue;
            }
        }

        opt_str = PREFIX_SPACE;
        opt_str += this->BuildOptStr(*it);
        while (opt_str.size() < OPT_STR_LEN - 2)
            opt_str += " ";
        opt_str += ": ";

        desc_str = (*it).description;
        int prev_found = 0;
        int found2 = desc_str.find('\n', prev_found);
        int found = desc_str.find(" ", prev_found);
        while (found != (int)string::npos) {
            if ((found2 != (int)string::npos) && (found2 < found)) {
                prev_found = found2;
            }
            if ((found - prev_found + 1) > OPT_DESC_LEN) {
                prev_found = found + 1;
                desc_str.insert(found + 1, "\n");
            }
            found2 = desc_str.find('\n', found + 1);
            found = desc_str.find(" ", found + 1);
        }

        prev_found = 0;
        found = desc_str.find('\n', prev_found);
        while (found != (int)string::npos) {
            for (int i = 0; i < OPT_STR_LEN; ++i)
                desc_str.insert(found + 1, " ");
            prev_found = found + OPT_STR_LEN;
            found = desc_str.find('\n', prev_found);
        }

        str += opt_str;
        str += desc_str;
        str += "\n";
    }

    if (str != "") {
        str = PREFIX_SHORT_SPACE + this->name + "\n" + str;
    }

    return str;
}


/****************************************************/
/**************class CommandLineParser***************/
/****************************************************/
/* private methods */
void CommandLineParser::SetLastError(const char *fmt, ...)
{
    char buff[1024];
    va_list args;

    memset(buff, 0, sizeof(buff));
    va_start(args, fmt);
    vsprintf(buff, fmt, args);
    va_end(args);

    this->last_error.assign(buff);
    return;
}


/* public methods */
int CommandLineParser::AddRequester(CommandLineRequester *p_req)
{
    for (vec_option_t::iterator it = p_req->GetOptions().begin();
            it != p_req->GetOptions().end(); ++it) {
        //long option must be valid
        if ((*it).option_name == "") {
            this->SetLastError("Requester \"%s\" has long option empty",
                    p_req->GetName().c_str());
            return 1;
        }

        //check if long option already exists
        map_str_p_command_line_req::iterator it2 =
                this->long_opt_to_req_map.find((*it).option_name);
        if (it2 != this->long_opt_to_req_map.end()) {
            this->SetLastError("Option \"%s\" from requester \"%s\" "   \
                    "already exists in requester \"%s\"",
                    (*it).option_name.c_str(),
                    p_req->GetName().c_str(),
                    (*it2).second->GetName().c_str());
            return 1;
        }

        //check if short option already exists
        if ((*it).option_short_name != ' ') {   //if space than no short option
            map_char_str::iterator it2 =
                    this->short_opt_to_long_opt.find((*it).option_short_name);
            if (it2 != this->short_opt_to_long_opt.end()) {
                this->SetLastError("Option \'%c\' from requester \"%s\" "   \
                        "already exists in requester \"%s\"",
                        (*it).option_short_name,
                        p_req->GetName().c_str(),
                        this->long_opt_to_req_map[(*it2).second]->GetName().c_str());
                return 1;
            }
        }
    }

    //finally add the requester
    for (vec_option_t::iterator it = p_req->GetOptions().begin();
            it != p_req->GetOptions().end(); ++it) {
        this->long_opt_to_req_map[(*it).option_name] = p_req;
        if ((*it).option_short_name != ' ') //if space than no short option
            this->short_opt_to_long_opt[(*it).option_short_name] = (*it).option_name;
    }
    this->p_requesters_list.push_back(p_req);
    return 0;
}


string CommandLineParser::GetUsage(bool hidden_options)
{
    string res;

    //name
    res = "NAME\n";
    res += PREFIX_SHORT_SPACE;
    res += this->name;
    res += "\n";

    //synopsis
    res += "SYNOPSIS\n";
    for (list_p_command_line_req::iterator it = this->p_requesters_list.begin();
            it != this->p_requesters_list.end(); ++it) {
        res += (*it)->GetUsageSynopsis(hidden_options);
    }

    //description
    if (hidden_options == false) {
        res += "DESCRIPTION\n";
        for (list_p_command_line_req::iterator it = this->p_requesters_list.begin();
                it != this->p_requesters_list.end(); ++it) {
            res += (*it)->GetUsageDescription();
        }
    }

    //options
    res += "OPTIONS\n";
    for (list_p_command_line_req::iterator it = this->p_requesters_list.begin();
            it != this->p_requesters_list.end(); ++it) {
        res += (*it)->GetUsageOptions(hidden_options);
    }
    return res;
}


ParseStatus CommandLineParser::ParseOptions(int argc, char **argv,
        bool to_ignore_unknown_options, list_p_command_line_req *p_ignored_requesters_list)
{
    char **internal_argv;
    struct option *options_arr = NULL;
    string options_str = "";
    vec_bool returned_option_types_vec;
    ParseStatus rc = PARSE_ERROR;
    unsigned num_options = 0;
    int option_type;
    int option_index = 0;
    unsigned i = 0;

    //allocate internal_argv
    internal_argv = new char *[argc];
    if (!internal_argv) {
        this->SetLastError("Fail to allocate internal argv for parsing");
        return PARSE_ERROR;
    }
    for (int j = 0; j < argc; ++j) {
    	 internal_argv[j] = NULL;
    }
    for (int j = 0; j < argc; ++j) {
        internal_argv[j] = new char[strlen(argv[j]) + 1];
        if (!internal_argv[j]) {
            this->SetLastError("Fail to allocate internal argv[%u] for parsing", j);
            rc = PARSE_ERROR;
			goto argv_err_exit;
        }
        strcpy(internal_argv[j], argv[j]);
    }

    //allocate long_options_arr
    num_options = this->long_opt_to_req_map.size();
    options_arr = new struct option[num_options + 1];
    if (!options_arr) {
        this->SetLastError("Fail to allocate long_options_arr");
        rc = PARSE_ERROR;
        goto parse_exit;
    }
    memset(options_arr, 0, sizeof(struct option)*(num_options + 1));

    /*
     * fill options array and options string with
     *  getopt_long_only() formats
     * also create vector of possible options type
     * that can be return by getopt_long_only()
     */
    i = 0;
    for (list_p_command_line_req::iterator it = this->p_requesters_list.begin();
            it != this->p_requesters_list.end(); ++it) {
        for (vec_option_t::iterator it2 = (*it)->GetOptions().begin();
                it2 != (*it)->GetOptions().end(); ++it2) {
            options_str += (*it2).option_short_name;
            options_arr[i].name = (*it2).option_name.c_str();
            if ((*it2).option_value != "") {
                options_arr[i].has_arg = 1;
                options_str += ":";
            } else {
                options_arr[i].has_arg = 0;
            }
            options_arr[i].flag = 0;
            if ((*it2).option_short_name != ' ') {
                options_arr[i].val = (*it2).option_short_name;
            } else {
                options_arr[i].val = 0;
            }

            if (returned_option_types_vec.empty() || (returned_option_types_vec.size() < (unsigned int)options_arr[i].val + 1))
                    for (unsigned j = returned_option_types_vec.size(); j < (unsigned int)options_arr[i].val + 1; ++j)
                        returned_option_types_vec.push_back(false);
            returned_option_types_vec[options_arr[i].val] = true;
            //printf("%c %d ", options_arr[i].val, options_arr[i].val);
            ++i;
        }
    }

    //finally parse all options
    if (to_ignore_unknown_options == true)
        tools_opterr = 0;
    else
        tools_opterr = 1;
    tools_optind = 0;

    ParseStatus curr_result;
    while ((option_type = tools_getopt_long_only(argc, internal_argv, options_str.c_str(),
            options_arr, &option_index)) != -1) {
        //printf("option_type=\'%c\'\n", option_type);

        string long_opt_name;
        if (option_type == 0) {
            long_opt_name = options_arr[option_index].name;
            goto do_handle_option;
        } else if (option_type == '?') {
            if (to_ignore_unknown_options == true)
                continue;
            this->SetLastError("Bad input parameter");
            goto parse_exit;
        } else if (returned_option_types_vec[option_type] == true) {
            long_opt_name = this->short_opt_to_long_opt[option_type];
            goto do_handle_option;
        } else {
            this->SetLastError("getopt_long_only() returned character code 0%o", option_type);
            goto parse_exit;
        }

do_handle_option:
        CommandLineRequester *p_req = this->long_opt_to_req_map[long_opt_name];
        bool ignore_this_req = false;
        if (p_ignored_requesters_list)
            for (list_p_command_line_req::iterator it = p_ignored_requesters_list->begin();
                    it != p_ignored_requesters_list->end(); ++it) {
                if (p_req == (*it)) {
                    ignore_this_req = true;
                    break;
                }
            }
        if (ignore_this_req == false) {
            curr_result = p_req->HandleOption(long_opt_name, (tools_optarg == NULL) ? "" : tools_optarg);
            if (curr_result) {
                rc = curr_result;
                this->SetLastError("Failed to handle option %s", long_opt_name.c_str());
                goto parse_exit;
            }
        }
        continue;
    }

    if (tools_optind < argc) {
        while (tools_optind < argc) {
            this->last_unknown_options += internal_argv[tools_optind];
            this->last_unknown_options += " ";
            ++tools_optind;
        }
        /*if (this->last_unknown_options != "")   //remove last space
            this->last_unknown_options.erase(this->last_unknown_options.end() - 1,
                    this->last_unknown_options.end());*/
        if (to_ignore_unknown_options == false) {
            string str = "Found some non-option ARGV-elements ";
            str += this->last_unknown_options;
            this->SetLastError(str.c_str());
            goto parse_exit;
        }
    }

    rc = PARSE_OK;
parse_exit:
    for (int i = 0; i < argc; ++i)
        delete [] internal_argv[i];
    delete [] internal_argv;
    delete [] options_arr;
    return rc;
argv_err_exit:
	for (int i = 0; i < argc; ++i)
        delete [] internal_argv[i];
    delete [] internal_argv;
    return rc;
}

