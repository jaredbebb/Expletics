#pragma once

#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED 1
#undef _DEBUG
#endif // _DEBUG

#include <Python.h>
#include<iostream>
#include "tchar.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <exception>
#include <cmath>




#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG 1
#endif // _DEBUG_WAS_DEFINED


