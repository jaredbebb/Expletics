from setuptools import setup, Extension

setup(
    name = "timeseries",
    version = "1.0.0.0.2",
    author = "Jared Bebb",
    license = "MIT",
    keywords = "dtw dynamic time warp",
    ext_modules = [Extension("timeseries",
                           [ "module.cpp"],
                         depends=["module.h"])],
)