# The Internals of Scintilla

Call stack:
```
	zpad-win64.exe!Scintilla::Internal::SurfaceD2D::DrawTextCommon(Scintilla::Internal::PRectangle rc, const Scintilla::Internal::Font * font_, double ybase, std::basic_string_view<char,std::char_traits<char>> text, int codePageOverride, unsigned int fuOptions) Line 2363	C++
 	zpad-win64.exe!Scintilla::Internal::SurfaceD2D::DrawTextTransparent(Scintilla::Internal::PRectangle rc, const Scintilla::Internal::Font * font_, double ybase, std::basic_string_view<char,std::char_traits<char>> text, Scintilla::Internal::ColourRGBA fore) Line 2428	C++
 	zpad-win64.exe!Scintilla::Internal::EditView::DrawForeground(Scintilla::Internal::Surface * surface, const Scintilla::Internal::EditModel & model, const Scintilla::Internal::ViewStyle & vsDraw, const Scintilla::Internal::LineLayout * ll, int xStart, Scintilla::Internal::PRectangle rcLine, int subLine, __int64 lineVisible, Scintilla::Internal::Range lineRange, __int64 posLineStart, std::optional<Scintilla::Internal::ColourRGBA> background) Line 2249	C++
 	zpad-win64.exe!Scintilla::Internal::EditView::DrawLine(Scintilla::Internal::Surface * surface, const Scintilla::Internal::EditModel & model, const Scintilla::Internal::ViewStyle & vsDraw, const Scintilla::Internal::LineLayout * ll, __int64 line, __int64 lineVisible, int xStart, Scintilla::Internal::PRectangle rcLine, int subLine, Scintilla::Internal::DrawPhase phase) Line 2440	C++
 	zpad-win64.exe!Scintilla::Internal::EditView::PaintText(Scintilla::Internal::Surface * surfaceWindow, const Scintilla::Internal::EditModel & model, const Scintilla::Internal::ViewStyle & vsDraw, Scintilla::Internal::PRectangle rcArea, Scintilla::Internal::PRectangle rcClient) Line 2614	C++
 	zpad-win64.exe!Scintilla::Internal::Editor::Paint(Scintilla::Internal::Surface * surfaceWindow, Scintilla::Internal::PRectangle rcArea) Line 1907	C++
 	zpad-win64.exe!Scintilla::Internal::ScintillaWin::PaintDC(HDC__ * hdc) Line 1025	C++
 	zpad-win64.exe!Scintilla::Internal::ScintillaWin::WndPaint() Line 1059	C++
 	zpad-win64.exe!Scintilla::Internal::ScintillaWin::WndProc(Scintilla::Message iMessage, unsigned __int64 wParam, __int64 lParam) Line 2041	C++
 	zpad-win64.exe!Scintilla::Internal::ScintillaWin::SWndProc(HWND__ * hWnd, unsigned int iMessage, unsigned __int64 wParam, __int64 lParam) Line 3851	C++
 	[External Code]	
 	zpad-win64.exe!WTL::CMessageLoop::Run() Line 666	C++
 	zpad-win64.exe!CZPadThreadManager::RunThread(void * lpData) Line 63	C++
 	[External Code]	
```
