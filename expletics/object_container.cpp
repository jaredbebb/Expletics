#include <Python.h>
#include "structmember.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

typedef struct {
	PyObject_HEAD
		PyObject *first; /* first name */
	PyObject *last;  /* last name */
	double score;  /* score */
	int number;
} object_container;




static void
object_container_dealloc(object_container* self)
{
	Py_XDECREF(self->first);
	Py_XDECREF(self->last);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
object_container_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	object_container *self;

	self = (object_container *)type->tp_alloc(type, 0);
	if (self != NULL) {
		self->first = PyString_FromString("");
		if (self->first == NULL) {
			Py_DECREF(self);
			return NULL;
		}

		self->last = PyString_FromString("");
		if (self->last == NULL) {
			Py_DECREF(self);
			return NULL;
		}

		self->number = 0;
		self->score = 0;
	}

	return (PyObject *)self;
}

static int
object_container_init(object_container *self, PyObject *args, PyObject *kwds)
{
	PyObject *first = NULL, *last = NULL, *tmp;


	const char *kwlist[] = { "first", "last", "number", NULL };

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|SSi", const_cast<char **> (kwlist),
		&first, &last,
		&self->number))
		return -1;

	if (first) {
		tmp = self->first;
		Py_INCREF(first);
		self->first = first;
		Py_XDECREF(tmp);
	}

	if (last) {
		tmp = self->last;
		Py_INCREF(last);
		self->last = last;
		Py_XDECREF(tmp);
	}
	return 0.0;
}

static PyMemberDef object_container_members[] = {

	{(char *)"number", T_INT, offsetof(object_container, number), 0,
	 (char *)"noddy number"},
	{NULL}  /* Sentinel */
};

static PyObject *
object_container_name(object_container* self)
{
	static PyObject *format = NULL;
	PyObject *args, *result;

	if (format == NULL) {
		format = PyString_FromString("%s %s");
		if (format == NULL)
			return NULL;
	}

	if (self->first == NULL) {
		PyErr_SetString(PyExc_AttributeError, "first");
		return NULL;
	}

	if (self->last == NULL) {
		PyErr_SetString(PyExc_AttributeError, "last");
		return NULL;
	}

	args = Py_BuildValue("OO", self->first, self->last);
	if (args == NULL)
		return NULL;

	result = PyString_Format(format, args);
	Py_DECREF(args);

	return result;
}

static PyObject *
object_container_getfirst(object_container *self, void *closure)
{
	Py_INCREF(self->first);
	return self->first;
}

static int
object_container_setfirst(object_container *self, PyObject *value, void *closure)
{
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
		return -1;
	}

	if (!PyString_Check(value)) {
		PyErr_SetString(PyExc_TypeError,
			"The first attribute value must be a string");
		return -1;
	}

	Py_DECREF(self->first);
	Py_INCREF(value);
	self->first = value;

	return 0;
}

static PyObject *
object_container_getlast(object_container *self, void *closure)
{
	Py_INCREF(self->last);
	return self->last;
}

static int
object_container_setlast(object_container *self, PyObject *value, void *closure)
{
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
		return -1;
	}

	if (!PyString_Check(value)) {
		PyErr_SetString(PyExc_TypeError,
			"The last attribute value must be a string");
		return -1;
	}

	Py_DECREF(self->last);
	Py_INCREF(value);
	self->last = value;

	return 0;
}

static PyGetSetDef object_container_getseters[] = {
	{(char *)"first",
	 (getter)object_container_getfirst, (setter)object_container_setfirst,
	 (char *)"first name",
	 NULL},
	{(char *)"last",
	 (getter)object_container_getlast, (setter)object_container_setlast,
	 (char *)"last name",
	 NULL},
	{NULL}  /* Sentinel */
};


static PyMethodDef object_container_methods[] = {
	{"name", (PyCFunction)object_container_name, METH_NOARGS,
	 "Return the name, combining the first and last name"
	},
	{NULL}  /* Sentinel */
};

static PyTypeObject object_containerType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"object_container.Object_container",             /* tp_name */
	sizeof(object_container),             /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)object_container_dealloc, /* tp_dealloc */
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
	"object_container objects",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	object_container_methods,             /* tp_methods */
	object_container_members,             /* tp_members */
	object_container_getseters,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)object_container_init,      /* tp_init */
	0,                         /* tp_alloc */
	object_container_new,                 /* tp_new */
};

static PyMethodDef module_methods[] = {
	{NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initobject_container(void)
{
	PyObject* m;

	if (PyType_Ready(&object_containerType) < 0)
		return;

	m = Py_InitModule3("object_container", module_methods,
		"Example module that creates an extension type.");

	if (m == NULL)
		return;

	Py_INCREF(&object_containerType);
	PyModule_AddObject(m, "object_container", (PyObject *)&object_containerType);
}