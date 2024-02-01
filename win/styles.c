
#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif 

#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>

#include "styles.h"


//=============================================================================
//
//  Style_SetDefaultFont()
//
void Style_SetDefaultFont(HWND hwnd, bool bGlobalDefault)
{
#if 0
    WCHAR newStyle[BUFSIZE_STYLE_VALUE] = { L'\0' };
    WCHAR lexerName[BUFSIZE_STYLE_VALUE] = { L'\0' };
    WCHAR styleName[BUFSIZE_STYLE_VALUE] = { L'\0' };

    PEDITLEXER const pLexer = bGlobalDefault ? GetCurrentStdLexer() : s_pLexCurrent;
    PEDITSTYLE const pLexerDefStyle = &(pLexer->Styles[STY_DEFAULT]);

    StringCchCopyW(newStyle, COUNTOF(newStyle), pLexer->Styles[STY_DEFAULT].szValue);

    GetLngString(pLexer->resID, lexerName, COUNTOF(lexerName));
    GetLngString(pLexer->Styles[STY_DEFAULT].rid, styleName, COUNTOF(styleName));

    DEFAULT_FONT_STYLES const defaultFontStyle = bGlobalDefault ? DFS_GLOBAL : DFS_CURR_LEXER;
    if (Style_SelectFont(hwnd, newStyle, COUNTOF(newStyle), lexerName, styleName, defaultFontStyle)) 
    {
        // set new styles to current lexer's default text
        StringCchCopyW(pLexerDefStyle->szValue, COUNTOF(pLexerDefStyle->szValue), newStyle);
        Style_ResetCurrentLexer(Globals.hwndEdit);
    }
#endif
}
