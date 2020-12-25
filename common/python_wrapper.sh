#! /bin/sh
EXEC_PATH=`readlink -f $0`
EXEC_NAME=`basename $EXEC_PATH`
EXEC_DIR=`dirname $EXEC_PATH`

mlibdir=@MST_LIB_DIR@
#@POST_MST_LIB_DIR@  # Update the lib dir by the post install script.
mbindir=@MST_BIN_DIR@
#@POST_MST_BIN_DIR@  # Update the bin dir by the post install script.

MSTFLINT_EXT_PYTHON_LIB_DIR=$mlibdir/mstflint/python_ext_libs
MSTFLINT_PYTHON_TOOLS=$mlibdir/mstflint/python_tools

if test -z "${PYTHONPATH}"; then
   PYTHONPATH=$MSTFLINT_PYTHON_TOOLS:$MSTFLINT_EXT_PYTHON_LIB_DIR
else
   PYTHONPATH=$MSTFLINT_PYTHON_TOOLS:$MSTFLINT_EXT_PYTHON_LIB_DIR:${PYTHONPATH}
fi

export PYTHONPATH
export MSTFLINT_LIB_DIR=$mlibdir
export LD_LIBRARY_PATH=$mlibdir
export MSTFLINT_BIN_DIR=$mbindir
PYTHON_EXEC=`find /usr/bin /bin/ /usr/local/bin -iname 'python*' 2>&1 | grep -e='*python[0-9,.]*' | sort -d | head -n 1`
which python3 >/dev/null 2>&1
if test $? -eq 0 ; then
   PYTHON_EXEC='/usr/bin/env python3'
else
    which python2 >/dev/null 2>&1
    if test $? -eq 0 ; then
       PYTHON_EXEC='/usr/bin/env python2'
    fi
fi

SCRIPT_PATH=$MSTFLINT_PYTHON_TOOLS/${EXEC_NAME}/${EXEC_NAME}.py

if test ! -f $SCRIPT_PATH; then
    SCRIPT_PATH=$(find $MSTFLINT_PYTHON_TOOLS -name ${EXEC_NAME}.py)
fi

if test -z "${SCRIPT_PATH=}"; then
    >&2 echo "-E- Couldn't find ${EXEC_NAME}.py"
    exit 2
fi

exec $PYTHON_EXEC $SCRIPT_PATH "$@"

