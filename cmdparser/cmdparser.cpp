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


/*Includes*/
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <errno.h>
#include "compatibility.h"
#include "my_getopt.h"
#include "cmdparser.h"


/*Constants*/
#define IDENT_LENGTH 4
#define PREFIX_SPACE_SIZE 8
#define LEFT_STR_MAX_LEN 45
#define RIGHT_STR_MAX_LEN 45
#define COLON_AND_SPACE_SIZE 2
#define TAB_SIZE 4


/*Declarations*/
typedef vector < bool > vec_bool;

static string CreateIndentFromInt(int ident_size);
static void FindAndReplace(string& source, string::size_type pos, string const& find, string const& replace);
static bool FindAndHandleNewLinePos(string& str, int& product_length, int& local_space_size, int& str_type_len,
                                    int& new_line_pos, string newline_and_ident, int deli_is_space);

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

string CommandLineRequester::FormatUsageStr(string str, int str_type_len, int ident_size,
                                            int is_not_description, bool is_left_side)
{
    string ident = CreateIndentFromInt(ident_size);
    string newline_and_ident = "\n" + ident;
    //replace tabs in spaces
    FindAndReplace(str, 0, "\t", CreateIndentFromInt(TAB_SIZE));
    //helper variables for formatting
    int residual = str.size();
    int initial_residual = residual;
    int product_length = 0;
    int local_space_size = is_not_description * ident_size;
    int new_line_pos = 0;
    int space_not_exists_count = 0;

    //iterate while the remained text is longer then a valid line length
    while (residual >= str_type_len + local_space_size) {
        //search for a user defined new line.
        if (FindAndHandleNewLinePos(str, product_length, local_space_size, str_type_len, new_line_pos,
                                    newline_and_ident, 0)) {
            goto next_iteration;
        }
        //if no such is found. try to find a space to break the line at it's position.
        if (FindAndHandleNewLinePos(str, product_length, local_space_size, str_type_len, new_line_pos,
                                    newline_and_ident, 1)) {
            goto next_iteration;
        }
        //if not found, break the line in a middle of a spaceless word.
        space_not_exists_count++;
        new_line_pos = local_space_size + str_type_len + product_length;
        str.insert(new_line_pos, newline_and_ident);
next_iteration:
        //update iteration variables
        local_space_size = ident_size;
        initial_residual += ident_size;
        residual = initial_residual - new_line_pos - 1 + space_not_exists_count;
        product_length = new_line_pos;
    }
    //handle the last line remained. if it is the left string - add aligned colon.
    if (is_left_side) {
        while (residual < str_type_len + ident_size) {
            str += " ";
            residual++;
        }
        str += ": ";
    }
    //Add user defined new lines in last line remained.
    FindAndReplace(str, product_length + local_space_size + 1, "\n", newline_and_ident);
    return str;
}

/* public methods */

// Add the data str1 and/or str2 to the optional help section "section_name".
// If "section_name" does not exist, don't worry, it would be created."
void CommandLineRequester::AddOptionalSectionData(string section_name, string str1, string str2)
{
    int pos;
    optional_sec_data_t sec_data;
    sec_data.name = section_name;
    sec_data.str1 = str1;
    sec_data.str2 = str2;

    for (optional_sections_t::iterator it = this->optional_sections_vec.begin();
         it != this->optional_sections_vec.end(); ++it) {
        if (it->first == section_name) {
            pos = distance(optional_sections_vec.begin(), it);
            this->optional_sections_vec[pos].second.push_back(sec_data);
            return;
        }
    }
    this->optional_sections_vec.push_back(pair < string, vector<struct optional_help_section_data > >
                                              (section_name, vector < struct optional_help_section_data >()));
    pos = optional_sections_vec.size() - 1;
    this->optional_sections_vec[pos].second.push_back(sec_data);
}


