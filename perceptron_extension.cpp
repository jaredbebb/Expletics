#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include <math.h>
#include <memory>
#include <vector>

#include "Perceptron.h"



typedef struct {
	PyObject_HEAD
	Perceptron perc;
} perceptron_model;

static void
perceptron_model_dealloc(perceptron_model* self)
{
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
perceptron_model_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	perceptron_model *self;
	self = (perceptron_model *)type->tp_alloc(type, 0);
	if (self != NULL) {
	}
	return (PyObject *)self;
}


PyObject* train(perceptron_model *self, PyObject *args) {
	PyObject *list_input, *list_labels, *learning_rate, *maxIter, *inner_arr;
	PyArg_UnpackTuple(args, "ref", 1, 4, &list_input, &list_labels, &learning_rate, &maxIter);
	Py_ssize_t  sizelist_input = PyList_Size(list_input);
	if (PyList_Size(list_input) != PyList_Size(list_labels)) {
		PyErr_SetString(PyExc_TypeError, "Lengths of labels and input not equal");
		return (PyObject *)NULL;
	}
	std::vector<std::vector<double>>input;
	input.resize(sizelist_input, std::vector<double>(sizelist_input, 0.0));
	std::vector<int> labels;
	std::vector<double> inner;
	for (Py_ssize_t i = 0; i < PyList_Size(list_labels); i++) {
		labels.push_back(PyLong_AsLong(PyList_GetItem(list_labels, i)));
		inner_arr = PyList_GetItem(list_input, i);
		for (Py_ssize_t j = 0; j < PyList_Size(inner_arr); j++) {
			input[i][j] = PyFloat_AsDouble(PyList_GetItem(inner_arr, j));
		}
	}
	self->perc.train(input, labels, (int)2, PyFloat_AsDouble(learning_rate), PyLong_AsLong(maxIter));
	Py_RETURN_NONE;
}

PyObject * predict(perceptron_model *self, PyObject *args) {
	PyObject *list_instance;
	std::vector<double> instance;
	PyArg_UnpackTuple(args, "ref", 1, 1, &list_instance);
	for (Py_ssize_t i = 0; i < PyList_Size(list_instance); i++) {
		instance.push_back(PyFloat_AsDouble(PyList_GetItem(list_instance, i)));
	}
	return PyLong_FromLong(self->perc.predict(instance));
}

static int
linear_model_setb(perceptron_model *self, PyObject *value, void *closure)
{
	return 0;
}

static PyMethodDef perceptron_model_methods[] = {
	{"train", (PyCFunction)train, METH_VARARGS,
	 "train model"
	},
	{"predict", (PyCFunction)predict, METH_VARARGS,
	 "make predictions"
	},
	{NULL}  /* Sentinel */
};

static PyTypeObject perceptron_modelType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"perceptron_model.Perceptron_Model",             /* tp_name */
	sizeof(perceptron_model),             /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)perceptron_model_dealloc, /* tp_dealloc */
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
	"perceptron_model objects",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	perceptron_model_methods,             /* tp_methods */
	0,							/* tp_members */
	//linear_model_getseters,
	0,     /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	0,						/* tp_init */
	0,                         /* tp_alloc */
	perceptron_model_new,                 /* tp_new */
};


static PyModuleDef perceptron_module = {
	PyModuleDef_HEAD_INIT,
	"perceptron_module", /* name of module */
	"Module that creates a perceptron.", /* module documentation, may be NULL */
	-1 /* size of per-interpreter state of the module,*/
};

PyMODINIT_FUNC
PyInit_perceptron(void)
{
	PyObject* m;

	if (PyType_Ready(&perceptron_modelType) < 0)
		return NULL;

	m = PyModule_Create(&perceptron_module);

	if (m == NULL)
		return NULL;

	Py_INCREF(&perceptron_modelType);
	PyModule_AddObject(m, "perceptron_model", (PyObject *)&perceptron_modelType);
	return m;
}