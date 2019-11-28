import os
from setuptools import setup, Extension


dtw = Extension('dtw',
				sources=['dtw_extension.cpp','Dtw.cpp'], 
				language='c++')
linear_regression = Extension("linear_regression",
						sources=["linear_regression_extension.cpp","LinearRegression.cpp"],
						language='c++')				
perceptron = Extension('perceptron',
				sources=['perceptron_extension.cpp', 'perceptron.cpp'],
				language='c++')
				
				
setup(name='expletics',
      version = '0.0.0',
      description = 'Algorithms for measuring similarities in time series lists',
      author = 'Jared Bebb',
      python_requires = '>=3.6,<3.7',
      install_requires=['pybind11>=2.2'],
      ext_modules = [dtw,perceptron,linear_regression],
      classifiers=[
          "Development Status :: 4 - Beta",
          "Topic :: Scientific/Engineering",
          "Topic :: Software Development"])

'''to compile binaries
python setup.py build
python setup.py install

from linear_regression import linear_regression as LR
lr = LR()
x = [0,1,2,3,4,5,6,7,8,9]
y = [5,10,25,30,40,50,65,70,80,90]

lr.fit(x, y)
print("a:",lr.a())
print("b:",lr.b())
print("score:",lr.score())

import dtw
print(dtw.calculate_dtw_distance([1,2,3],[1,3,3]))


from perceptron import perceptron_model as pm
input =  [[1, 1],[0.6, 0.6],[0.4, 0],[0, 0.4],[0, 0]]
labels = [1,1,0,0,0]
learning_rate = 0.01
maxIter = 10
perc = pm()

perc.train(input,labels,learning_rate,maxIter)

test = [.88,.76]
test1 = [0.7,0.84]
test2 = [0.3,0.44]
test3 = [0.2,0.0]

print(perc.predict(test))
print(perc.predict(test1))
print(perc.predict(test2))
print(perc.predict(test3))
'''