string CommandLineRequester::GetUsageSynopsis(bool hidden_options)
{
    string prefix_space = CreateIndentFromInt(PREFIX_SPACE_SIZE);
    string prefix_short_space = CreateIndentFromInt(IDENT_LENGTH);
    string curr_str = "";
    string str = prefix_space;
    int curr_line_len = PREFIX_SPACE_SIZE;
    int new_line_pos;

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
        if (curr_str.size() + curr_line_len <  RIGHT_STR_MAX_LEN + LEFT_STR_MAX_LEN) {
            if (curr_line_len > PREFIX_SPACE_SIZE) {
                str += " ";
            }
            curr_line_len += curr_str.size();
            str += curr_str;
            curr_str = "";
            continue;
        }
        while (curr_str.size() + curr_line_len >= RIGHT_STR_MAX_LEN + LEFT_STR_MAX_LEN) {
            if (curr_str.size() < RIGHT_STR_MAX_LEN + LEFT_STR_MAX_LEN) {
                str += "\n" + prefix_space + curr_str;
                curr_line_len = PREFIX_SPACE_SIZE + curr_str.size();
                curr_str = "";
                continue;
            }
            new_line_pos = curr_str.find_last_of(" ", RIGHT_STR_MAX_LEN + LEFT_STR_MAX_LEN);
            if ((size_t)new_line_pos == curr_str.npos) {
                new_line_pos = RIGHT_STR_MAX_LEN + LEFT_STR_MAX_LEN;
            } else {
                new_line_pos += 1;
            }
            if (curr_line_len > PREFIX_SPACE_SIZE) {
                str += "\n" + prefix_space;
                curr_line_len = PREFIX_SPACE_SIZE;
            }
            str += curr_str.substr(0, new_line_pos);
            curr_str = curr_str.substr(new_line_pos, curr_str.npos);
            str += "\n" + prefix_space;
            curr_line_len = PREFIX_SPACE_SIZE;
        }
        if (curr_str != "") {
            str += curr_str;
            curr_line_len += PREFIX_SPACE_SIZE + curr_str.size();
            curr_str = "";
        }
    }
    if (curr_str != prefix_space) {
        str += curr_str;
        str += "\n";
    }
    if (str != "") {
        str = prefix_short_space + this->name + "\n" + str;
    }

    return str;
}


string CommandLineRequester::GetUsageDescription()
{
    optional_sec_data_t desc_data;
    desc_data.name = "DESCRIPTION";
    desc_data.str1 = this->description;
    vector<struct optional_help_section_data> desc_vector;
    desc_vector.push_back(desc_data);
    return this->GetUsageOptionalSection(desc_vector);
}


string CommandLineRequester::GetUsageOptions(bool hidden_options)
{
    string str = "";
    string opt_str, desc_str;
    string prefix_space = CreateIndentFromInt(PREFIX_SPACE_SIZE);
    string prefix_short_space = CreateIndentFromInt(IDENT_LENGTH);

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
        opt_str = prefix_space;
        opt_str += this->BuildOptStr(*it);
        opt_str = FormatUsageStr(opt_str, LEFT_STR_MAX_LEN, PREFIX_SPACE_SIZE, 1, true);
        str += opt_str;
        desc_str = FormatUsageStr((*it).description, RIGHT_STR_MAX_LEN, LEFT_STR_MAX_LEN + PREFIX_SPACE_SIZE +
                                  COLON_AND_SPACE_SIZE, 0, false);
        str += desc_str;
        str += "\n";
    }
    if (str != "") {
        str = prefix_short_space + this->name + "\n" + str;
    }
    return str;
}


string CommandLineRequester::GetUsageOptionalSections(vector<string> excluded_sections)
{
    string res = "";

    for (unsigned i = 0; i < optional_sections_vec.size(); ++i) {
        if (find(excluded_sections.begin(), excluded_sections.end(), optional_sections_vec[i].first) !=
            excluded_sections.end()) {
            continue;
        }
        res += optional_sections_vec[i].first + "\n";
        res += GetUsageOptionalSection(optional_sections_vec[i].second) + "\n";
    }
    return res;
}

string CommandLineRequester::GetUsageOptional1Str(vector<struct optional_help_section_data>::iterator it)
{
    string data_string("");
    string prefix_space = CreateIndentFromInt(PREFIX_SPACE_SIZE);
    data_string += FormatUsageStr(prefix_space + it->str1, LEFT_STR_MAX_LEN + RIGHT_STR_MAX_LEN, PREFIX_SPACE_SIZE, 1,
                                  false);
    data_string += "\n";
    return data_string;
}

string CommandLineRequester::GetUsageOptional2Str(vector<struct optional_help_section_data>::iterator it)
{
    string data_string("");
    string prefix_space = CreateIndentFromInt(PREFIX_SPACE_SIZE);
    data_string += FormatUsageStr(prefix_space + it->str1, LEFT_STR_MAX_LEN, PREFIX_SPACE_SIZE, 1, true);
    data_string += FormatUsageStr(it->str2, RIGHT_STR_MAX_LEN,
                                  LEFT_STR_MAX_LEN  + PREFIX_SPACE_SIZE + COLON_AND_SPACE_SIZE, 0, false);
    data_string += "\n";
    return data_string;
}

string CommandLineRequester::GetUsageOptionalSection(vector<struct optional_help_section_data> section_vec)
{
    string section_str("");
    if (section_vec.empty()) {
        return section_str;
    }
    for (vector<struct optional_help_section_data>::iterator it = section_vec.begin(); it != section_vec.end(); ++it) {
        if (it->str2 != "") {
            section_str += this->GetUsageOptional2Str(it);
        } else {
            section_str += this->GetUsageOptional1Str(it);
        }
    }
    return section_str;
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
        if ((*it).option_short_name != ' ') { //if space than no short option
            this->short_opt_to_long_opt[(*it).option_short_name] = (*it).option_name;
        }
    }
    this->p_requesters_list.push_back(p_req);
    return 0;
}

