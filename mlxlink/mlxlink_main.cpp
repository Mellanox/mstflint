/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

#include "modules/mlxlink_ui.h"

int main(int argc, char **argv)
{
    int exitCode = 0;
    try {
        mft_signal_set_msg((char*) "Interrupted, Exiting...");
        mft_signal_set_handling(1);
        MlxlinkUi mlxlink;
        exitCode = mlxlink.run(argc, argv);
    } catch (MlxRegException& exp) {
        MlxlinkRecord::printErr("-E- " + string(exp.what_s()));
        exitCode = 1;
    } catch (AdbException& exp) {
        MlxlinkRecord::printErr("-E- " + string(exp.what_s()));
        exitCode = 1;
    } catch (const std::exception& exp) {
        MlxlinkRecord::printErr("-E- General Exception: " + string(exp.what()));
        exitCode = 1;
    }
    return exitCode;
}
