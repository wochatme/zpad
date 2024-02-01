#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif 

#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>

//#include "ZPad.h"
#include "typedefs.h"
#include "styles.h"
#include "notepad3.h"


FLAGS_T     Flags = { 0 };
FLAGS_T DefaultFlags = { 0 };

GLOBALS_T   Globals = { 0 };
SETTINGS_T  Settings = { 0 };
SETTINGS_T  Defaults = { 0 };
SETTINGS2_T Settings2 = { 0 };

void InitGlobals()
{
#if 0
    Globals.hLngResContainer = NULL;

    Globals.hDlgIcon256 = NULL;
    Globals.hDlgIcon128 = NULL;
    Globals.hDlgIconBig = NULL;
    Globals.hDlgIconSmall = NULL;
    Globals.hDlgIconPrefs256 = NULL;
    Globals.hDlgIconPrefs128 = NULL;
    Globals.hDlgIconPrefs64 = NULL;

    Globals.hMainMenu = NULL;
    Globals.pFileMRU = NULL;
    Globals.pMRUfind = NULL;
    Globals.pMRUreplace = NULL;
    Globals.uAvailLngCount = 1;
    Globals.iWrapCol = 80;

    Globals.CmdLnFlag_PosParam = false;
    Globals.CmdLnFlag_AlwaysOnTop = 0;
    Globals.CmdLnFlag_WindowPos = 0;
    Globals.CmdLnFlag_ReuseWindow = 0;
    Globals.CmdLnFlag_SingleFileInstance = 0;
    Globals.CmdLnFlag_MultiFileArg = 0;
    Globals.CmdLnFlag_ShellUseSystemMRU = 0;
    Globals.CmdLnFlag_PrintFileAndLeave = 0;

    Globals.DOSEncoding = CPI_NONE;
    Globals.bZeroBasedColumnIndex = false;
    Globals.bZeroBasedCharacterCount = false;
    Globals.iReplacedOccurrences = 0;
    Globals.iSelectionMarkNumber = 0;
    Globals.iMarkOccurrencesCount = 0;
    Globals.bUseLimitedAutoCCharSet = false;
    Globals.bIsCJKInputCodePage = false;
    Globals.bIniFileFromScratch = false;
    Globals.bFindReplCopySelOrClip = true;
    Globals.bReplaceInitialized = false;
    Globals.FindReplaceMatchFoundState = FND_NOP;
    Globals.bDocHasInconsistentEOLs = false;
    Globals.pStdDarkModeIniStyles = NULL;
    Globals.bMinimizedToTray = false;
    Globals.uCurrentThemeIndex = 0;

    Flags.bHugeFileLoadState = DefaultFlags.bHugeFileLoadState = false;
    Flags.bDevDebugMode = DefaultFlags.bDevDebugMode = false;
    Flags.bStickyWindowPosition = DefaultFlags.bStickyWindowPosition = false;
    Flags.bReuseWindow = DefaultFlags.bReuseWindow = false;
    Flags.bSingleFileInstance = DefaultFlags.bSingleFileInstance = true;
    Flags.MultiFileArg = DefaultFlags.MultiFileArg = false;
    Flags.RelativeFileMRU = DefaultFlags.RelativeFileMRU = true;
    Flags.PortableMyDocs = DefaultFlags.PortableMyDocs = Flags.RelativeFileMRU;
    Flags.NoFadeHidden = DefaultFlags.NoFadeHidden = false;
    Flags.ToolbarLook = DefaultFlags.ToolbarLook = IsWindowsXPSP3OrGreater() ? 1 : 2;
    Flags.SimpleIndentGuides = DefaultFlags.SimpleIndentGuides = false;
    Flags.NoHTMLGuess = DefaultFlags.NoHTMLGuess = false;
    Flags.NoCGIGuess = DefaultFlags.NoCGIGuess = false;
    Flags.NoFileVariables = DefaultFlags.NoFileVariables = false;
    Flags.SaveBlankNewFile = DefaultFlags.SaveBlankNewFile = true;
    Flags.ShellUseSystemMRU = DefaultFlags.ShellUseSystemMRU = true;
    Flags.PrintFileAndLeave = DefaultFlags.PrintFileAndLeave = 0;
    Flags.bPreserveFileModTime = DefaultFlags.bPreserveFileModTime = false;
    Flags.bDoRelaunchElevated = DefaultFlags.bDoRelaunchElevated = false;
    Flags.bSearchPathIfRelative = DefaultFlags.bSearchPathIfRelative = false;

    Flags.bSettingsFileSoftLocked = DefaultFlags.bSettingsFileSoftLocked = false;

    Settings.EFR_Data.chFindPattern = StrgCreate(NULL);
    Settings.EFR_Data.chReplaceTemplate = StrgCreate(NULL);
    Defaults.EFR_Data.chFindPattern = StrgCreate(NULL);
    Defaults.EFR_Data.chReplaceTemplate = StrgCreate(NULL);

    Settings.OpenWithDir = Path_Allocate(NULL);
    Defaults.OpenWithDir = Path_Allocate(NULL);
    Settings.FavoritesDir = Path_Allocate(NULL);
    Defaults.FavoritesDir = Path_Allocate(NULL);

    Settings2.DefaultDirectory = Path_Allocate(NULL);
    Settings2.FileBrowserPath = Path_Allocate(NULL);
    Settings2.GrepWinPath = Path_Allocate(NULL);
    Settings2.AdministrationTool = Path_Allocate(NULL);

    Settings2.WebTemplate1 = StrgCreate(NULL);
    Settings2.WebTemplate2 = StrgCreate(NULL);
    Settings2.HyperlinkShellExURLWithApp = StrgCreate(NULL);
    Settings2.HyperlinkShellExURLCmdLnArgs = StrgCreate(NULL);
    Settings2.FileDlgFilters = StrgCreate(NULL);

    FocusedView.HideNonMatchedLines = false;
    FocusedView.CodeFoldingAvailable = false;
    FocusedView.ShowCodeFolding = true;

    FileWatching.FileWatchingMode = FWM_DONT_CARE;
    FileWatching.MonitoringLog = false;

    Paths.CurrentFile = Path_Allocate(NULL);
    Paths.ModuleDirectory = Path_Allocate(NULL);
    Paths.WorkingDirectory = Path_Allocate(NULL);
    Paths.IniFile = Path_Allocate(NULL);
    Paths.IniFileDefault = Path_Allocate(NULL);

    // --- unstructured globals ---

    g_tchToolbarBitmap = Path_Allocate(NULL);
    g_tchToolbarBitmapHot = Path_Allocate(NULL);
    g_tchToolbarBitmapDisabled = Path_Allocate(NULL);

    // --- dynamicly created globals ---

    WCHAR tchIndex[16] = { L'\0' };
    StringCchPrintf(tchIndex, COUNTOF(tchIndex), L"%i", s_tbbMainWnd[0].iBitmap + 1);
    StringCchCopy(TBBUTTON_DEFAULT_IDS, COUNTOF(TBBUTTON_DEFAULT_IDS), tchIndex);
    assert(TBBUTTON_LAST_DEFAULT <= COUNTOF(s_tbbMainWnd));
    for (int i = 1; i < TBBUTTON_LAST_DEFAULT; ++i) {
        if (s_tbbMainWnd[i].idCommand) {
            StringCchPrintf(tchIndex, COUNTOF(tchIndex), L" %i", s_tbbMainWnd[i].iBitmap + 1);
            StringCchCat(TBBUTTON_DEFAULT_IDS, COUNTOF(TBBUTTON_DEFAULT_IDS), tchIndex);
        }
        else {
            StringCchCat(TBBUTTON_DEFAULT_IDS, COUNTOF(TBBUTTON_DEFAULT_IDS), L" 0");
        }
    }

    // --- static locals ---

    s_hpthRelaunchElevatedFile = Path_Allocate(NULL);

    ThemesItems_Init();
    s_hstrCurrentFindPattern = StrgCreate(NULL);

    s_pthArgFilePath = Path_Allocate(NULL);
    s_pthCheckFilePath = Path_Allocate(NULL);

    // don't allow empty extensions settings => use default ext
    Style_InitFileExtensions();
#endif
}


//=============================================================================
//
//  UpdateLineNumberWidth()
//
//
void UpdateLineNumberWidth()
{
#if 0
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
        iLineMarginWidthFit = (int)SendScintillaMessage(SCI_TEXTWIDTH, STYLE_LINENUMBER, (LPARAM)"_99999");

        if (iLineMarginWidthNow != iLineMarginWidthFit) 
        {
            //SendMessage(hwndEdit,SCI_SETMARGINWIDTHN,0,0);
            //SendMessage(hwndEdit, SCI_SETMARGINWIDTHN, 0, iLineMarginWidthFit);
            SendScintillaMessage(SCI_SETMARGINWIDTHN, 0, iLineMarginWidthFit);
        }
    }
    else
        SendScintillaMessage(SCI_SETMARGINWIDTHN, 0, 0);
#endif
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
