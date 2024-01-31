#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif 

#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>

#include "ZPad.h"
#include "styles.h"
#include "notepad2.h"


//=============================================================================
//
//  UpdateLineNumberWidth()
//
//
void UpdateLineNumberWidth()
{
    char tchLines[32];
    int  iLineMarginWidthNow;
    int  iLineMarginWidthFit = 16;

    XORShowNumberLines(g_statusU64);

    SendScintillaMessage(SCI_SETMARGINWIDTHN, 0, iLineMarginWidthFit);
    return;

    if (GetShowNumberLines(g_statusU64))
    {
        wsprintfA(tchLines, "_%i_", SendScintillaMessage(SCI_GETLINECOUNT, 0, 0));

        iLineMarginWidthNow = (int)SendScintillaMessage(SCI_GETMARGINWIDTHN, 0, 0);
        // iLineMarginWidthFit = (int)SendScintillaMessage(SCI_TEXTWIDTH, STYLE_LINENUMBER, (LPARAM)tchLines);
        iLineMarginWidthFit = (int)SendScintillaMessage(SCI_TEXTWIDTH, STYLE_LINENUMBER, "_99999");

        if (iLineMarginWidthNow != iLineMarginWidthFit) 
        {
            //SendMessage(hwndEdit,SCI_SETMARGINWIDTHN,0,0);
            //SendMessage(hwndEdit, SCI_SETMARGINWIDTHN, 0, iLineMarginWidthFit);
            SendScintillaMessage(SCI_SETMARGINWIDTHN, 0, iLineMarginWidthFit);
        }
    }
    else
        SendScintillaMessage(SCI_SETMARGINWIDTHN, 0, 0);
}

