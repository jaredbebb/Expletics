rem ..\tests\venv\Scripts\activate
rem "%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x64
set DISTUTILS_USE_SDK=1
set MSSdk=1
python setup.py sdist bdist_wheel
pip install dist/expletics-0.0.0-cp27-cp27m-win_amd64.whl