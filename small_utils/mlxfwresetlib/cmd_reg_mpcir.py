# Copyright (c) Sep 2019 Mellanox Technologies LTD. All rights reserved.
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --

import time


class CmdRegMpcir():

    def __init__(self, reg_access):
        self._reg_access = reg_access

    def _wait_for_fw_idle(self):
        DELAY_BETWEEN_SAMPLES = 0.01  # [sec]
        NUM_OF_SAMPLES = 10
        MPCIR_STATUS_IDLE = 0

        for _ in range(NUM_OF_SAMPLES):
            if self._reg_access.sendMpcir(command="status") == MPCIR_STATUS_IDLE:
                break
            time.sleep(DELAY_BETWEEN_SAMPLES)
        else:
            raise RuntimeError("FW is not ready to start ISSU flow (MPCIR)")

    def _start_preperations(self):
        self._reg_access.sendMpcir(command="start")

    def _wait_for_completion(self):
        DELAY_BETWEEN_SAMPLES = 0.01  # [sec]
        NUM_OF_SAMPLES = 10
        MPCIR_STATUS_DONE = 1

        for _ in range(NUM_OF_SAMPLES):
            if self._reg_access.sendMpcir(command="status") == MPCIR_STATUS_DONE:
                break
            time.sleep(DELAY_BETWEEN_SAMPLES)
        else:
            raise RuntimeError("FW didn't finish preperations for FW upgrade on time (MPCIR)")

    def prepare_for_phyless_fw_upgrade(self):
        'send FW an indication to perpare to PHY-less FW upgrade and wait for completion'
        # self._wait_for_fw_idle()  # Removed since it caused failure on MH setup.
        # The first host will pass this wait, but others won't and raise exception.
        self._start_preperations()
        self._wait_for_completion()
