#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include <math.h>
#include <memory>
#include <vector>
#include "LinearRegression.h"

typedef struct {
	PyObject_HEAD
		LinearRegression lr;
} linear_regression_model;

static void
linear_regression_model_dealloc(linear_regression_model* self)
{
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
linear_regression_model_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	linear_regression_model *self;
	self = (linear_regression_model *)type->tp_alloc(type, 0);
	if (self != NULL) {
	}
	return (PyObject *)self;
}


PyObject* fit(linear_regression_model *self, PyObject *args) {
	PyObject *pylist_x, *pylist_y;
	PyArg_UnpackTuple(args, "ref", 1, 2, &pylist_x, &pylist_y);
	if (PyList_Size(pylist_x) != PyList_Size(pylist_y)) {
		PyErr_SetString(PyExc_TypeError, "Lengths of x and y not equal");
		return (PyObject *)NULL;
	}
	std::vector<double>x;
	std::vector<double>y;
	for (Py_ssize_t i = 0; i < PyList_Size(pylist_x); i++) {
		x.push_back(PyFloat_AsDouble(PyList_GetItem(pylist_x, i)));
		y.push_back(PyFloat_AsDouble(PyList_GetItem(pylist_y, i)));
	}
	self->lr.fit(x, y);
	Py_RETURN_NONE;
}

PyObject * get_a(linear_regression_model *self, PyObject *args) {
	return PyFloat_FromDouble(self->lr.get_a());
}

PyObject * get_b(linear_regression_model *self, PyObject *args) {
	return PyFloat_FromDouble(self->lr.get_b());
}

PyObject * get_score(linear_regression_model *self, PyObject *args) {
	return PyFloat_FromDouble(self->lr.get_score());
}

static PyMethodDef linear_regression_model_methods[] = {
	{"fit", (PyCFunction)fit, METH_VARARGS,
	 "fit model"
	},
	{"a", (PyCFunction)get_a, METH_VARARGS,
	 "a"
	},
	{"b", (PyCFunction)get_b, METH_VARARGS,
	 "b"
	},
	{"score", (PyCFunction)get_score, METH_VARARGS,
	 "score"
	},
	{NULL}  /* Sentinel */
};

static PyTypeObject linear_regression_modelType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"linear_regression_model.LinearRegression_Model",             /* tp_name */
	sizeof(linear_regression_model),             /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)linear_regression_model_dealloc, /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_compare */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT |
		Py_TPFLAGS_BASETYPE,   /* tp_flags */
	"linear_regression_model objects",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	linear_regression_model_methods,             /* tp_methods */
	0,							/* tp_members */
	//linear_regression_model_getseters,
	0,     /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	0,						/* tp_init */
	0,                         /* tp_alloc */
	linear_regression_model_new,                 /* tp_new */
};


static PyModuleDef linear_regression_module = {
	PyModuleDef_HEAD_INIT,
	"linear_regression_module", /* name of module */
	"Module for linear regression.", /* module documentation, may be NULL */
	-1 /* size of per-interpreter state of the module,*/
};

PyMODINIT_FUNC
PyInit_linear_regression(void)
{
	PyObject* m;

	if (PyType_Ready(&linear_regression_modelType) < 0)
		return NULL;

	m = PyModule_Create(&linear_regression_module);

	if (m == NULL)
		return NULL;

	Py_INCREF(&linear_regression_modelType);
	PyModule_AddObject(m, "linear_regression", (PyObject *)&linear_regression_modelType);
	return m;
}

