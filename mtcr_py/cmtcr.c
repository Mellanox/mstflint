
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
 *
 */

#include <Python.h>
#include <mtcr.h>
#include <string.h>
#include <errno.h>

#define CMTCR_UNUSED(var) ((void)(var))
static PyObject *mtcrModule = 0;
static PyObject *mtcrExceptionType = 0;

/**********************************************
 * mtcr_init
 * @return
 *********************************************/
PyObject* mtcr_init(PyObject *self, PyObject *args)
{
    PyObject *mfileObj;
    const char *dev;
    mfile *mf;


    CMTCR_UNUSED(self);
    // Parse args
    if (!PyArg_ParseTuple(args, "Os", &mfileObj, &dev)) {
        return NULL;
    }

    mf = mopen(dev);
    if (!mf) {
        PyErr_SetString(mtcrExceptionType, strerror(errno));
        return NULL;
    }

    PyObject *mfLong = PyLong_FromVoidPtr(mf);
    PyObject_SetAttrString(mfileObj, "mf", mfLong);
    Py_DecRef(mfLong);

    return Py_None;
}

/**********************************************
 * mtcr_close
 *********************************************/
PyObject* mtcr_close(PyObject *self, PyObject *args)
{
    PyObject *mfileObj;
    const char *dev;
    mfile *mf;

    CMTCR_UNUSED(self);
    // Parse args
    if (!PyArg_ParseTuple(args, "Os", &mfileObj, &dev)) {
        return NULL;
    }

    PyObject *mfLong = PyObject_GetAttrString(mfileObj, "mf");
    mf = (mfile*) PyLong_AsVoidPtr(mfLong);
    if (mf) {
        mclose(mf);
    }
    Py_DecRef(mfLong);

    return Py_None;
}

/**********************************************
 * mtcr_del
 *********************************************/
PyObject* mtcr_del(PyObject *self, PyObject *args)
{
    PyObject *mfileObj;
    const char *dev;

    CMTCR_UNUSED(self);
    // Parse args
    if (!PyArg_ParseTuple(args, "Os", &mfileObj, &dev)) {
        return NULL;
    }

    mtcr_close(self, args);
    PyObject *mfLong = PyLong_FromLong(0);
    PyObject_SetAttrString(mfLong, "mf", mfLong);
    Py_DecRef(mfLong);

    return Py_None;
}

/**********************************************
 * mtcr_read4
 *********************************************/
PyObject* mtcr_read4(PyObject *self, PyObject *args)
{
    PyObject *mfileObj;
    int addr;
    mfile *mf;
    u_int32_t value;
    PyObject *valueObj;

    CMTCR_UNUSED(self);
    // Parse args
    if (!PyArg_ParseTuple(args, "Oi", &mfileObj, &addr)) {
        return NULL;
    }

    PyObject *mfLong = PyObject_GetAttrString(mfileObj, "mf");
    mf = (mfile*) PyLong_AsVoidPtr(mfLong);
    Py_DecRef(mfLong);

    if (mread4(mf, addr, &value) != 4) {
        PyErr_SetString(mtcrExceptionType, strerror(errno));
        return NULL;
    }

    valueObj = PyLong_FromLong(value);
    return valueObj;
}

/**********************************************
 * mtcr_read4
 *********************************************/
PyObject* mtcr_read4block(PyObject *self, PyObject *args)
{
    PyObject *mfileObj;
    int addr;
    int i;
    mfile *mf;
    int dword_len;
    PyObject *data_list;
    u_int32_t *data_buf;
    PyObject *mfLong;

    CMTCR_UNUSED(self);
    // Parse args
    if (!PyArg_ParseTuple(args, "Oii", &mfileObj, &addr, &dword_len)) {
        return NULL;
    }

    mfLong = PyObject_GetAttrString(mfileObj, "mf");
    mf = (mfile*) PyLong_AsVoidPtr(mfLong);
    Py_DecRef(mfLong);

    data_buf = malloc(sizeof(u_int32_t) * dword_len);
    if (!data_buf) {
        PyErr_SetString(mtcrExceptionType, "Out read of memory");
        return NULL;
    }

    if (mread4_block(mf, addr, data_buf, dword_len * 4) != (dword_len * 4)) {
        PyErr_SetString(mtcrExceptionType, strerror(errno));
        return NULL;
    }

    data_list = PyList_New(dword_len);
    for (i = 0; i < dword_len; i++) {
        PyList_SET_ITEM(data_list, i, PyInt_FromLong((long)data_buf[i]));
    }

    return data_list;
}

