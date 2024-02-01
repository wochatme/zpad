#ifndef _ZPAD_STYLES_H_
#define _ZPAD_STYLES_H_

#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif 

#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>
#include <stdbool.h>

#include "stylelexers/editlexer.h"

#ifdef __cplusplus
extern "C" {
#endif

void Style_SetDefaultFont(HWND hwnd, bool bGlobalDefault);


#ifdef __cplusplus
}
#endif




#endif // _ZPAD_STYLES_H_