/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */


#include <iostream>
#include <cmdparser/cmdparser.h>

namespace mlxarchive{


class Mlxarchive : public CommandLineRequester
{
public:
    Mlxarchive();
    ~Mlxarchive();
    ParseStatus HandleOption(string name, string value);
    void run(int agc, char **argv);

private:
    void initCmdParser();
    void printHelp();
    void paramValidate();
    CommandLineParser _cmdParser;
    std::string _binsDir;
    std::string _outFile;
    std::string _date;
    std::string _version;
};
}
