from timeseries import dtw
import unittest
from unittest import TestLoader, TextTestRunner, TestSuite
import warnings

class DtwMethods(unittest.TestCase):

    def setUp(self):
        self.lista = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
        self.listb = [1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0]
        self.trenddown =[16.0,8.0,4.0,2.0,0.0,0.0,0.0]
        self.str_arr = ["hi", "heelo", "bye"]
        self.short_trend =[16.0,8.0,5.0,3.0]

    def test_upper(self):
        self.assertEqual('foo'.upper(), 'FOO')

    def test_dtw(self):
        self.assertEquals(15,dtw(self.lista,self.listb)) 
      
    def test_diff_sizes(self):
        self.assertEquals(27,dtw(self.lista,self.short_trend))
        self.assertEquals(27,dtw(self.short_trend,self.lista))

    def test_diff_array_size_warning(self):   
        with warnings.catch_warnings(record=True) as w:
            self.assertEquals(27,dtw(self.short_trend,self.lista))
            assert issubclass(w[-1].category, Warning)

    def test_wrong_array_type(self):
        with self.assertRaises(TypeError):
            dtw(self.trenddown,self.str_arr)

    def test_invalid_object_type(self):
        with self.assertRaises(TypeError):
            dtw(self.trenddown,1.0)

tests = [unittest.defaultTestLoader.loadTestsFromTestCase(DtwMethods)]
suite = TestSuite(tests)
runner = TextTestRunner(verbosity=2)
runner.run(suite)