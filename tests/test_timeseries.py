import expletics
from expletics.timeseries import dtw
from expletics.timeseries import euclidean

import unittest
from unittest import TestLoader, TextTestRunner, TestSuite
import warnings

class DtwMethods(unittest.TestCase):
    def setUp(self):
        self.lista = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.lista1 = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.listb = [1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0]
        self.trenddown =[16.0,8.0,4.0,2.0,0.0,0.0,0.0]
        self.trendup = [16.0, 8.0, 4.0, 2.0, 0.0, 0.0, 0.0]
        self.trendflat = [16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0]
        self.str_arr = ["hi","hi", "heelo","heelo","heelo", "bye","bye"]
        self.short_trend =[16.0,8.0,5.0,3.0]

    def test_upper(self):
        self.assertEqual('foo'.upper(), 'FOO')

    def test_dtw(self):
        self.assertEquals(15,dtw(self.lista,self.listb))
        self.assertEquals(0.0,dtw(self.lista,self.lista1))


    def test_wrong_array_type(self):
        with self.assertRaises(TypeError):
            dtw(self.trenddown,self.str_arr)

    def test_invalid_object_type(self):
        for i in ["fjdkla;fdj",'r',1,5.6,-13]:
            with self.assertRaises(TypeError):
                dtw(self.trenddown,i)
    def test_flat(self):
        up = dtw(self.trendflat,self.trendup)
        down = dtw(self.trendflat,self.trenddown)
        self.assertEquals(1.0, (1.0/up)/(1.0/down))

#from timeseries import euclidean
class EuclideanMethods(unittest.TestCase):
    def setUp(self):
        self.lista = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.lista1 = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.listb = [1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0]
        self.str_arr = ["hi","hi", "heelo","heelo","heelo", "bye","bye","bye","bye","bye"]

    def test_euclidean(self):
        self.assertEqual(0.0, euclidean(self.lista,self.lista1))
        self.assertEqual(176.0, euclidean(self.lista,self.listb))

    def test_wrong_array_type(self):
        with self.assertRaises(TypeError):
            self.assertEqual(18, euclidean(self.lista,self.str_arr))

    def test_invalid_object_type(self):
        for i in ["fjdkla;fdj",'r',1,5.6,-13]:
            with self.assertRaises(TypeError):
                euclidean(self.lista,i)

from linear_model import linear_model
class Linear_Regression_Methods(unittest.TestCase):
    def setUp(self):

        self.list_x = [17,13,12,15,16,14,16,16,18,19]
        self.list_y = [94,73,59,80,93,85,66,79,77,91]

        self.list_x1 = [0,1,2,3,4,5,6,7,8,9]
        self.list_y1 = [1,2,3,4,5,6,7,8,9,10]

        self.list_x2 = [0,1,2,3,4,5,6,7,8,9]
        self.list_y2 = [5,10,25,30,40,50,65,70,80,90]



    def test_linear_regression(self):
        lm = linear_model()
        lm.LinearRegression(self.list_x, self.list_y)
        self.assertEqual(["%.4f" % e for e in [0.3553,3.1792, 30.1038]],
                         ["%.4f" % e for e in lm.score,lm.b, lm.a])
        lm2=linear_model()
        lm2.LinearRegression(self.list_x1, self.list_y1)
        self.assertEqual(["%.4f" % e for e in [1.0,1.0,1.0]],
                        ["%.4f" % e for e in lm2.score,lm2.b,lm2.a])

        lm3 = linear_model()
        lm3.LinearRegression(self.list_x2, self.list_y2)
        self.assertEqual(["%.4f" % e for e in [0.9944,9.6667,3.0]],
                        ["%.4f" % e for e in lm3.score,lm3.b,lm3.a])






for methods in [DtwMethods,EuclideanMethods,Linear_Regression_Methods]:
    tests = [unittest.defaultTestLoader.loadTestsFromTestCase(methods)]
    suite = TestSuite(tests)
    runner = TextTestRunner(verbosity=2)
    runner.run(suite)

