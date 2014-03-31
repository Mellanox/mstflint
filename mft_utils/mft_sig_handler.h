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


#ifndef MFT_SIG_HANDLER
#define MFT_SIG_HANDLER

#ifdef __cplusplus
extern "C" {
#endif


/** @file
 *  mft_sig_hanndler - Generic signal handling API
 *  Re place the default sig handlers for user interrupts with a
 *  'thin' handler that sets a flag and prints message to user
 *  (to stderr), and returns.
 *
 *  This allows application to place this handler in the main
 *  loop and do a propper exit with cleanup on signal.
 *
 *  NOTE: mft_sig_handler saves on first call to
 *  mft_signal_set_handling(1), the current handlers
 *  and restores them each time we turn the thin handler off
 *  thus the main program should not change its default signal
 *  handlers after their initial initilization.
 */

/**
 * @brief Start/Stop the thin handler
 * @param [in] is_on: 1 - enable thin handler. 0 - restore
 *       previous handlers
 * @return 0 on success, 1 otherwise.
 */
int  mft_signal_set_handling(int is_on);

/**
 * @brief signal accepted indication
 * @return N - signal N was accepted. 0 otherwise...
 */
int  mft_signal_is_fired();

/**
 * @brief set value for signal accepted indication.
 *        Can be used to clear signal
 * @param [in] is_fired
 */
void mft_signal_set_fired(int is_fired);

/**
 * @brief Set teh message to be printed on signal
 * @param [in] msg - the mesage or NULL if no message is to be
 *        printed.
 */
void mft_signal_set_msg(char* msg);

#ifdef __cplusplus
}
#endif

#endif

