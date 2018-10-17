import os
from setuptools import setup, Extension

timeseries = Extension('expletics.timeseries', sources=['module.cpp'], language='c++')
linear_model = Extension('expletics.linear_model', sources=['linear_model.cpp'], language='c++')

setup(name='expletics',
      version = '0.0.0',
      description = 'Algorithms for measuring similarities in time series lists',
      author = 'Jared Bebb',
      python_requires = '>=2.7,<2.8',
      namespace_packages = ["expletics"],
      ext_modules = [timeseries,linear_model],
      classifiers=[
          "Development Status :: 4 - Beta",
          "Topic :: Scientific/Engineering",
          "Topic :: Software Development"])


'''to compile binaries
cd timeseries or where setup.py is stored
Scripts\python setup.py sdist bdist_wheel
pip install dist\ *.whl i.e timeseries-0.0.0.0-cp27-cp27m-win_amd64.whl'''