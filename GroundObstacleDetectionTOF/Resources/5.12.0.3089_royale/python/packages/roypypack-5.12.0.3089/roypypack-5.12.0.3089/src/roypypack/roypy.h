/****************************************************************************\
* Copyright (C) 2017 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#if defined(_DEBUG) && defined(SWIG_PYTHON_INTERPRETER_NO_DEBUG)
#define ROYALE_PYTHON_UNDEF_DEBUG
// To be able to link against the release libraries of Python, we have
// to include these headers with undefined _DEBUG symbol.
#include <assert.h>
#include <basetsd.h>
#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#undef _DEBUG
#if defined(_MSC_VER) && _MSC_VER >= 1400
#define _CRT_NOFORCE_MANIFEST 1
#endif
#endif

#if defined(_MSC_VER)
#pragma warning(push, 1)
#endif

#if defined(_MSC_VER) && defined(_DEBUG)
#include <corecrt.h>
#undef _DEBUG
#include <Python.h>
#define _DEBUG 1
#else
#include <Python.h>
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#ifdef ROYALE_PYTHON_UNDEF_DEBUG
#define _DEBUG
#undef ROYALE_PYTHON_UNDEF_DEBUG
#endif

#if defined(_MSC_VER)
#pragma warning(disable : 4127 4456 4459 4701 4703)
#include <BaseTsd.h>
using ssize_t = SSIZE_T;
#endif
