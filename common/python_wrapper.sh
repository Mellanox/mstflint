#! /bin/sh

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
EXEC_NAME=`basename $(readlink -f $0)`
exec /usr/bin/env python $MSTFLINT_PYTHON_TOOLS/$EXEC_NAME/${EXEC_NAME}.py "$@"
