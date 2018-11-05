#include <Python.h>
#include "structmember.h"
#include <math.h>
//#include <memory>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

typedef struct {
	PyObject_HEAD
	//PyObject *first; /* first name */
	//PyObject *last;  /* last name */
	PyObject * score;  /* score */
	PyObject * a;
	PyObject * b;
	//std::shared_ptr<PyObject> a;
	int number;
} linear_model;

static void
linear_model_dealloc(linear_model* self)
{
	//Py_XDECREF(self->first);
	//Py_XDECREF(self->last);
	Py_XDECREF(self->score);
	Py_XDECREF(self->a);
	Py_XDECREF(self->b);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
linear_model_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	linear_model *self;

	self = (linear_model *)type->tp_alloc(type, 0);
	if (self != NULL) {
		//self->first = PyString_FromString("");
		//if (self->first == NULL) {
		//	Py_DECREF(self);
		//	return NULL;
		//}

		//self->last = PyString_FromString("");
		//if (self->last == NULL) {
		//	Py_DECREF(self);
		//	return NULL;
		//}

		self->score = PyString_FromString("");
		if (self->score == NULL) {
			Py_DECREF(self);
			return NULL;
		}
		self->a = PyString_FromString("");
		if (self->a == NULL) {
			Py_DECREF(self);
			return NULL;
		}

		//self->a = std::shared_ptr<PyObject>(PyFloat_FromDouble(0.0));
		self->a =PyFloat_FromDouble(0.0);
		self->number = 0;
	}

	return (PyObject *)self;
}

static int
linear_model_init(linear_model *self, PyObject *args, PyObject *kwds)
{
	PyObject *first = NULL, *last = NULL, *tmp;


	const char *kwlist[] = { "first", "last", NULL };

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|SS", const_cast<char **> (kwlist),
		&first, &last))
		return -1;

	//if (first) {
	//	tmp = self->first;
	//	Py_INCREF(first);
	//	self->first = first;
	//	Py_XDECREF(tmp);
	//}

	//if (last) {
	//	tmp = self->last;
	//	Py_INCREF(last);
	//	self->last = last;
	//	Py_XDECREF(tmp);
	//}
	return 0.0;
}

static PyMemberDef linear_model_members[] = {

	{(char *)"linear_model", T_INT, offsetof(linear_model, number), 0,
	(char *)"linear_model number"},
	{NULL}  /* Sentinel */
};



//static PyObject *
//linear_model_name(linear_model* self)
//{
//	static PyObject *format = NULL;
//	PyObject *args, *result;
//
//	if (format == NULL) {
//		format = PyString_FromString("%s %s");
//		if (format == NULL)
//			return NULL;
//	}
//
//	if (self->first == NULL) {
//		PyErr_SetString(PyExc_AttributeError, "first");
//		return NULL;
//	}
//
//	if (self->last == NULL) {
//		PyErr_SetString(PyExc_AttributeError, "last");
//		return NULL;
//	}
//
//	args = Py_BuildValue("OO", self->first, self->last);
//	if (args == NULL)
//		return NULL;
//
//	result = PyString_Format(format, args);
//	Py_DECREF(args);
//
//	return result;
//}

double mean(PyObject  * list) {
	double sum = 0.0, count = 0.0;
	for (int i = 0; i < PyList_Size(list); i++) {
		sum += PyFloat_AsDouble(PyList_GetItem(list, i));
		count += 1.0;
	}
	return sum / count;
}


double std_deviation(double a, double length) {
	return sqrt(a / (length - 1));
}


double calculate_slope(double r, double std_devx, double std_devy) {
	return r * (std_devy / std_devx);
}

void calculate_linear_regression(linear_model* self,PyObject * X, PyObject * Y) {
	double x = 0.0, x2 = 0.0, y = 0.0, y2 = 0.0, xy = 0.0;
	double meanx = 0.0, meany = 0.0;
	meanx = mean(X);
	meany = mean(Y);
	Py_ssize_t len = PyList_Size(X);
	for (int i = 0; i < len; i++) {
		x = PyFloat_AsDouble(PyList_GetItem(X, i));
		y = PyFloat_AsDouble(PyList_GetItem(Y, i));
		x2 += pow((x - meanx), 2);
		y2 += pow((y - meany), 2);
		xy += (x - meanx)*(y - meany);
	}
	double r = 0.0, std_devx = 0.0, std_devy = 0.0, b = 0.0, a = 0.0;
	r = xy / sqrt(x2*y2);
	self->score = PyFloat_FromDouble(pow(r, 2));
	std_devx = std_deviation(x2, len);
	std_devy = std_deviation(y2, len);

	b = calculate_slope(r, std_devx, std_devy);
	a = meany - b * meanx;
	self->b = PyFloat_FromDouble(b);
	self->a = PyFloat_FromDouble(a);
}

