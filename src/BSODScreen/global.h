/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2018
*
*  TITLE:       GLOBAL.H
*
*  VERSION:     1.00
*
*  DATE:        29 Dec 2018
*
*  Global definitions.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

#if !defined UNICODE
#error ANSI build is not supported
#endif

#if defined (_MSC_VER)
#if (_MSC_VER >= 1900) //VS15, 17 etc
#ifdef _DEBUG
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libucrt.lib")
#pragma comment(lib, "libvcruntime.lib")
#endif
#endif
#endif

#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4152) // nonstandard extension, function/data pointer conversion in expression
#pragma warning(disable: 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable: 6258) // Using TerminateThread does not allow proper thread clean up

#pragma comment(lib, "Scrnsavw.lib")
#pragma comment(lib, "Comctl32.lib")

#include <Windows.h>
#include <ScrnSave.h>
#include "minirtl/minirtl.h"

#pragma warning(push)
#pragma warning(disable: 4458) //declaration of %s hides class member

#include <gdiplus.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <glext.h>
#include <wglext.h>
#include "resource.h"
#include "roos.h"
#include "util.h"

#pragma warning(pop)

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "gdiplus.lib")
