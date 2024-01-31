#ifndef _zpad_notepad2_h_
#define _zpad_notepad2_h_

#ifdef __cplusplus
extern "C" {
#endif

	BOOL FileLoad(BOOL bDontSave, BOOL bNew, BOOL bReload, BOOL bNoEncDetect, LPCWSTR lpszFile);

	void UpdateLineNumberWidth();

#ifdef __cplusplus
}
#endif

#endif // _zpad_notepad2_h_