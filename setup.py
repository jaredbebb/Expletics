import os
from setuptools import setup, Extension


dtw = Extension('dtw',
				include_dirs = ['D:/Documents/Visual Studio/repos/expletics/expletics/venv/Include/'],
				library_dirs = ['D:/Documents/Visual Studio/repos/expletics/expletics/venv/Lib/'],
				sources=['dtw_extension.cpp','Dtw.cpp'], 
				language='c++')

setup(name='expletics',
      version = '0.0.0',
      description = 'Algorithms for measuring similarities in time series lists',
      author = 'Jared Bebb',
      python_requires = '>=3.6,<3.7',
      install_requires=['pybind11>=2.2'],
      ext_modules = [dtw],
      classifiers=[
          "Development Status :: 4 - Beta",
          "Topic :: Scientific/Engineering",
          "Topic :: Software Development"])

'''to compile binaries
go into timeseries or where setup.py is stored
Scripts\python setup.py sdist bdist_wheel
pip install dist\ *.whl i.e expletics-0.0.0-cp27-cp27m-win_amd64.whl

https://github.com/pybind/python_example
For earlier versions of Python, including Python 2.7:

Pybind11 requires a C++11 compliant compiler (i.e. Visual Studio 2015 on Windows). 
Running a regular pip install command will detect the version of the compiler used to build Python and attempt to build the extension with it. 
We must force the use of Visual Studio 2015.

clone this repository
"%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x64
set DISTUTILS_USE_SDK=1
set MSSdk=1
'''