#include "module.h"

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION


PyObject* calculate_dtw_distance(PyObject * lista, PyObject * listb)
{
	Py_ssize_t  sizea = PyList_Size(lista);
	Py_ssize_t sizeb = PyList_Size(listb);
	std::vector<std::vector<double>> distance_matrix;
	distance_matrix.resize(sizea, std::vector<double>(sizeb, 0.0));
	double top = 0.0;
	double left = 0.0;
	double diagonal = 0.0;
	double cost = 0.0;
	double current = 0.0;
	double compareTo = 0.0;
	for (int i = 0; i < sizea; i++) {
		for (int j = 0; j < sizeb; j++) {
			current = PyFloat_AsDouble(PyList_GetItem(lista, i));
			compareTo = PyFloat_AsDouble(PyList_GetItem(listb, j));
			if (PyErr_Occurred()) {
				PyErr_SetString(PyExc_TypeError, "List a or list b parameters are not list of type double. Example use dtw([0.1,0.2,0.3],[0.4,0.5,0.6])");
				return (PyObject *)NULL;
			}
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
				//TODO only have to use std::abs for each cell
				top = std::abs(distance_matrix[i - 1][j]);
				left = std::abs(distance_matrix[i][j - 1]);
				diagonal = std::abs(distance_matrix[i - 1][j - 1]);
				distance_matrix[i][j] = std::min(top, std::min(left,diagonal)) + cost;
			}
		}
	}
	return PyFloat_FromDouble(distance_matrix[sizea - 1][sizea - 1]);
}

bool is_list(PyObject *lista, PyObject *listb) {
	if (!PyList_Check(lista) || !PyList_Check(listb)) {
		PyErr_SetString(PyExc_TypeError, "List a or list b parameters are not list type. Example use dist([0.1,0.2,0.3],[0.4,0.5,0.6])");
		return false;
	}
	else {
		return true;
	}	
}

void equal_list_lengths(PyObject *lista, PyObject *listb) {
	if (PyList_Size(lista) != PyList_Size(listb))
	{
		PyErr_WarnEx(PyExc_RuntimeWarning, "Unequal list sizes", 1);
	}
}

bool valid_list_type(PyObject *lista, PyObject *listb) {
	if (PyErr_Occurred()) {
		PyErr_SetString(PyExc_TypeError, "List a or list b parameters are not list of type double. Example use [0.1,0.2,0.3],[0.4,0.5,0.6]");
		return false;
	}
	return true;
}


PyObject* dtw(PyObject *self, PyObject *args)
{
	PyObject *lista;
	PyObject *listb;
	PyArg_UnpackTuple(args, "ref", 1, 2, &lista, &listb);
	if (!is_list(lista,listb)) {
		return (PyObject *)NULL;
	}
	Py_ssize_t sizea = PyList_Size(lista);
	Py_ssize_t sizeb = PyList_Size(listb);
	//works with unequal sized lists. Need to change that in future
	equal_list_lengths(lista, listb);
	if (sizea > sizeb) {
		return calculate_dtw_distance(listb, lista);
	}
	else {
		return calculate_dtw_distance(lista, listb);
	}
}

PyObject* euclidean(PyObject *self, PyObject *args) {
	PyObject *lista;
	PyObject *listb;
	PyArg_UnpackTuple(args, "ref", 1, 2, &lista, &listb);
	if (!is_list(lista, listb)) {
		return (PyObject *)NULL;
	}
	equal_list_lengths(lista, listb);
	int sizea = PyList_Size(lista);
	double sum = 0.0;
	double a = 0.0;
	double b = 0.0;
	for (int i = 0; i < sizea; i++) {
		a = PyFloat_AsDouble(PyList_GetItem(lista, i));
		b = PyFloat_AsDouble(PyList_GetItem(listb, i));
		if(!valid_list_type(lista, listb)){
			return (PyObject *)NULL;
		}
		sum += pow(a-b,2);
	}
	return PyFloat_FromDouble(sum);
}

PyMethodDef timeseriesMethods[] =
{
	{"dtw", (PyCFunction)dtw, METH_VARARGS, 0},
	{"euclidean", (PyCFunction)euclidean, METH_VARARGS, 0},
	{NULL, NULL, NULL, NULL}
};

PyMODINIT_FUNC
inittimeseries(void)
{
	PyObject *m;
	m = Py_InitModule("expletics.timeseries", timeseriesMethods);
	if (m == NULL)
		return ;
}


