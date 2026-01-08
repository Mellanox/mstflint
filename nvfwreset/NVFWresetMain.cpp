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

#include <iostream>

#include "NVFWresetParser.h"
#include "ResetParameterChooser.h"
#include "ResetFlowExecutor.h"
#include "mft_utils/mft_sig_handler.h"

using namespace std;

int main(int argc, char* argv[])
{
    int errorCode = 0;
    NVFWresetParser parser;
    ParseStatus status = parser.Parse(argc, argv);
    vector<string> asicDBDFTargets;
    mfile* mf = nullptr;

    mft_signal_set_msg((char*)"Interrupted, Exiting...");
    mft_signal_set_handling(1);
    try
    {
        if (status == PARSE_OK_WITH_EXIT)
        {
            return 0;
        }
        if (status != PARSE_OK)
        {
            throw mft_core::MftGeneralException("Error: Failed to parse command line arguments");
        }

        auto parsedParams = parser.getParsedParams();
        if (parsedParams->cmdType != ResetCommandType::RESET)
        {
            throw mft_core::MftGeneralException(
              "Error: Only reset command is supported. Use 'reset' or 'r' to execute reset.");
        }

        mf = mopen(parsedParams->device.c_str());
        if (mf == nullptr)
        {
            throw mft_core::MftGeneralException("Error: Failed to open device " + parsedParams->device);
        }
        if (mf->dinfo == nullptr)
        {
            throw mft_core::MftGeneralException("Error: Failed to get device information");
        }
        char dbdf[32] = {0};
        snprintf(dbdf, sizeof(dbdf), "%04x:%02x:%02x.%x", mf->dinfo->pci.domain, mf->dinfo->pci.bus, mf->dinfo->pci.dev,
                 mf->dinfo->pci.func);
        asicDBDFTargets.push_back(dbdf);

        ResetParameterChooser chooser(mf, *parsedParams);
        ResetFlowParameters resetFlowParameters = chooser.getResetFlowParameters(mf, asicDBDFTargets);

        if (!parsedParams->answerYes)
        {
            cout << "Continue with reset? [y/N] ";
            string reply;
            getline(cin, reply);
            if (reply.empty() || (reply[0] != 'y' && reply[0] != 'Y'))
            {
                cout << "Reset operation aborted by user." << endl;
                if (mf != nullptr)
                {
                    mclose(mf);
                }
                return 0;
            }
        }

        ResetFlowExecutor resetFlowExecutor(mf, resetFlowParameters, asicDBDFTargets);
        resetFlowExecutor.RunResetFlow(*parsedParams);
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        errorCode = -1;
    }

    if (mf != nullptr)
    {
        mclose(mf);
    }

    mft_restore_and_raise();
    return errorCode;
}
