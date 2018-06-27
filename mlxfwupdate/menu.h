/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef MENU_H_
#define MENU_H_

#include <vector>
#include <string>
#include <cctype>
#include "mlxfwmanager_common.h"
#include "cmd_line_params.h"

struct filesOPtions {
    string file_type;
    string family;
    string os;
    vector <string> names;
    vector <string> urls;
    vector <string> osDirName;
    vector <DownloadedFileProperties> files;
    vector <DownloadedFileProperties> filtered;
};

class BaseMenu
{
public:
    BaseMenu();
    virtual ~BaseMenu();
    virtual BaseMenu* getNextMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions) = 0;
    virtual BaseMenu* getPrevMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions) = 0;
    virtual bool parseChoice(int choice, bool &isExit, bool &isPrev, filesOPtions &filterOPtions)  = 0;
    virtual void generateMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions) = 0;
    virtual bool isValid(CmdLineParams &cmd_params, filesOPtions &filterOPtions)      = 0;
    virtual bool isPrevious(CmdLineParams &cmd_params, filesOPtions &filterOPtions)    = 0;
    void printText()
    {
        std::cout << _menuText;
    }
protected:
    int _maxChoice;
    bool _valid;
    bool _isPrev;
    int _all;
    int _goBack;
    int _exit;
    std::string _menuText; // This string will be shared by all children (i.e. derived) classes
};

class FileTypeMenu : public BaseMenu {
public:
    FileTypeMenu();
    ~FileTypeMenu();
    BaseMenu* getNextMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    BaseMenu* getPrevMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool parseChoice(int choice, bool &isExit, bool &isPrev, filesOPtions &filterOPtions);
    void generateMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool isValid(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool isPrevious(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    static void setValuesDirectly(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
};

class DevFamilyMenu : public BaseMenu {
public:
    DevFamilyMenu();
    ~DevFamilyMenu();
    BaseMenu* getNextMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    BaseMenu* getPrevMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool parseChoice(int choice, bool &isExit, bool &isPrev, filesOPtions &filterOPtions);
    void generateMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool isValid(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool isPrevious(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    static void setValuesDirectly(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
private:
    string beautify(string family);
    vector <string> availableFamilies;
};

class OSMenu : public BaseMenu {
public:
    OSMenu();
    ~OSMenu();
    BaseMenu* getNextMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    BaseMenu* getPrevMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool parseChoice(int choice, bool &isExit, bool &isPrev, filesOPtions &filterOPtions);
    void generateMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool isValid(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    bool isPrevious(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
    static void setValuesDirectly(CmdLineParams &cmd_params, filesOPtions &filterOPtions);
private:
    string beautify(string os);
    vector <string> availableOs;
};

#endif /* MENU_H_ */
