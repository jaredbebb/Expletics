#from distutils.core import setup, Extension, DEBUG

#sfc_module = Extension('timeseries', sources = ['module.cpp'])
#setup(name = 'timeseries', version = '1.0',
#    description = 'Python Package with timeseries C++ extension',
#   ext_modules = [sfc_module]
#   )

import os
from setuptools import setup, Extension

module = Extension('timeseries', sources=['module.cpp'], language='c++')

setup(name='timeseries', ext_modules = [module])