// ZPad.h
#ifndef _ZPAD_H_
#define _ZPAD_H_

#include <stdint.h>
#include <assert.h>

#include "scintilla/Scintilla.h"

#define S8      int8_t
#define S16     int16_t
#define S32     int32_t
#define S64     int64_t

#define U8      uint8_t
#define U16     uint16_t
#define U32     uint32_t
#define U64     uint64_t

#define ZPAD_STATUS_NONE										0x0000000000000000
#define ZPAD_STATUS_SHOWNUMBERLINES								0x0000000000000001

#define GetShowNumberLines(s)	(s & ZPAD_STATUS_SHOWNUMBERLINES)
#define SetShowNumberLines(s)	(s |= ZPAD_STATUS_SHOWNUMBERLINES)
#define XORShowNumberLines(s)	(s ^= ZPAD_STATUS_SHOWNUMBERLINES)

#ifdef __cplusplus
extern "C" {
#endif

	extern U64      g_statusU64;

	extern HINSTANCE g_hInstance;

	extern U64 (*g_fnScintilla)(void*, UINT, WPARAM, LPARAM);
	extern void* g_ptrScintilla;

	U64 SendScintillaMessage(UINT, WPARAM, LPARAM);

#ifdef __cplusplus
}
#endif

#pragma comment(lib, "imm32.lib")

#endif // _ZPAD_H_
