#from distutils.core import setup, Extension, DEBUG

#sfc_module = Extension('timeseries', sources = ['module.cpp'])

#setup(name = 'timeseries', version = '1.0',
#    description = 'Python Package with timeseries C++ extension',
#   ext_modules = [sfc_module]
#   )

from setuptools import setup, Extension

setup(
    # Information
    name = "timeseries",
    version = "1.0.0.0.2",
    author = "Jared Bebb",
    license = "MIT",
    keywords = "dtw dynamic time warp",
    # Build instructions
    ext_modules = [Extension("timeseries",
                           [ "module.cpp"],
                         #include_dirs=["edlib/include"],
                         depends=["module.h"])],
)