#include "encoding.h"

// ============================================================================

// Supported Encodings
WCHAR wchANSI[16] = { L'\0' };
WCHAR wchOEM[16] = { L'\0' };

// special WideCharToMultiByte() encodings (set dwFlags=0 to avoid ERROR_INVALID_FLAGS)
const UINT uCodePageMBCS[] = 
{
    42,                                                                   // (Symbol)
    50220, 50221, 50222, 50225, 50227, 50229,                             // (Chinese, Japanese, Korean)
    52936,                                                                // (GB2312)
    54936,                                                                // (GB18030)
    57002, 57003, 57004, 57005, 57006, 57007, 57008, 57009, 57010, 57011, // (ISCII)
    65000,                                                                // (UTF-7)
    65001                                                                 // (UTF-8)
};

// ============================================================================
DWORD Encoding_GetWCMBFlagsByCodePage(const UINT codePage)
{
    DWORD flags = WC_NO_BEST_FIT_CHARS;
    
    for (int k = 0; k < COUNTOF(uCodePageMBCS); k++) 
    {
        if (codePage == uCodePageMBCS[k]) 
        {
            flags = 0UL;
            break;
        }
    }
    return flags;
}

// ============================================================================

bool Encoding_IsValid(cpi_enc_t iTestEncoding)
{
#if 0
    CPINFO cpi;
    if (Encoding_IsValidIdx(iTestEncoding)) 
    {
        if ((g_Encodings[iTestEncoding].uFlags & NCP_INTERNAL) ||
            (IsValidCodePage(g_Encodings[iTestEncoding].uCodePage) &&
                GetCPInfo(g_Encodings[iTestEncoding].uCodePage, &cpi))) {
            return true;
        }
    }
#endif
    return false;
}

// ============================================================================
cpi_enc_t Encoding_Current(cpi_enc_t iEncoding)
{
    static cpi_enc_t CurrentEncoding = CPI_NONE;

    if (iEncoding >= CPI_NONE) 
    {
        if (Encoding_IsValid(iEncoding)) 
        {
            CurrentEncoding = iEncoding;
        }
        else {
            CurrentEncoding = CPI_PREFERRED_ENCODING;
        }
    }
    return CurrentEncoding;
}
// ============================================================================


