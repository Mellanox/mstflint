
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
#include <unistd.h>

#include "iniparser.h"

void create_example_ini_file(void);
int  parse_ini_file(char * ini_name);

int main(int argc, char * argv[])
{
	int		status ;

	if (argc<2) {
		create_example_ini_file();
		status = parse_ini_file("example.ini");
	} else {
		status = parse_ini_file(argv[1]);
	}
	return status ;
}

void create_example_ini_file(void)
{
	FILE	*	ini ;

	ini = fopen("example.ini", "w");
	fprintf(ini,
    "#\n"
    "# This is an example of ini file\n"
    "#\n"
    "\n"
    "[Pizza]\n"
    "\n"
    "Ham       = yes ;\n"
    "Mushrooms = TRUE ;\n"
    "Capres    = 0 ;\n"
    "Cheese    = Non ;\n"
    "\n"
    "\n"
    "[Wine]\n"
    "\n"
    "Grape     = Cabernet Sauvignon ;\n"
    "Year      = 1989 ;\n"
    "Country   = Spain ;\n"
    "Alcohol   = 12.5  ;\n"
    "\n");
	fclose(ini);
}


int parse_ini_file(char * ini_name)
{
	dictionary	*	ini ;

	/* Some temporary variables to hold query results */
	int				b ;
	int				i ;
	double			d ;
	char		*	s ;

	ini = iniparser_load(ini_name);
	if (ini==NULL) {
		fprintf(stderr, "cannot parse file: %s\n", ini_name);
		return -1 ;
	}
	iniparser_dump(ini, stderr);

	/* Get pizza attributes */
	printf("Pizza:\n");

	b = iniparser_getboolean(ini, "pizza:ham", -1);
	printf("Ham:       [%d]\n", b);
	b = iniparser_getboolean(ini, "pizza:mushrooms", -1);
	printf("Mushrooms: [%d]\n", b);
	b = iniparser_getboolean(ini, "pizza:capres", -1);
	printf("Capres:    [%d]\n", b);
	b = iniparser_getboolean(ini, "pizza:cheese", -1);
	printf("Cheese:    [%d]\n", b);

	/* Get wine attributes */
	printf("Wine:\n");
	s = iniparser_getstring(ini, "wine:grape", NULL);
    printf("Grape:     [%s]\n", s ? s : "UNDEF");

    i = iniparser_getint(ini, "wine:year", -1);
    printf("Year:      [%d]\n", i);

	s = iniparser_getstring(ini, "wine:country", NULL);
    printf("Country:   [%s]\n", s ? s : "UNDEF");

    d = iniparser_getdouble(ini, "wine:alcohol", -1.0);
    printf("Alcohol:   [%g]\n", d);

	iniparser_freedict(ini);
	return 0 ;
}


