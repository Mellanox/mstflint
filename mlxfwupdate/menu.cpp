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


#include "menu.h"

BaseMenu::BaseMenu()
{
    _isPrev = false;
    _valid  = false;
    _all       = 0;
    _goBack    = 0;
    _exit      = 0;
    _maxChoice = 0;
}

BaseMenu::~BaseMenu()
{

}

FileTypeMenu::FileTypeMenu()  : BaseMenu()
{

}

FileTypeMenu::~FileTypeMenu()
{

}
BaseMenu* FileTypeMenu::getNextMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    BaseMenu *newMenu = NULL;

    if (!cmd_params.download_dev.length()) {
        newMenu = new DevFamilyMenu;
        return newMenu;
    } else {
        DevFamilyMenu::setValuesDirectly(cmd_params, filterOPtions);
    }

    if (filterOPtions.file_type != "mfa" and !cmd_params.download_os.length()) {
        newMenu = new OSMenu;
        return newMenu;
    } else {
        OSMenu::setValuesDirectly(cmd_params, filterOPtions);
    }

    //newMenu = new PickFilesMenu;
    return newMenu;

}

BaseMenu* FileTypeMenu::getPrevMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) cmd_params;
    (void) filterOPtions;
    BaseMenu *newMenu = NULL;
    return newMenu;
}

bool FileTypeMenu::isPrevious(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) cmd_params;
    (void) filterOPtions;
    return _isPrev;
}

bool FileTypeMenu::isValid(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) filterOPtions;
    return !cmd_params.download_type.length();
}

void FileTypeMenu::setValuesDirectly(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    if (cmd_params.download_type == "") {
        filterOPtions.file_type = "";
    } else {
        filterOPtions.file_type = cmd_params.download_type;
    }
}

void FileTypeMenu::generateMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    _menuText = "";
    if (isValid(cmd_params, filterOPtions)) {
        _menuText = "------ Download Type Selection ------\n";
        _menuText += "\t1- MFA            : (Contains FW images)\n";
        _menuText += "\t2- Self_Extractor : (Update Package for Mellanox Firmware)\n";
        _menuText += "\t3- All\n";
        _menuText += "\t4- Exit\n";
        _menuText += "\n-?- Select an option: ";
        _maxChoice = 4;
        printText();
    } else {
        setValuesDirectly(cmd_params, filterOPtions);
    }
}

bool FileTypeMenu::parseChoice(int choice, bool &isExit, bool &isPrev, filesOPtions &filterOPtions)
{
    isPrev = false;
    isExit = false;
    if (choice > _maxChoice or choice <= 0) {
        fprintf(stderr, "-E- Invalid choice!\n");
        return false;
    }

    switch (choice) {
    case 4:
        isExit = true;
        break;

    case 3:
        filterOPtions.file_type = "all";
        break;

    case 2:
        filterOPtions.file_type = "self_extractor";
        break;

    default:
        filterOPtions.file_type = "mfa";
    }
    return true;
}

BaseMenu* DevFamilyMenu::getNextMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    BaseMenu *newMenu = NULL;

    if (filterOPtions.file_type != "mfa" and !cmd_params.download_os.length()) {
        newMenu = new OSMenu;
        return newMenu;
    } else {
        OSMenu::setValuesDirectly(cmd_params, filterOPtions);
    }

    //newMenu = new PickFilesMenu;
    return newMenu;

}

DevFamilyMenu::DevFamilyMenu()  : BaseMenu()
{

}

DevFamilyMenu::~DevFamilyMenu()
{

}

BaseMenu* DevFamilyMenu::getPrevMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) filterOPtions;
    BaseMenu *newMenu = NULL;
    if (!cmd_params.download_type.length()) {
        newMenu = new FileTypeMenu;
    }
    return newMenu;
}

bool DevFamilyMenu::isPrevious(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) filterOPtions;
    _isPrev = !cmd_params.download_type.length();
    return _isPrev;
}

bool DevFamilyMenu::isValid(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    unsigned int i = 0;
    vector <string> _availableFamilies;
    if (!cmd_params.download_dev.length()) {
        for (i = 0; i < filterOPtions.files.size(); i++) {
            if (std::find(_availableFamilies.begin(), availableFamilies.end(), filterOPtions.files[i].family) == _availableFamilies.end() and
                (filterOPtions.file_type == "all" or filterOPtions.file_type == filterOPtions.files[i].file_type)) {
                _availableFamilies.push_back(filterOPtions.files[i].family);
            }
        }
    } else {
        return false;
    }
    if (_availableFamilies.size() == 1) {
        filterOPtions.family = _availableFamilies[0];
        return false;
    } else {
        return true;
    }
}

void DevFamilyMenu::setValuesDirectly(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    if (cmd_params.download_dev == "") {
        filterOPtions.family = "all";
    } else {
        filterOPtions.family = cmd_params.download_dev;
    }
}

string DevFamilyMenu::beautify(string family)
{
    return beautify_device_name(family);
}

