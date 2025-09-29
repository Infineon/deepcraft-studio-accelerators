/****************************************************************************\
 * Copyright (C) 2015 Infineon Technologies
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#ifdef _WIN32
#define ROYALE_API __declspec(dllexport)

// During debugging we want to show the console.
// We are using __pragma because the preprocessor can't use #pragma in defines.
// Add this above the main function in Qt GUI tools.
#if defined _DEBUG || defined ROYALE_RELEASE_DEBUG_CONSOLE
// Show console
#define ADD_DEBUG_CONSOLE __pragma(comment(linker, "/SUBSYSTEM:console"))
#else
// Hide console
#define ADD_DEBUG_CONSOLE __pragma(comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"))
#endif

#else
#define ROYALE_API
#define ADD_DEBUG_CONSOLE
#endif
