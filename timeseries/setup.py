import os
from setuptools import setup, Extension

module = Extension('timeseries', sources=['module.cpp'], language='c++')

setup(name='timeseries', ext_modules = [module])