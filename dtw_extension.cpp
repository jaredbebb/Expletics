#include <Python.h>
#include "Dtw.h"


typedef struct {
	PyObject_HEAD
	Dtw dtw;
} dtw_model;

static void
dtw_model_dealloc(dtw_model* self)
{
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
dtw_model_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	Dtw *self;
	self = (Dtw *)type->tp_alloc(type, 0);
	if (self != NULL) {
	}
	return (PyObject *)self;
}

PyObject* calculate_dtw_distance(dtw_model *self, PyObject *args) {
	PyObject *python_list__a, *python_list_b;
	PyArg_UnpackTuple(args, "ref", 1, 2, &python_list__a, &python_list_b);
	if (PyList_Size(python_list__a) != PyList_Size(python_list_b)) {
		PyErr_SetString(PyExc_TypeError, "Lengths of list_a and list_b not equal");
		return (PyObject *)NULL;
	}
	std::vector<double> cpp_list_a;
	for (Py_ssize_t i = 0; i < PyList_Size(python_list__a); i++) {
		cpp_list_a.push_back(PyFloat_AsDouble(PyList_GetItem(python_list__a, i)));
	}
	std::vector<double> cpp_list_b;
	for	(Py_ssize_t i = 0; i < PyList_Size(python_list_b); i++) {
		cpp_list_b.push_back(PyFloat_AsDouble(PyList_GetItem(python_list_b, i)));
	}
	return PyFloat_FromDouble(self->dtw.calculate_dtw_distance(cpp_list_a, cpp_list_b));
}

PyMethodDef dtwMethods[] =
{
	{"calculate_dtw_distance", (PyCFunction)calculate_dtw_distance, METH_VARARGS, 0},
	{NULL, NULL, NULL, NULL}
};

static struct PyModuleDef dtw_module_methods = {
	PyModuleDef_HEAD_INIT,
	"dtw",   /* name of module */
	NULL, /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
				 or -1 if the module keeps state in global variables. */
	dtwMethods
};

PyMODINIT_FUNC
PyInit_dtw(void)
{
	return PyModule_Create(&dtw_module_methods);
}

