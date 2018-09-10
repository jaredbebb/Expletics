#include "module.h"
/*
https://www.tutorialspoint.com/python/python_further_extensions.htm
https://www.youtube.com/watch?v=y_eh00oE5rI
https://docs.microsoft.com/en-us/visualstudio/python/working-with-c-cpp-python-in-visual-studio?view=vs-2017
https://en.wikipedia.org/wiki/Dynamic_time_warping
Step 1: Define true/positive time series classes, ap, an
Step 2: Compare classes to current time series. abs(distanct(a-(ap or an))
Step 3: Print Probability that it is +/- class
*/

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include<iostream>
#include "tchar.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <exception>

PyObject* add_one(PyObject* self, PyObject* args) {
	int i;
	if (!PyArg_ParseTuple(args, "i", &i))
	{
		goto error;
	}
	return PyInt_FromLong(i + 1);
error:
	return 0;
}

PyObject* dtw(PyObject * lista, PyObject * listb)
{
	int sizea = PyList_Size(lista);
	std::vector<std::vector<double>> distance_matrix;
	distance_matrix.resize(sizea, std::vector<double>(sizea, 0.0));
	double top = 0.0;
	double left = 0.0;
	double diagonal = 0.0;
	double cost = 0.0;
	double current = 0.0;
	double compareTo = 0.0;
	for (int i = 0; i < sizea; i++) {
		for (int j = 0; j < sizea; j++) {
			current = PyFloat_AS_DOUBLE(PyList_GET_ITEM(lista, i));
			compareTo = PyFloat_AS_DOUBLE(PyList_GET_ITEM(listb, j));
			cost = std::abs(current-compareTo);
			if (i == 0 && j == 0) {
				distance_matrix[i][j] = cost;
			}
			else if (i == 0) {
				left = std::abs(distance_matrix[i][j - 1]);
				distance_matrix[i][j] = left + cost;
			}
			else if (j == 0) {
				top = std::abs(distance_matrix[i - 1][j]);
				distance_matrix[i][j] = top + cost;
			}
			else {
				top = std::abs(distance_matrix[i - 1][j]);
				left = std::abs(distance_matrix[i][j - 1]);
				diagonal = std::abs(distance_matrix[i - 1][j - 1]);
				distance_matrix[i][j] = std::min(top, std::min(left,diagonal)) + cost;
			}
		}
	}
	return PyFloat_FromDouble(distance_matrix[sizea - 1][sizea - 1]);
}

PyObject* dtwdistance(PyObject *self, PyObject *args)
{
	PyObject *lista;
	PyObject *listb;
	PyArg_UnpackTuple(args, "ref", 1, 2, &lista, &listb);
	return dtw(lista, listb);
}


PyMethodDef timeseriesMethods[] =
{
	{"add_one", (PyCFunction)add_one, METH_VARARGS, 0},
	{"dtwdistance", (PyCFunction)dtwdistance, METH_VARARGS, 0},
	{0, 0, 0, 0}
};

PyMODINIT_FUNC
inittimeseries(void)
{
	PyObject *m;
	m = Py_InitModule("timeseries", timeseriesMethods);
	if (m == NULL)
		return;
}