void DevFamilyMenu::generateMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    _menuText = "";
    if (isValid(cmd_params, filterOPtions)) {

        _menuText = "------ Device Family Selection ------\n";
        unsigned int i = 0;

        for (i = 0; i < filterOPtions.files.size(); i++) {
            if (std::find(availableFamilies.begin(), availableFamilies.end(), filterOPtions.files[i].family) == availableFamilies.end() and
                (filterOPtions.file_type == "all" or filterOPtions.file_type == filterOPtions.files[i].file_type)) {
                availableFamilies.push_back(filterOPtions.files[i].family);
            }
        }

        for (i = 0; i < availableFamilies.size(); i++) {
            _menuText += "\t" + int_to_string(i + 1) + "- " + beautify(availableFamilies[i]) + "\n";
        }

        if (availableFamilies.size() > 1) {
            _menuText += "\t" + int_to_string(i + 1) + "- All\n";
            _all = i + 1;
            i++;
            _maxChoice = i;
        }
        if (isPrevious(cmd_params, filterOPtions)) {
            _goBack = i + 1;
            _menuText += "\t" + int_to_string(_goBack) + "- Back\n";
            i++;
        }
        _maxChoice = i + 1;
        _exit = _maxChoice;
        _menuText += "\t" + int_to_string(_exit) + "- Exit\n";
        _menuText += "\n-?- Select an option: ";
        printText();
    }
}

bool DevFamilyMenu::parseChoice(int choice, bool &isExit, bool &isPrev, filesOPtions &filterOPtions)
{

    isPrev = false;
    isExit = false;
    if (choice > _maxChoice or choice <= 0) {
        fprintf(stderr, "-E- Invalid choice!\n");
        return false;
    }

    if (choice == _goBack) {
        isPrev = true;
        return true;
    } else if (choice == _exit) {
        isExit = true;
        return true;
    } else if (choice == _all) {
        filterOPtions.family = "all";
        return true;
    } else {
        filterOPtions.family = availableFamilies[choice - 1];
    }
    return true;
}


BaseMenu* OSMenu::getNextMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) filterOPtions;
    (void) cmd_params;
    //BaseMenu *newMenu =  new PickFilesMenu;
    return NULL;

}

BaseMenu* OSMenu::getPrevMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) filterOPtions;
    BaseMenu *newMenu = NULL;
    if (!cmd_params.download_dev.length()) {
        newMenu = new DevFamilyMenu;
    } else if (!cmd_params.download_type.length()) {
        newMenu = new FileTypeMenu;
    }
    return newMenu;
}

bool OSMenu::isPrevious(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) filterOPtions;
    _isPrev = (!cmd_params.download_type.length() or !cmd_params.download_dev.length());
    return _isPrev;
}

bool OSMenu::isValid(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    (void) filterOPtions;
    return !cmd_params.download_os.length();
}

void OSMenu::setValuesDirectly(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    if (cmd_params.download_os == "") {
        filterOPtions.os = "all";
    } else {
        filterOPtions.os = cmd_params.download_os;
    }

}
string OSMenu::beautify(string os)
{
    if (os == "linux_ppc64") {
        os = "Linux_PPC64";
    } else if (os == "linux_ppc64le") {
        os = "Linux_PPC64le";
    } else if (os == "fbsd10_64") {
        os = "FBSD10_64";
    } else if (os == "fbsd10_32") {
        os = "FBSD10_32";
    } else if (os == "fbsd10_1_64") {
        os = "FBSD10_1_64";
    } else if (os == "fbsd11_64") {
        os = "FBSD11_64";
    }
    os[0] = toupper(os[0]);
    return os;
}
void OSMenu::generateMenu(CmdLineParams &cmd_params, filesOPtions &filterOPtions)
{
    _menuText = "";
    if (isValid(cmd_params, filterOPtions)) {
        _menuText = "------ Operating System Selection ------\n";
        unsigned int i = 0;
        for (i = 0; i < filterOPtions.files.size(); i++) {
            if (filterOPtions.files[i].os != "all" and
                std::find(availableOs.begin(), availableOs.end(), filterOPtions.files[i].os) == availableOs.end() and
                (filterOPtions.family == "all" or filterOPtions.family == filterOPtions.files[i].family) and
                (filterOPtions.file_type == "all" or filterOPtions.file_type == filterOPtions.files[i].file_type)) {
                availableOs.push_back(filterOPtions.files[i].os);
            }
        }

        for (i = 0; i < availableOs.size(); i++) {
            _menuText += "\t" + int_to_string(i + 1) + "- " + beautify(availableOs[i]) + "\n";
        }

        if (availableOs.size() > 1) {
            _menuText += "\t" + int_to_string(i + 1) + "- All\n";
            _all = i + 1;
            i++;
        }

        if (isPrevious(cmd_params, filterOPtions)) {
            _goBack = i + 1;
            _menuText += "\t" + int_to_string(_goBack) + "- Back\n";
            _maxChoice = _goBack;
            i++;
        }
        _exit = i + 1;
        _maxChoice = _exit;
        _menuText += "\t" + int_to_string(_exit) + "- Exit\n";
        _menuText += "\n-?- Select an option: ";
        printText();
    }
}

OSMenu::OSMenu()  : BaseMenu()
{
    ;;
}

OSMenu::~OSMenu()
{
    ;;
}

bool OSMenu::parseChoice(int choice, bool &isExit, bool &isPrev, filesOPtions &filterOPtions)
{
    isPrev = false;
    isExit = false;
    if (choice > _maxChoice or choice <= 0) {
        fprintf(stderr, "-E- Invalid choice!\n");
        return false;
    }

    if (choice == _goBack) {
        isPrev = true;
        return true;
    } else if (choice == _exit) {
        isExit = true;
        return true;
    } else if (choice == _all) {
        filterOPtions.os = "all";
        return true;
    } else {
        filterOPtions.os = availableOs[choice - 1];
    }
    return true;
}
