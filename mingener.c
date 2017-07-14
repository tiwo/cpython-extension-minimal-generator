#include <Python.h>
#include <stdio.h>

#include "compatibility23.include.c"


static PyObject *
mingener_print_countdown(PyObject *self, PyObject *args) {
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


typedef struct {
    PyObject_HEAD
    unsigned char number;
} mingener_CounterDownerInstance;


static PyObject *
mingener_CounterDowner_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
  unsigned int *number;

  if (!PyArg_ParseTuple(args, "b", &number)) return NULL;


  mingener_CounterDownerInstance *state
    = (mingener_CounterDownerInstance *)type -> tp_alloc(type, 0);

  if (!state) return NULL;

  state->number = *number;
  return (PyObject *) state;
}


static void mingener_CounterDowner_dealloc(mingener_CounterDownerInstance *state) {
  Py_TYPE(state)->tp_free(state);
}

static PyObject *mingener_CounterDowner_next(mingener_CounterDownerInstance *state) {

  if (!state->number) return NULL;

  PyObject *n = Py_BuildValue("B", state->number);
  if (!n) return NULL;

  state->number --;

  return n;
}


PyTypeObject mingener_CounterDowner = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  "CounterDowner",                /* tp_name */
  sizeof(mingener_CounterDownerInstance),  /* tp_basicsize */
  0,                              /* tp_itemsize */
  (destructor)mingener_CounterDowner_dealloc,     /* tp_dealloc */
  0,                              /* tp_print */
  0,                              /* tp_getattr */
  0,                              /* tp_setattr */
  0,                              /* tp_reserved */
  0,                              /* tp_repr */
  0,                              /* tp_as_number */
  0,                              /* tp_as_sequence */
  0,                              /* tp_as_mapping */
  0,                              /* tp_hash */
  0,                              /* tp_call */
  0,                              /* tp_str */
  0,                              /* tp_getattro */
  0,                              /* tp_setattro */
  0,                              /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT,             /* tp_flags */
  0,                              /* tp_doc */
  0,                              /* tp_traverse */
  0,                              /* tp_clear */
  0,                              /* tp_richcompare */
  0,                              /* tp_weaklistoffset */
  PyObject_SelfIter,              /* tp_iter */
  (iternextfunc)mingener_CounterDowner_next,      /* tp_iternext */
  0,                              /* tp_methods */
  0,                              /* tp_members */
  0,                              /* tp_getset */
  0,                              /* tp_base */
  0,                              /* tp_dict */
  0,                              /* tp_descr_get */
  0,                              /* tp_descr_set */
  0,                              /* tp_dictoffset */
  0,                              /* tp_init */
  PyType_GenericAlloc,            /* tp_alloc */
  mingener_CounterDowner_new,     /* tp_new */
};




static PyMethodDef mingenerMethods[]= {
  {"print_countdown", mingener_print_countdown, METH_VARARGS, "count down on stdout"},
  {NULL, NULL, 0, NULL}
};

MOD_INIT(mingener) {
  PyObject *module;
  MOD_DEF(module, "mingener", "close-to minimal extension module", mingenerMethods)

  if (!module) return MOD_ERROR_VAL;

  if (PyType_Ready(&mingener_CounterDowner) < 0) return MOD_ERROR_VAL;

  Py_INCREF((PyObject *)&mingener_CounterDowner);
  PyModule_AddObject(module, "CounterDowner", (PyObject *)&mingener_CounterDowner);

  return MOD_SUCCESS_VAL(module);
}
