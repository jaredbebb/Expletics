#pragma once

#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED 1
#undef _DEBUG
#endif // _DEBUG

#include <Python.h>
//#include "D:\Python27_32bit\Lib\site-packages\numpy\core\include\numpy\arrayobject.h"
#include<iostream>
#include "tchar.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <exception>

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG 1
#endif // _DEBUG_WAS_DEFINED