/**********************************************
 * mtcr_write4
 *********************************************/
PyObject* mtcr_write4(PyObject *self, PyObject *args)
{
    PyObject *mfileObj;
    int addr;
    mfile *mf;
    u_int32_t value;

    CMTCR_UNUSED(self);
    // Parse args
    if (!PyArg_ParseTuple(args, "Oii", &mfileObj, &addr, &value)) {
        return NULL;
    }

    PyObject *mfLong = PyObject_GetAttrString(mfileObj, "mf");
    mf = (mfile*) PyLong_AsVoidPtr(mfLong);
    Py_DecRef(mfLong);

    if (mwrite4(mf, addr, value) != 4) {
        PyErr_SetString(mtcrExceptionType, strerror(errno));
        return NULL;
    }

    return Py_None;
}

/**********************************************
 * mtcr_write4block
 *********************************************/
PyObject* mtcr_write4block(PyObject *self, PyObject *args)
{
    PyObject *mfileObj;
    int addr;
    int i;
    mfile *mf;
    int dword_len;
    PyObject *data_list;
    u_int32_t *data_buf;
    PyObject *mfLong;

    CMTCR_UNUSED(self);
    // Parse args
    if (!PyArg_ParseTuple(args, "OiO", &mfileObj, &addr, &data_list)) {
        return NULL;
    }

    mfLong = PyObject_GetAttrString(mfileObj, "mf");
    mf = (mfile*) PyLong_AsVoidPtr(mfLong);
    Py_DecRef(mfLong);

    dword_len = PyList_Size(data_list);
    data_buf = malloc(sizeof(u_int32_t) * dword_len);
    if (!data_buf) {
        PyErr_SetString(mtcrExceptionType, "Write Out of memory");
        return NULL;
    }

    for (i = 0; i < dword_len; i++) {
        data_buf[i] = PyLong_AsUnsignedLong(PyList_GET_ITEM(data_list, i));
    }

    if (mwrite4_block(mf, addr, data_buf, dword_len * 4) != (dword_len * 4)) {
        PyErr_SetString(mtcrExceptionType, strerror(errno));
        return NULL;
    }

    return Py_None;
}

/**********************************************
 * mtcr_funcs static db
 *********************************************/
static PyMethodDef mtcr_funcs [] = { {"mtcr_init", (PyCFunction)mtcr_init, METH_VARARGS,  "Init mfile object"},
                                     {"mtcr_close", (PyCFunction)mtcr_close, METH_VARARGS, "Close internal mfile"},
                                     {"mtcr_del", (PyCFunction)mtcr_del, METH_VARARGS, "Free resources"},
                                     {"mtcr_read4", (PyCFunction)mtcr_read4, METH_VARARGS, "Read dword"},
                                     {"mtcr_write4", (PyCFunction)mtcr_write4, METH_VARARGS, "Write dword"},
                                     {"mtcr_read4block", (PyCFunction)mtcr_read4block, METH_VARARGS, "Read block of dwords"},
                                     {"mtcr_write4block", (PyCFunction)mtcr_write4block, METH_VARARGS, "Write block of dwords"},
                                     {NULL, NULL, 0, NULL} };

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

#define TOK_PASTE(x, y) x##y
#define TOK_PASTE2(x, y) TOK_PASTE(x, y)

#define MODULE_NAME "cmtcr" STR(PY_VER)
#define INIT_FUNC TOK_PASTE2(initcmtcr, PY_VER)

/**********************************************
 * initcmtcr
 * @return
 *********************************************/
#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC INIT_FUNC()
{
    Py_InitModule(MODULE_NAME, mtcr_funcs);
    mtcrModule = PyImport_ImportModule("mtcr");
    if (!mtcrModule) {
        PyErr_SetString(mtcrExceptionType, "Failed to import module");
        return;
    }

    mtcrExceptionType =  PyObject_GetAttrString(mtcrModule, "MtcrException");
    if (!mtcrExceptionType) {
        PyErr_SetString(PyExc_ImportError, "Failed to import MtcrException class");
        return;
    }
}
