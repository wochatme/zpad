// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

const U8 txt[] = { 0xE7,0x8B,0xA1,0xE5,0x85,0x94,0x0A,0xE4,0xB8,0x89,0xE7,0xAA,0x9F,0};

class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	//CView m_view;
	CCommandBarCtrl m_CmdBar;
	// HWND m_hWndScintilla = nullptr;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		//return m_view.PreTranslateMessage(pMsg);
		 return FALSE;
	}

	virtual BOOL OnIdle()
	{
		UIUpdateToolBar();
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDMZPAD_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(IDMZPAD_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(IDMZPAD_FILE_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(IDMZPAD_VIEW_LINENUMBERS, OnViewLineNumbers)
		COMMAND_ID_HANDLER(IDMZPAD_VIEW_FONT, OnViewFont)
		COMMAND_ID_HANDLER(IDMZPAD_FILE_NEWWINDOW, OnFileNewWindow)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(IDMZPAD_HELP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// create command bar window
		HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		// attach menu
		m_CmdBar.AttachMenu(GetMenu());
		// load command bar images
		m_CmdBar.LoadImages(IDR_MAINFRAME);
		// remove old menu
		SetMenu(NULL);

		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(hWndCmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		CreateSimpleStatusBar();

		//m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

		// m_hWndScintilla = nullptr;
		m_hWndClient = ::CreateWindowExW(0, L"Scintilla", L"", 
										WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL, 
										0, 0, 2, 2, m_hWnd, NULL, g_hInstance, NULL);

		if (::IsWindow(m_hWndClient))
		{
			// m_hWndScintilla = m_hWndClient;
			g_fnScintilla = (U64 (__cdecl*)(void*, UINT, WPARAM, LPARAM))SendMessage(m_hWndClient, SCI_GETDIRECTFUNCTION, 0, 0);
			ATLASSERT(g_fnScintilla);
			g_ptrScintilla = (void*)SendMessage(m_hWndClient, SCI_GETDIRECTPOINTER, 0, 0);
			ATLASSERT(g_ptrScintilla);

			//::SendMessage(m_hWndClient, SCI_SETWRAPMODE, SC_WRAP_WORD, 0);
			g_fnScintilla(g_ptrScintilla, SCI_SETTECHNOLOGY, SC_TECHNOLOGY_DIRECTWRITE, 0);
			g_fnScintilla(g_ptrScintilla, SCI_SETWRAPMODE, SC_WRAP_WORD, 0);
			//g_fnScintilla(g_ptrScintilla, SCI_STYLESETFONT, STYLE_DEFAULT, (LPARAM)"Courier New");
			g_fnScintilla(g_ptrScintilla, SCI_STYLESETFONT, STYLE_DEFAULT, (LPARAM)"Microsoft YaHei");
			g_fnScintilla(g_ptrScintilla, SCI_STYLESETSIZE, STYLE_DEFAULT, (LPARAM)11);

			SendScintillaMessage(SCI_SETTEXT, 0, (LPARAM)txt);
		}

		UIAddToolBar(hWndToolBar);
		UISetCheck(ID_VIEW_TOOLBAR, 1);
		UISetCheck(ID_VIEW_STATUS_BAR, 1);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		bHandled = FALSE;
		return 1;
	}

	LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		FileLoad(FALSE, FALSE, FALSE, FALSE, L"");
		return 0;
	}

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	
	LRESULT OnViewLineNumbers(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		UpdateLineNumberWidth();
		return 0;
	}

	LRESULT OnViewFont(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: add code to initialize document
		// MessageBox(_T("got!"), L"ZPad", MB_OK);
		// Style_SetDefaultFont(m_hWndClient);
		// UpdateStatusbar();
		// UpdateLineNumberWidth();
		return 0;
	}

	LRESULT OnFileNewWindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::PostThreadMessage(_Module.m_dwMainThreadID, WM_USER, 0, 0L);
		return 0;
	}

	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		static BOOL bVisible = TRUE;	// initially visible
		bVisible = !bVisible;
		CReBarCtrl rebar = m_hWndToolBar;
		int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
		rebar.ShowBand(nBandIndex, bVisible);
		UISetCheck(ID_VIEW_TOOLBAR, bVisible);
		UpdateLayout();
		return 0;
	}

	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
		::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
		UpdateLayout();
		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		//FileLoad(FALSE, TRUE, FALSE, FALSE, L"");
		U64 uRet = 0;
		U64 wp;
		char text[128] = { 0 };

		wp = SendScintillaMessage(SCI_GETTEXT, 0, 0); /// get the text length
		uRet = SendScintillaMessage(SCI_GETTEXT, wp, (intptr_t)text); /// get the text

		uRet = SendScintillaMessage(SCI_SETTEXT, 0, (LPARAM)txt); /// set the text

		return 0;
	}

};
