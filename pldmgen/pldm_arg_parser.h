/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

 #pragma once

 #include <memory>
 #include <vector>
 #include "cmdparser/cmdparser.h"
 #include "pldm_params.h"
 
 class PldmgenCmdLineParser : public CommandLineRequester
 {
 public:
     std::unique_ptr<CmdLineParams> _parsedParams;
     PldmgenCmdLineParser();
     ~PldmgenCmdLineParser(){};
     ParseStatus Parse(char** argv, int argc);
     virtual ParseStatus HandleOption(string name, string value);
     void printUsage();
 
 protected:
     CommandLineParser _cmdParser;
     ParseStatus ParseCommand(string& command);
     virtual void initOptions();
 
 private:
     bool isFlag(const string& arg);
 };