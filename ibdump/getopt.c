/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#include "getopt.h"

/*  for preventing C4996-warning on deprecated functions like strtok in VS 8.0. */
#pragma warning(disable : 4996)

/* Global variables for getopt_long */
char *optarg;
int optind = 1;
int opterr = 1;
int optopt = '?';

static char* get_char_option(const char* optstring,char*const* argv,int argc, int iArg, int* opt_ind,char* opt_p);

/*      *         *           *           *       *       *       *       *       *       */

int iArg = 1;

int getopt(int argc, char *const*argv, const char *optstring)
{

	char chOpt;

	if (iArg == argc)
	{
		return (EOF);
	}

	if (argv[iArg][0] != '-')
	{
		/* Does not start with a - - we are done scanning */
		return (EOF);
	}

	/*termination of scanning */
	if (!strcmp("--",argv[iArg])) {
		return EOF;
	}
	optarg = get_char_option(optstring,argv,argc,iArg,&optind,&chOpt);
	iArg = optind;
	return chOpt;
}

/*      *         *           *           *       *       *       *       *       *       */

int getopt_long(int argc, char *const*argv,
	const char *optstring,
	const struct option *longopts, int *longindex)
{
	char chOpt;
	char tmp_str[256];
	char* tmp_arg = NULL;
	char* tok=NULL;
	int i;
	char tokens[2] = {'='};

	if (iArg == argc)
	{
		return (EOF);
	}

	if (argv[iArg][0] != '-')
	{
		/* Does not start with a - - we are done scanning */
		return (EOF);
	}

	/*termination of scanning */
	if (!strcmp("--",argv[iArg])) {
		return EOF;
	}


	/* char option : -d 5 */
	if ((argv[iArg][0] == '-') &&(argv[iArg][1] != '-') ) {
		optarg = get_char_option(optstring,argv,argc,iArg,&optind,&chOpt);
		iArg = optind;
		return chOpt;
	}

	/* Look for this string in longopts */
	strcpy(tmp_str,&(argv[iArg][2]));

	/*get the option */
	tok = strtok(tmp_str,tokens);

	for (i = 0; longopts[i].name; i++){
		if (strcmp (tok, longopts[i].name) == 0)
		{
			/* We have a match */
			if (longindex != NULL) *longindex = i;

			if (longopts[i].flag != NULL) {
				*(longopts[i].flag) = longopts[i].val;
			}

			if (longopts[i].has_arg != no_argument)
			{
				/*get the argument */

				if (strchr(argv[iArg],'=') != NULL)
				{
					optarg = strtok(NULL,tokens);
				}else {
					/*the next arg in cmd line is the param */
					tmp_arg = argv[iArg+1];
					if (*tmp_arg == '-') {
						/*no param is found */
						chOpt = '?';
						if ((longopts[i].has_arg == required_argument) && opterr)
						{
							fprintf (stderr, "Option %s requires argument\n",tok);
						}

					}else {
						optarg = tmp_arg;
						iArg++;
						optind++;
					}
				}

			}/*longopts */

			iArg++;
			optind++;
			if (longopts[i].flag == 0)
			return (longopts[i].val);
		else return 0;

		}/*end if strcmp */
	}

  return ('?');
}

/*      *    *       *     *          *           *       *           *           *       *       */

static char* get_char_option(const char* optstring,char*const* argv,int argc, int iArg, int* opt_ind,char* opt_p)
	{
	char chOpt;
	char* tmp_str;
	char* prm = NULL;

	chOpt = argv[iArg][1];


	/*non valid argument*/
	if (!isalpha(chOpt))
	{
		chOpt = EOF;
		goto end;
	}

	tmp_str = strchr(optstring, chOpt);

	/*the argument wasn't found in optstring */
	if (tmp_str == NULL){
		chOpt = EOF;
		optopt = chOpt;
		goto end;
	}

	/* don't need argument */
	if (tmp_str[1]!= ':' ) {
		goto end;
	}

	if (argv[iArg][2] != '\0')
	{
		// param is attached to option: -po8889
		prm = &(argv[iArg][2]);
		goto end;
	}

	// must look at next argv for param
	/*at the end of arg list */
	if ((iArg)+1 == argc) {
	/* no param will be found */
		if (tmp_str[2]== ':' ) {
			/* optional argument ::*/
			goto end;
		}else{
			chOpt = EOF;
			goto end;
		}
	}

      prm = &(argv[(iArg)+1][0]);
      if (*prm == '-' )
      {
          // next argv is a new option, so param
         // not given for current option
          if (tmp_str[2]== ':' ) {
              /* optional argument ::*/
              goto end;
          }
          else
           {
                chOpt = EOF;
                goto end;
            }
      }

      // next argv is the param
      (*opt_ind)++;


end:
	(*opt_ind)++;
	*opt_p = chOpt;
	return prm;
}