string CommandLineParser::GetSynopsis(bool hidden_options)
{
    string res;
    string prefix_short_space = CreateIndentFromInt(IDENT_LENGTH);

    //name
    res = "NAME\n";
    res += prefix_short_space;
    res += this->name;
    res += "\n\n";

    //synopsis
    res += "SYNOPSIS\n";
    for (list_p_command_line_req::iterator it = this->p_requesters_list.begin();
         it != this->p_requesters_list.end(); ++it) {
        res += (*it)->GetUsageSynopsis(hidden_options);
    }
    res += "\n";

    return res;
}

string CommandLineParser::GetUsage(bool hidden_options, vector<string> excluded_sections)
{
    string res;

    //synopsis
    res = GetSynopsis(hidden_options);

    //description
    if (hidden_options == false) {
        res += "DESCRIPTION\n";
        for (list_p_command_line_req::iterator it = this->p_requesters_list.begin();
             it != this->p_requesters_list.end(); ++it) {
            res += (*it)->GetUsageDescription() + "\n";
        }
    }

    //options
    res += "OPTIONS\n";
    for (list_p_command_line_req::iterator it = this->p_requesters_list.begin();
         it != this->p_requesters_list.end(); ++it) {
        res += (*it)->GetUsageOptions(hidden_options) + "\n";
    }

    //optinal sections
    for (list_p_command_line_req::iterator req_it = this->p_requesters_list.begin();
         req_it != this->p_requesters_list.end(); ++req_it) {
        res += (*req_it)->GetUsageOptionalSections(excluded_sections);
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
    internal_argv = new char*[argc];
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
    memset(options_arr, 0, sizeof(struct option) * (num_options + 1));

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
            options_arr[i].name = (char*)(*it2).option_name.c_str();
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

            if (returned_option_types_vec.empty() || (returned_option_types_vec.size() < (unsigned int)options_arr[i].val + 1)) {
                for (unsigned j = returned_option_types_vec.size(); j < (unsigned int)options_arr[i].val + 1; ++j)
                    returned_option_types_vec.push_back(false);
            }
            returned_option_types_vec[options_arr[i].val] = true;
            //printf("%c %d ", options_arr[i].val, options_arr[i].val);
            ++i;
        }
    }

    //finally parse all options
    if (to_ignore_unknown_options == true) {
        tools_opterr = 0;
    } else {
        tools_opterr = 1;
    }
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
            if (to_ignore_unknown_options == true) {
                continue;
            }
            this->SetLastError("Bad input parameter");
            rc = PARSE_ERROR_SHOW_USAGE;
            goto argv_err_exit;
        } else if (returned_option_types_vec[option_type] == true) {
            long_opt_name = this->short_opt_to_long_opt[option_type];
            goto do_handle_option;
        } else {
            this->SetLastError("getopt_long_only() returned character code 0%o", option_type);
            goto parse_exit;
        }

do_handle_option:
        CommandLineRequester * p_req = this->long_opt_to_req_map[long_opt_name];
        bool ignore_this_req = false;
        if (p_ignored_requesters_list) {
            for (list_p_command_line_req::iterator it = p_ignored_requesters_list->begin();
                 it != p_ignored_requesters_list->end(); ++it) {
                if (p_req == (*it)) {
                    ignore_this_req = true;
                    break;
                }
            }
        }
        if (ignore_this_req == false) {
            try{
                curr_result = p_req->HandleOption(long_opt_name, (tools_optarg == NULL) ? "" : tools_optarg);
            }catch (std::exception){
                this->SetLastError("Failed to handle option %s", long_opt_name.c_str());
                goto parse_exit;
            }
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
    if (options_arr) {
        delete [] options_arr;
    }
    return rc;
}


/*Static functions*/

static string CreateIndentFromInt(int ident_size)
{
    string ident = "";
    int i;
    for (i = 0; i < ident_size; i++) {
        ident += " ";
    }
    return ident;
}


static void FindAndReplace(string& source, string::size_type pos, string const& find, string const& replace)
{
    for (string::size_type i = pos; (i = source.find(find, i)) != string::npos;) {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}


static bool FindAndHandleNewLinePos(string& str, int& product_length, int& local_space_size, int& str_type_len,
                                    int& new_line_pos, string newline_and_ident, int deli_is_space)
{
    int plus_one_for_space = 1 * deli_is_space;
    if (!deli_is_space) {
        new_line_pos = str.substr(product_length + local_space_size, str_type_len).find("\n");
    } else {
        new_line_pos = str.substr(product_length + local_space_size + 1, str.npos).
                       find_last_of(" ", str_type_len - 1);
    }
    if ((size_t)new_line_pos != str.npos) {
        new_line_pos += local_space_size + product_length + plus_one_for_space;
        str.replace(new_line_pos, 1, newline_and_ident);
        return true;
    }
    return false;
}
