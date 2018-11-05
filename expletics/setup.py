import os
from setuptools import setup, Extension

timeseries = Extension('expletics.timeseries', sources=['module.cpp'],extra_compile_args=['-std=c++14'], language='c++')
#linear_model = Extension('expletics.linear_model', sources=['linear_model.cpp'], language='c++')
noddy2 = Extension("noddy4", sources=["noddy.cpp"],extra_compile_args=['-std=c++14'],language='c++')
object_container = Extension("object_container", sources=["object_container.cpp"],extra_compile_args=['-std=c++14'],language='c++')
linear_model = Extension("linear_model", sources=["linear_model.cpp"],extra_compile_args=['-std=c++14'],language='c++')

setup(name='expletics',
      version = '0.0.0',
      description = 'Algorithms for measuring similarities in time series lists',
      author = 'Jared Bebb',
      python_requires = '>=2.7,<2.8',
      namespace_packages = ["expletics"],
      ext_modules = [timeseries,noddy2,object_container,linear_model],
      classifiers=[
          "Development Status :: 4 - Beta",
          "Topic :: Scientific/Engineering",
          "Topic :: Software Development"])


'''to compile binaries
cd timeseries or where setup.py is stored
Scripts\python setup.py sdist bdist_wheel
pip install dist\ *.whl i.e timeseries-0.0.0.0-cp27-cp27m-win_amd64.whl'''