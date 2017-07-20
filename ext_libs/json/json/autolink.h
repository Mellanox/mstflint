
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

#ifndef JSON_AUTOLINK_H_INCLUDED
# define JSON_AUTOLINK_H_INCLUDED

# include "config.h"

# ifdef JSON_IN_CPPTL
#  include <cpptl/cpptl_autolink.h>
# endif

# if !defined(JSON_NO_AUTOLINK)  &&  !defined(JSON_DLL_BUILD)  &&  !defined(JSON_IN_CPPTL)
#  define CPPTL_AUTOLINK_NAME "json"
#  undef CPPTL_AUTOLINK_DLL
#  ifdef JSON_DLL
#   define CPPTL_AUTOLINK_DLL
#  endif
#  include "autolink.h"
# endif

#endif // JSON_AUTOLINK_H_INCLUDED