PyObject* linearRegression(linear_model *self, PyObject *args)
{
	PyObject *list_x;
	PyObject *list_y;
	PyArg_UnpackTuple(args, "ref", 1, 2, &list_x, &list_y);
	calculate_linear_regression(self,list_x, list_y);
	Py_DECREF(list_x);
	Py_DECREF(list_y);
	Py_RETURN_NONE;
}

//static PyObject *
//linear_model_getfirst(linear_model *self, void *closure)
//{
//	Py_INCREF(self->first);
//	return self->first;
//}

//static int
//linear_model_setfirst(linear_model *self, PyObject *value, void *closure)
//{
//	if (value == NULL) {
//		PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
//		return -1;
//	}
//
//	if (!PyString_Check(value)) {
//		PyErr_SetString(PyExc_TypeError,
//			"The first attribute value must be a string");
//		return -1;
//	}
//
//	Py_DECREF(self->first);
//	Py_INCREF(value);
//	self->first = value;
//
//	return 0;
//}

//static PyObject *
//linear_model_getlast(linear_model *self, void *closure)
//{
//	Py_INCREF(self->last);
//	return self->last;
//}

//static int
//linear_model_setlast(linear_model *self, PyObject *value, void *closure)
//{
//	if (value == NULL) {
//		PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
//		return -1;
//	}
//
//	if (!PyString_Check(value)) {
//		PyErr_SetString(PyExc_TypeError,
//			"The last attribute value must be a string");
//		return -1;
//	}
//
//	Py_DECREF(self->last);
//	Py_INCREF(value);
//	self->last = value;
//
//	return 0;
//}


static PyObject *
linear_model_getscore(linear_model* self)
{
	Py_INCREF(self->score);
	return self->score;
}

static int
linear_model_setscore(linear_model *self, PyObject *value, void *closure)
{
	return 0;
}

//static std::shared_ptr<PyObject>
static PyObject *
linear_model_geta(linear_model* self)
{
	Py_INCREF(self->a);
	return self->a;
}

static int
linear_model_seta(linear_model *self, PyObject *value, void *closure)
{
	return 0;
}

static PyObject *
linear_model_getb(linear_model* self)
{
	Py_INCREF(self->b);
	return self->b;
}

static int
linear_model_setb(linear_model *self, PyObject *value, void *closure)
{
	return 0;
}
static PyGetSetDef linear_model_getseters[] = {
	//{(char *)"first",
	// (getter)linear_model_getfirst, (setter)linear_model_setfirst,
	// (char *)"first name",
	// NULL},
	//{(char *)"last",
	// (getter)linear_model_getlast, (setter)linear_model_setlast,
	// (char *)"last name",NULL},
	{(char *)"score",
	 (getter)linear_model_getscore,(setter)linear_model_setscore,
	 (char *)"score",NULL},
	{(char *)"a",
	 (getter)linear_model_geta,(setter)linear_model_seta,
	 (char *)"a",NULL},
	{(char *)"b",
	 (getter)linear_model_getb,(setter)linear_model_setb,
	 (char *)"b",NULL},
	{NULL}  /* Sentinel */
};


static PyMethodDef linear_model_methods[] = {
	//{"name", (PyCFunction)linear_model_name, METH_NOARGS,
	// "Return the name, combining the first and last name"
	//},
	{"LinearRegression", (PyCFunction)linearRegression, METH_VARARGS,
	 "Return the equation of form Y=a+bx"
	},
	{NULL}  /* Sentinel */
};

static PyTypeObject linear_modelType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"linear_model.Linear_Model",             /* tp_name */
	sizeof(linear_model),             /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)linear_model_dealloc, /* tp_dealloc */
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
	"linear_model objects",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	linear_model_methods,             /* tp_methods */
	linear_model_members,             /* tp_members */
	linear_model_getseters,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)linear_model_init,      /* tp_init */
	0,                         /* tp_alloc */
	linear_model_new,                 /* tp_new */
};

static PyMethodDef module_methods[] = {
	{NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initlinear_model(void)
{
	PyObject* m;

	if (PyType_Ready(&linear_modelType) < 0)
		return;

	m = Py_InitModule3("linear_model", module_methods,
		"Example module that creates an extension type.");

	if (m == NULL)
		return;

	Py_INCREF(&linear_modelType);
	PyModule_AddObject(m, "linear_model", (PyObject *)&linear_modelType);
}