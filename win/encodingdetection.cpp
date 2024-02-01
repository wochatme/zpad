// encoding: UTF-8
/******************************************************************************
*                                                                             *
*                                                                             *
* Notepad3                                                                    *
*                                                                             *
* EncodingDetection.cpp                                                       *
*   Interface to Encoding Detector  (CED or UCHARDET)                         *
*                                                                             *
*                                                                             *
*                                                  (c) Rizonesoft 2008-2024   *
*                                                    https://rizonesoft.com   *
*                                                                             *
*                                                                             *
*******************************************************************************/

#if !defined(WINVER)
#define WINVER 0x601  /*_WIN32_WINNT_WIN7*/
#endif
#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x601  /*_WIN32_WINNT_WIN7*/
#endif
#if !defined(NTDDI_VERSION)
#define NTDDI_VERSION 0x06010000  /*NTDDI_WIN7*/
#endif

#if (defined(_DEBUG) || defined(DEBUG)) && !defined(NDEBUG)
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define VC_EXTRALEAN 1
#define WIN32_LEAN_AND_MEAN 1
#define NOMINMAX 1
#include <windows.h>

#define STRSAFE_NO_CB_FUNCTIONS
#define STRSAFE_NO_DEPRECATE      // don't allow deprecated functions
#include <strsafe.h>
#include <string_view>

extern "C" 
{
#include "Helpers.h"
#include "PathLib.h"
#include "Encoding.h"
#include "SciCall.h"
}

static WCHAR wchEncodingInfo[MIDSZ_BUFFER] = { L'\0' };

extern "C" const WCHAR * Encoding_GetTitleInfo()
{
    return wchEncodingInfo;
}

constexpr cpi_enc_t _CountOfEncodings()
{
    ///return static_cast<cpi_enc_t>(ARRAYSIZE(g_Encodings));
    return 0;
}

extern "C" cpi_enc_t Encoding_CountOf()
{
    return _CountOfEncodings();
}


