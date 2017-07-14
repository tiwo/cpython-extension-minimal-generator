#include <Python.h>
#include <stdio.h>

#include "compatibility23.include.c"


static PyObject *
mingener_print_countdown(PyObject *sef, PyObject *args) {
  unsigned char number;

  if (!PyArg_ParseTuple(args, "b", &number)) {
    return NULL;
  }

  for(; number; --number) {
    fprintf(stdout, "%u to go...\n", number);
  }

  fprintf(stdout, "done.\n");

  /* return Py_BuildValue("i", 1); */
  return Py_True;
}


static PyMethodDef mingenerMethods[]= {
  {"print_countdown", mingener_print_countdown, METH_VARARGS, "count down on stdout"},
  {NULL, NULL, 0, NULL}
};

MOD_INIT(mingener) {
  PyObject *module;
  MOD_DEF(module, "mingener", "close-to minimal extension module", mingnerMethods)

  if (!m) return MOD_ERROR_VAL;

  return MOD_SUCCESS_VAL(module);
}
