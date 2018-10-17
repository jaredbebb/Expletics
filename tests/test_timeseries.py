import expletics
from expletics import timeseries
import unittest
from unittest import TestLoader, TextTestRunner, TestSuite
import warnings

class DtwMethods(unittest.TestCase):
    def setUp(self):
        self.lista = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.lista1 = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.listb = [1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0]
        self.trenddown =[16.0,8.0,4.0,2.0,0.0,0.0,0.0]
        self.str_arr = ["hi","hi", "heelo","heelo","heelo", "bye","bye"]
        self.short_trend =[16.0,8.0,5.0,3.0]

    def test_upper(self):
        self.assertEqual('foo'.upper(), 'FOO')

    def test_dtw(self):
        self.assertEquals(15,timeseries.dtw(self.lista,self.listb))
        self.assertEquals(0.0,timeseries.dtw(self.lista,self.lista1))


    def test_wrong_array_type(self):
        with self.assertRaises(TypeError):
            timeseries.dtw(self.trenddown,self.str_arr)

    def test_invalid_object_type(self):
        for i in ["fjdkla;fdj",'r',1,5.6,-13]:
            with self.assertRaises(TypeError):
                timeseries.dtw(self.trenddown,i)

#from timeseries import euclidean
class EuclideanMethods(unittest.TestCase):
    def setUp(self):
        self.lista = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.lista1 = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.listb = [1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0]
        self.str_arr = ["hi","hi", "heelo","heelo","heelo", "bye","bye","bye","bye","bye"]

    def test_euclidean(self):
        self.assertEqual(0.0, timeseries.euclidean(self.lista,self.lista1))
        self.assertEqual(176.0, timeseries.euclidean(self.lista,self.listb))

    def test_wrong_array_type(self):
        with self.assertRaises(TypeError):
            self.assertEqual(18, timeseries.euclidean(self.lista,self.str_arr))

    def test_invalid_object_type(self):
        for i in ["fjdkla;fdj",'r',1,5.6,-13]:
            with self.assertRaises(TypeError):
                timeseries.euclidean(self.lista,i)



from expletics import linear_model as lm
class Linear_Regression_Methods(unittest.TestCase):
    def setUp(self):
        self.list_x = [0,1,2,3,4,5,6,7,8,9]
        self.list_y = [1,2,3,4,5,6,7,8,9,10]

        self.list_x1 = [17,13,12,15,16,14,16,16,18,19]
        self.list_y1 = [94,73,59,80,93,85,66,79,77,91]

    def test_linear_regression(self):
        self.assertEqual(["%.4f" % e for e in [1.0,1.0,3.027650354,3.027650354,1.0,4.5,5.5]],
                         ["%.4f" % e for e in lm.LinearRegression(self.list_x, self.list_y)])

        self.assertEqual(["%.4f" % e for e in [3.1792, 30.1038,2.170509413,11.57631682,0.596094761,15.6,79.7]],
                         ["%.4f" % e for e in lm.LinearRegression(self.list_x1, self.list_y1)])


for methods in [DtwMethods,EuclideanMethods,Linear_Regression_Methods]:
    tests = [unittest.defaultTestLoader.loadTestsFromTestCase(methods)]
    suite = TestSuite(tests)
    runner = TextTestRunner(verbosity=2)
    runner.run(suite)