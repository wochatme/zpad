
#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif 

#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>

#include "styles.h"


//=============================================================================
//
//  Style_StrGetFont()
//
BOOL Style_StrGetFont(LPCWSTR lpszStyle, LPWSTR lpszFont, int cchFont)
{
#if 0
    WCHAR tch[256];
    WCHAR* p;

    if (p = StrStrIW(lpszStyle, L"font:"))
    {
        lstrcpy(tch, p + CSTRLEN(L"font:"));
        if (p = StrChr(tch, L';'))
            *p = L'\0';
        TrimString(tch);
        lstrcpyn(lpszFont, tch, cchFont);
        return TRUE;
    }
#endif
    return FALSE;
}

//=============================================================================
//
//  Style_SetDefaultFont()
//
void Style_SetDefaultFont(HWND hwnd)
{
#if 0
    int iIdx = (bUse2ndDefaultStyle) ? 12 : 0;
    if (Style_SelectFont(hwnd,
        lexDefault.Styles[0 + iIdx].szValue,
        COUNTOF(lexDefault.Styles[0].szValue),
        TRUE)) {
        fStylesModified = TRUE;
        Style_SetLexer(hwnd, pLexCurrent);
    }
#endif
}
