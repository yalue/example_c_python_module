// This file contains the definitions for wrapping a "printf" statement that
// we can call from python.  It's probably better to just try to follow the
// official tutorial at https://docs.python.org/3/extending/extending.html,
// but this can be a useful example (or reminder if you've done this before) if
// you'd rather cut to the chase.

// Changes the integer type python uses for array sizes when communicating with
// C. Look for it on https://docs.python.org/3/c-api/arg.html for more info.
#define PY_SSIZE_T_CLEAN

#include <stdio.h>
#include <Python.h>

// This will be the thing that gets called when we call
// example_library.print_number(...) from our python scripts.
static PyObject* print_number(PyObject *self, PyObject *args) {
  int arg;

  // This is how we get the values of standard, positional, arguments passed
  // by the python script. See https://docs.python.org/3/c-api/arg.html for
  // more information about argument passing and parsing, including the other
  // "format" strings that we can pass to PyArg_ParseTuple.  In this case, "i"
  // means to parse an integer.
  if (!PyArg_ParseTuple(args, "i", &arg)) {
    // Returning NULL from a Python C function causes python to raise an
    // exception.
    return NULL;
  }

  // Arbitrarily raise an exception if the number passed to the function was
  // negative, just to use an example.
  if (arg < 0) {
    // We can use PyErr_Format to set the exception info before returning NULL.
    // See https://docs.python.org/3/c-api/exceptions.html for more info.
    PyErr_Format(PyExc_ValueError, "print_number requires a positive argument,"
      " but got %d", arg);
    return NULL;
  }

  // Actually print our message.
  printf("Message from C: We got the number %d!\n", arg);

  // Even when returning None, we need to increment its reference counter.
  Py_INCREF(Py_None);
  return Py_None;
}

// We need to create this list of the functions our C module provides. If you
// want to add more functions, add new PyMethodDef structs to this list.
//
// Each struct has the following format:
// {
//   <Name of the function used when calling it from python scripts>,
//   <Pointer to our C function>,
//   <How python should process the args>,
//   <The doc string, shown when calling help(function_name) in python>
// }
//
// See https://docs.python.org/3/c-api/structures.html for more information
// about the PyMethodDef struct.
//
// This list must end with {NULL, NULL, 0, NULL}.
static PyMethodDef example_library_methods[] = {
  {
    "print_number",
    print_number,
    METH_VARARGS,
    "Prints a message to stdout. Requires a non-negative integer argument.",
  },
  {NULL, NULL, 0, NULL},
};

// This time, we create a single struct containing metadata about our entire
// module, including its name in python scripts, its docstring, and the list
// of methods.  See https://docs.python.org/3/c-api/module.html#c.PyModuleDef
// for more information about all the settings you can do with this struct.
static struct PyModuleDef example_library_module = {
  PyModuleDef_HEAD_INIT,
  "example_library",
  "A toy C library showing how work with the C API.",
  -1,
  example_library_methods,
  NULL,
  NULL,
  NULL,
  NULL,
};

// This function is called when our module is first loaded. The main thing to
// note is that it needs to be named PyInit_<module_name>.  It should return
// NULL to raise an exception if it fails for some reason.
PyMODINIT_FUNC PyInit_example_library(void) {
  return PyModule_Create(&example_library_module);
}