//=============================================================================
//
//  FileLoad()
//
//
BOOL FileLoad(BOOL bDontSave, BOOL bNew, BOOL bReload, BOOL bNoEncDetect, LPCWSTR lpszFile)
{
#if 0
    WCHAR tch[MAX_PATH] = L"";
    WCHAR szFileName[MAX_PATH] = L"";
    BOOL fSuccess;
    BOOL bUnicodeErr = FALSE;
    BOOL bFileTooBig = FALSE;

    if (!bDontSave)
    {
        if (!FileSave(FALSE, TRUE, FALSE, FALSE))
            return FALSE;
    }

    if (bNew) 
    {
        lstrcpy(szCurFile, L"");
        SetDlgItemText(hwndMain, IDC_FILENAME, szCurFile);
        SetDlgItemInt(hwndMain, IDC_REUSELOCK, GetTickCount(), FALSE);
        if (!fKeepTitleExcerpt)
            lstrcpy(szTitleExcerpt, L"");
        FileVars_Init(NULL, 0, &fvCurFile);
        EditSetNewText(hwndEdit, "", 0);
        Style_SetLexer(hwndEdit, NULL);
        UpdateLineNumberWidth();
        bModified = FALSE;
        bReadOnly = FALSE;
        iEOLMode = iLineEndings[iDefaultEOLMode];
        SendMessage(hwndEdit, SCI_SETEOLMODE, iLineEndings[iDefaultEOLMode], 0);
        iEncoding = iDefaultEncoding;
        iOriginalEncoding = iDefaultEncoding;
        SendMessage(hwndEdit, SCI_SETCODEPAGE, (iDefaultEncoding == CPI_DEFAULT) ? iDefaultCodePage : SC_CP_UTF8, 0);
        EditSetNewText(hwndEdit, "", 0);
        SetWindowTitle(hwndMain, uidsAppTitle, fIsElevated, IDS_UNTITLED, szCurFile,
            iPathNameFormat, bModified || iEncoding != iOriginalEncoding,
            IDS_READONLY, bReadOnly, szTitleExcerpt);

        // Terminate file watching
        if (bResetFileWatching)
            iFileWatchingMode = 0;
        InstallFileWatching(NULL);

        return TRUE;
    }

    if (!lpszFile || lstrlen(lpszFile) == 0) 
    {
        if (!OpenFileDlg(hwndMain, tch, COUNTOF(tch), NULL))
            return FALSE;
    }

    else
        lstrcpy(tch, lpszFile);

    ExpandEnvironmentStringsEx(tch, COUNTOF(tch));

    if (PathIsRelative(tch)) {
        StrCpyN(szFileName, g_wchWorkingDirectory, COUNTOF(szFileName));
        PathAppend(szFileName, tch);
        if (!PathFileExists(szFileName)) {
            WCHAR wchFullPath[MAX_PATH];
            if (SearchPath(NULL, tch, NULL, COUNTOF(wchFullPath), wchFullPath, NULL)) {
                lstrcpy(szFileName, wchFullPath);
            }
        }
    }
    else
        lstrcpy(szFileName, tch);

    PathCanonicalizeEx(szFileName);
    GetLongPathNameEx(szFileName, COUNTOF(szFileName));

    if (PathIsLnkFile(szFileName))
        PathGetLnkPath(szFileName, szFileName, COUNTOF(szFileName));

    // Ask to create a new file...
    if (!bReload && !PathFileExists(szFileName))
    {
        if (flagQuietCreate || MsgBox(MBYESNO, IDS_ASK_CREATE, szFileName) == IDYES) {
            HANDLE hFile = CreateFile(szFileName,
                GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
            dwLastIOError = GetLastError();
            if (fSuccess = (hFile != INVALID_HANDLE_VALUE)) {
                CloseHandle(hFile);
                FileVars_Init(NULL, 0, &fvCurFile);
                EditSetNewText(hwndEdit, "", 0);
                Style_SetLexer(hwndEdit, NULL);
                iEOLMode = iLineEndings[iDefaultEOLMode];
                SendMessage(hwndEdit, SCI_SETEOLMODE, iLineEndings[iDefaultEOLMode], 0);
                if (iSrcEncoding != -1) {
                    iEncoding = iSrcEncoding;
                    iOriginalEncoding = iSrcEncoding;
                }
                else {
                    iEncoding = iDefaultEncoding;
                    iOriginalEncoding = iDefaultEncoding;
                }
                SendMessage(hwndEdit, SCI_SETCODEPAGE, (iEncoding == CPI_DEFAULT) ? iDefaultCodePage : SC_CP_UTF8, 0);
                bReadOnly = FALSE;
                EditSetNewText(hwndEdit, "", 0);
            }
        }
        else
            return FALSE;
    }

    else
        fSuccess = FileIO(TRUE, szFileName, bNoEncDetect, &iEncoding, &iEOLMode, &bUnicodeErr, &bFileTooBig, NULL, FALSE);

    if (fSuccess) {
        lstrcpy(szCurFile, szFileName);
        SetDlgItemText(hwndMain, IDC_FILENAME, szCurFile);
        SetDlgItemInt(hwndMain, IDC_REUSELOCK, GetTickCount(), FALSE);
        if (!fKeepTitleExcerpt)
            lstrcpy(szTitleExcerpt, L"");
        if (!flagLexerSpecified) // flag will be cleared
            Style_SetLexerFromFile(hwndEdit, szCurFile);
        UpdateLineNumberWidth();
        iOriginalEncoding = iEncoding;
        bModified = FALSE;
        //bReadOnly = FALSE;
        SendMessage(hwndEdit, SCI_SETEOLMODE, iEOLMode, 0);
        MRU_AddFile(pFileMRU, szFileName, flagRelativeFileMRU, flagPortableMyDocs);
        if (flagUseSystemMRU == 2)
            SHAddToRecentDocs(SHARD_PATHW, szFileName);
        SetWindowTitle(hwndMain, uidsAppTitle, fIsElevated, IDS_UNTITLED, szFileName,
            iPathNameFormat, bModified || iEncoding != iOriginalEncoding,
            IDS_READONLY, bReadOnly, szTitleExcerpt);

        // Install watching of the current file
        if (!bReload && bResetFileWatching)
            iFileWatchingMode = 0;
        InstallFileWatching(szCurFile);

        // the .LOG feature ...
        if (SendMessage(hwndEdit, SCI_GETLENGTH, 0, 0) >= 4) {
            char tchLog[5] = "";
            SendMessage(hwndEdit, SCI_GETTEXT, 5, (LPARAM)tchLog);
            if (lstrcmpiA(tchLog, ".LOG") == 0) {
                EditJumpTo(hwndEdit, -1, 0);
                SendMessage(hwndEdit, SCI_BEGINUNDOACTION, 0, 0);
                SendMessage(hwndEdit, SCI_NEWLINE, 0, 0);
                SendMessage(hwndMain, WM_COMMAND, MAKELONG(IDM_EDIT_INSERT_SHORTDATE, 1), 0);
                EditJumpTo(hwndEdit, -1, 0);
                SendMessage(hwndEdit, SCI_NEWLINE, 0, 0);
                SendMessage(hwndEdit, SCI_ENDUNDOACTION, 0, 0);
                EditJumpTo(hwndEdit, -1, 0);
                EditEnsureSelectionVisible(hwndEdit);
            }
        }

        // Show warning: Unicode file loaded as ANSI
        if (bUnicodeErr)
            MsgBox(MBWARN, IDS_ERR_UNICODE);
    }

    else if (!bFileTooBig)
        MsgBox(MBWARN, IDS_ERR_LOADFILE, szFileName);

    return(fSuccess);
#endif
    return TRUE;
}
