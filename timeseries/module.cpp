#include "module.h"
/*
Step 1: Define true/positive time series classes, ap, an
Step 2: Compare classes to current time series. abs(distanct(a-(ap or an))
Step 3: Print Probability that it is +/- class
*/
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION


PyObject* calculate_dtw_distance(PyObject * lista, PyObject * listb)
{
	int sizea = PyList_Size(lista);
	int sizeb = PyList_Size(listb);
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
				PyErr_SetString(PyExc_TypeError, "List a or list b parameters are not list of type double. Example use dtwdistance([0.1,0.2,0.3],[0.4,0.5,0.6])");
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
				top = std::abs(distance_matrix[i - 1][j]);
				left = std::abs(distance_matrix[i][j - 1]);
				diagonal = std::abs(distance_matrix[i - 1][j - 1]);
				distance_matrix[i][j] = std::min(top, std::min(left,diagonal)) + cost;
			}
		}
	}
	return PyFloat_FromDouble(distance_matrix[sizea - 1][sizea - 1]);
}

PyObject* dtw(PyObject *self, PyObject *args)
{
	PyObject *lista;
	PyObject *listb;
	PyArg_UnpackTuple(args, "ref", 1, 2, &lista, &listb);
	//return 
	if (!PyList_Check(lista) || !PyList_Check(listb)) {
		PyErr_SetString(PyExc_TypeError, "List a or list b parameters are not list type. Example use dtwdistance([0.1,0.2,0.3],[0.4,0.5,0.6])");
		return (PyObject *)NULL;
	}
	int sizea = PyList_Size(lista);
	int sizeb = PyList_Size(listb);
	//works with unequal sized lists
	if (sizea > sizeb) {
		return calculate_dtw_distance(listb, lista);
	}
	else {
		if (sizea < sizeb)
		{
			PyErr_WarnEx(PyExc_RuntimeWarning, "Unequal list sizes", 1);
		}
		return calculate_dtw_distance(lista, listb);
	}
}

PyMethodDef timeseriesMethods[] =
{
	{"dtw", (PyCFunction)dtw, METH_VARARGS, 0},
	{NULL, NULL, NULL, NULL}
};

PyMODINIT_FUNC
inittimeseries(void)
{
	PyObject *m;
	m = Py_InitModule("timeseries", timeseriesMethods);
	if (m == NULL)
		return;
}


