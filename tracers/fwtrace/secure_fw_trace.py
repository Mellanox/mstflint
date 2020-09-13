# Copyright (c) Sep 2019 Mellanox Technologies LTD. All rights reserved.
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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#--

from __future__ import print_function
import sys
import os
import string
import time
from fw_trace_utilities import FwTraceUtilities


class SecureFwTrace(object):
    OPEN_CLOSE_FILE_DELAY_SEC = 1
    LINUX_TRACER_FILE = "/sys/kernel/debug/tracing/trace"
    WINDOWS_TRACER_FILE = ""
    
    def __init__(self,
                 mst_device,
                 device_name,
                 ignore_old_events=False,
                 real_ts=False):
        self._mst_device = mst_device
        self._device_name = device_name
        self._ignore_old_events = ignore_old_events
        self._real_ts = real_ts
        self._MAX_TIME_STAMP = 0
        self._TRACER_FILE = ""
        self._device_freq = 0
        
        if os.name == "nt":
            # future capability - windows
            # self._TRACER_FILE = self.WINDOWS_TRACER_FILE
            pass
        else:    
            self._TRACER_FILE = self.LINUX_TRACER_FILE
        
        if real_ts:
            self._device_freq = FwTraceUtilities.get_device_frequency(device_name)

    def _prepare_and_print_event(self, event): 
        """
        The method responsible for adjusting the event according
        the given flags (real_ts and future formating and flags)
        """
        # if real time stamp is needed
        if self._real_ts:
            event_suffix = event.split("]", 1)[1]
            event_prefix = FwTraceUtilities.ts_to_real_ts(self._MAX_TIME_STAMP, self._device_freq)
            event = "[{0}]{1}".format(event_prefix, event_suffix)

        print(event)
                   
    def _parse_driver_mem_line_to_event(self, line, bdf = "", print_event = True):
        """
        The method responsible for checking filtering and parsing the events,
        store the max time stamp and sending the event for printing if needed
        """  
        # check if the event line belong to the fw trace and contain the bdf address
        if (("fw_tracer: " in line) or ("mlx5_fw: " in line)) and (bdf in line):
            if "fw_tracer: " in line:
                tracer_str = line.split("fw_tracer: ")[1]
            else:
                tracer_str = line.split("mlx5_fw: ")[1]
            tracer_str = tracer_str.split("\n")[0]
            tracer_str = tracer_str[len(bdf + " "):]
            
            # isolate the time stamp and store it for the next time we will
            # read the file (prevent duplication and present the most updated events)
            time_stamp = int(tracer_str.split("]")[0].replace("[", "").replace("]", ""), 16)
            if time_stamp > self._MAX_TIME_STAMP:
                self._MAX_TIME_STAMP = time_stamp
                if print_event:
                    self._prepare_and_print_event(tracer_str)
            
    def parse_driver_mem(self):
        """
        The method responsible for parsing the events file that
        filled by the mellanox driver
        """ 
        self._MAX_TIME_STAMP = 0  
        first_run = True
        second_run = False 
        print_event = True
        
        if os.path.exists(self._TRACER_FILE):
            bdf = FwTraceUtilities.get_dev_dbdf(self._device_name)
            try:  
                while True:
                    # first run is the first time we open the file.
                    # in that case we need to print that we read old event and
                    # apply the logic of the ignore old event if needed
                    if first_run:
                        first_run = False
                        second_run = True
                        if self._ignore_old_events:
                            print_event = False
                        else: 
                            print_event = True   
                            print("Read old events:")
                    # we need to print 'read new event' only one time and only 
                    # at the second time we open the file (new events arrive)
                    elif second_run:
                        print_event = True
                        second_run = False
                        print("Read new events:")
                    
                    fd = open(self._TRACER_FILE, "rt")
                    # go over all the file lines on each iteration
                    # in order to overcome a case that the file has some
                    # corruptions while being written
                    for line in fd:
                        self._parse_driver_mem_line_to_event(line, bdf, print_event)
                                                        
                    fd.close()
                    time.sleep(self.OPEN_CLOSE_FILE_DELAY_SEC)
            except KeyboardInterrupt:
                print("\nStopping... ")        
        else:
            print("no trace file to parse")                
    
##########################################


if __name__ == "__main__":
    sys.exit(ExtractStrings())
