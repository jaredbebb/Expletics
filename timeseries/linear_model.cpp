#include "linear_model.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION


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

PyObject* calculate_linear_regression(PyObject * X, PyObject * Y) {
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
	double r = 0.0, std_devx = 0.0, std_devy = 0.0, slope = 0.0, a = 0.0;
	r = xy / sqrt(x2*y2);
	std_devx = std_deviation(x2, len);
	std_devy = std_deviation(y2, len);
	slope = calculate_slope(r, std_devx, std_devy);
	a = meany - slope * meanx;

	PyObject * equation = PyList_New(7);
	PyList_SetItem(equation, 0, PyFloat_FromDouble(slope));
	PyList_SetItem(equation, 1, PyFloat_FromDouble(a));
	PyList_SetItem(equation, 2, PyFloat_FromDouble(std_devx));
	PyList_SetItem(equation, 3, PyFloat_FromDouble(std_devy));
	PyList_SetItem(equation, 4, PyFloat_FromDouble(r));
	PyList_SetItem(equation, 5, PyFloat_FromDouble(meanx));
	PyList_SetItem(equation, 6, PyFloat_FromDouble(meany));

	return equation;
	//return PyFloat_FromDouble(a);
	//return PyString_FromString("y=ax+b");
	//return PyFloat_FromDouble(5.5);
}

PyObject* linear_regression(PyObject *self, PyObject *args)
{
	PyObject *list_x;
	PyObject *list_y;
	PyArg_UnpackTuple(args, "ref", 1, 2, &list_x, &list_y);

	return calculate_linear_regression(list_x, list_y);
}

PyMethodDef linear_regressionMethods[] =
{
	{"LinearRegression", (PyCFunction)linear_regression, METH_VARARGS, 0},
	{NULL, NULL, NULL, NULL}
};

PyMODINIT_FUNC
initlinear_model(void)
{
	PyObject *m;
	m = Py_InitModule("expletics.linear_model", linear_regressionMethods);
	if (m == NULL)
		return; 
}


