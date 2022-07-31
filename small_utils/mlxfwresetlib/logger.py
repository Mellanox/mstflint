# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --

import logging


class LoggerFactory(object):

    def get(self, name, level):

        if level is None:
            log_level = logging.CRITICAL
        elif level == 'critical':
            log_level = logging.CRITICAL
        elif level == 'error':
            log_level = logging.ERROR
        elif level == 'warning':
            log_level = logging.WARNING
        elif level == 'info':
            log_level = logging.INFO
        elif level == 'debug':
            log_level = logging.DEBUG

        #import logging
        logging.basicConfig(level=log_level, format='%(asctime)s - %(name)s - %(levelname)s - {%(pathname)s:%(lineno)d} - %(message)s')
        logger = logging.getLogger(name)

        #logger = logging.getLogger(name)
        # logger.setLevel(logging.INFO)

        # create a file handler
        #handler = logging.FileHandler(name+'.log')
        # handler.setLevel(logging.INFO)

        # create a logging format
        #formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
        # handler.setFormatter(formatter)

        # add the handlers to the logger
        # logger.addHandler(handler)

        return logger
