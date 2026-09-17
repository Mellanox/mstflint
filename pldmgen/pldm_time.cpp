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

 #include <cstring>
 #include <ctime>
 #include <string>
 #include <sys/time.h>

 #include "pldm_time.h"
 #include "pldm_utils/pldm_utils.h"
 
 void dumpTimeStamp104(std::vector<u_int8_t>& buff, const std::string& releaseDateTime)
 {
     struct timeval tv;
 
     gettimeofday(&tv, NULL);
 
     // bytes 0:1 are for UTC diff
     short utcDiffInMinute = (short)(getUTCOffsetInSecond(tv.tv_sec) / 60);
     utcDiffInMinute = __cpu_to_le16(utcDiffInMinute);
     buff.push_back(((u_int8_t*)&(utcDiffInMinute))[0]);
     buff.push_back(((u_int8_t*)&(utcDiffInMinute))[1]);
 
     // bytes 4:2 is: microseconds within the second
     buff.push_back(0x0);
     buff.push_back(0x0);
     buff.push_back(0x0);
 
     struct tm time;
     memset(&time, 0, sizeof(struct tm));
 
     // release date time format: %Y-%m-%d %H:%M:%S
     if (!releaseDateTime.empty())
     {
         if (strptime(releaseDateTime.c_str(), "%Y-%m-%d %H:%M:%S", &time) == NULL)
         {
            throw PLDMException(
              "-E- Invalid Format. Failed to parse date string - the format should be %s.\n",
              "%Y-%m-%d %H:%M:%S");
             return;
         }
     }
     else
     {
         struct tm* generatedTime = localtime((time_t*)&(tv.tv_sec));
         if (!generatedTime)
         {
             throw PLDMException("-E- Failed to generate time.\n");
             return;
         }
         memcpy(&time, generatedTime, sizeof(struct tm));
     }
 
     // byte 5 is: seconds
     buff.push_back(time.tm_sec);
 
     // byte 6 is: minute
     buff.push_back(time.tm_min);
 
     // byte 7 is: hour
     buff.push_back(time.tm_hour);
 
     // byte 8 is: day of month
     buff.push_back(time.tm_mday);
 
     // byte 9 is: month
     buff.push_back(time.tm_mon + 1);
 
     // bytes 11:10 is: year
     u_int16_t year = time.tm_year + 1900; // tm_year is The number of years since 1900
     dumpUInt16(buff, year);
 
     // byte 12, ignore
     buff.push_back(22); // in bits it is 10110, from 0..3: Time resolution in seconds. 4..7: UTC resolution in minutes
 }
 
 long getUTCOffsetInSecond(time_t t)
 {
     struct tm* local = localtime(&t);
     struct tm* utc = gmtime(&t);
     if (!local || !utc)
     {
         return 0;
     }
     long diff =
       ((local->tm_hour - utc->tm_hour) * 60 + (local->tm_min - utc->tm_min)) * 60L + (local->tm_sec - utc->tm_sec);
     int delta_day = local->tm_mday - utc->tm_mday;
     if ((delta_day == 1) || (delta_day < -1))
     {
         diff += 24L * 60 * 60;
     }
     else if ((delta_day == -1) || (delta_day > 1))
     {
         diff -= 24L * 60 * 60;
     }
     return diff;
 }