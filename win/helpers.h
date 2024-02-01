// encoding: UTF-8
/******************************************************************************
*                                                                             *
*                                                                             *
* MiniPath - Notepad3 Explorer Plugin                                         *
*                                                                             *
* Helpers.h                                                                   *
*   Definitions for general helper functions and macros                       *
*   Based on code from metapath, (c) Florian Balmer 1996-2011                 *
*                                                                             *
*                                                  (c) Rizonesoft 2008-2024   *
*                                                    https://rizonesoft.com   *
*                                                                             *
*                                                                             *
*******************************************************************************/

#ifndef _ZPAD_HELPERS_H_
#define _ZPAD_HELPERS_H_

#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif 

#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>
#include <VersionHelpers.h>

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UNUSED(expr) (void)(expr)
//#define COUNTOF(ar) ARRAYSIZE(ar)   
#define COUNTOF(ar) (sizeof(ar)/sizeof(ar[0]))
#define CSTRLEN(s)  (COUNTOF(s)-1)


#ifdef __cplusplus
}
#endif

#endif // _ZPAD_HELPERS_H_