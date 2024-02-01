#ifndef _ZPAD_NOTEPAD3_H_
#define _ZPAD_NOTEPAD3_H_

#ifdef __cplusplus
extern "C" {
#endif

	BOOL FileLoad(BOOL bDontSave, BOOL bNew, BOOL bReload, BOOL bNoEncDetect, LPCWSTR lpszFile);

	void UpdateLineNumberWidth();

	void InitGlobals();
#ifdef __cplusplus
}
#endif

#endif // _ZPAD_NOTEPAD3_H_