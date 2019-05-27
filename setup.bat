rem ..\tests\venv\Scripts\activate
rem %VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x64
rem set DISTUTILS_USE_SDK=1
rem set MSSdk=1
python setup.py sdist bdist_wheel
rem pip install dist/expletics-0.0.0-cp36-cp36m-win_amd64.whl