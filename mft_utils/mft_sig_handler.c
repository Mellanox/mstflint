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


#include <stdio.h>
#include <signal.h>

#include <tools_utils.h>

static int s_is_fired = 0;
static char* s_interrupt_message = NULL;

//siganls to handle
#ifdef __WIN__
    static int signals_array[] =
    {SIGINT};
#else
    static int signals_array[] = {SIGINT, SIGQUIT, SIGTERM};
#endif

static void (*prev_handlers[sizeof(signals_array)/sizeof(signals_array[0])])(int sig);



static void my_termination_handler(int sig)
{
    s_is_fired = sig; // assuming signals recieved are always different then zero
    if (s_interrupt_message) {
        fprintf(stderr, "%s", s_interrupt_message);
    }
}

#ifdef __WIN__
static BOOL CtrlHandler( DWORD fdwCtrlType )
{
    switch( fdwCtrlType )
    {
      // Handle the CTRL-C signal.
      case CTRL_C_EVENT:
      // CTRL-CLOSE: confirm that the user wants to exit.
      case CTRL_CLOSE_EVENT:
      // Pass other signals to the next handler.
      case CTRL_BREAK_EVENT:
      case CTRL_LOGOFF_EVENT:
      case CTRL_SHUTDOWN_EVENT:
          my_termination_handler(SIGINT);
          return TRUE;

      default:
        return FALSE;
    }
 }
#endif

int  mft_signal_set_handling(int is_on)
{
    unsigned int i;

#ifdef __WIN__
    SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, is_on );
#endif
    static int first_on = 0;
    static int is_on_counter = 0;

    if (is_on_counter == 0 && is_on == 0) {
    	//if we reach here it means previous handler is already set so there is no need to restore it once more.
        return 0;
    }
    // incr/decr counter
    if (is_on) {
    	is_on_counter += 1;
    }else {
    	is_on_counter = is_on_counter > 0 ? is_on_counter -1 : is_on_counter;
    }

    if (is_on == 1 && first_on == 0) {
        /* first time we turned thin handler on so we save previous handlers in prev_handlers array */
        for (i = 0; i < sizeof(signals_array)/sizeof(signals_array[0]); i++)
        {
            prev_handlers[i] = signal(signals_array[i], my_termination_handler);
            if (prev_handlers[i] == SIG_ERR) {
                return -1;
            }
        }
        first_on = 1;
        return 0;
    }
    /* not the first time we turned on the signals */
    /* register term/kill signal handler */
    /* we need to call signal routine only when is_on_counter == 0 or 1 (more precisely when it goes from zero to one or visa versa )*/
    if ((is_on_counter == 0 && is_on == 0) || (is_on_counter == 1 && is_on == 1 )) {
    	for (i = 0; i < sizeof(signals_array)/sizeof(signals_array[0]); i++)
    	{
    		if (signal(signals_array[i], is_on_counter > 0 ? my_termination_handler : prev_handlers[i]) == SIG_ERR) {
    			return -1;
    		}
    	}
    }

    return 0;
}

int  mft_signal_is_fired() {
    return s_is_fired;
}

void mft_signal_set_fired(int is_fired)
{
    s_is_fired = is_fired;
}

void mft_signal_set_msg(char* msg)
{
    s_interrupt_message = msg;
}

