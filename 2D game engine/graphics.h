#ifndef _GRAPHICS_H //literally, if not defined, then define
#define _GRAPHICS_H
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG //literally, IF DEFINED, then define
#define D3D_DEBUG_INFO
#endif

#include <d3d.h>
//programmer defined headers, as indicated by the " instead of the <> characters around them
#include "constants.h"
#include "gameError.h"


//These are DirectX pointer types

#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D		LPDIRECT3D9

// Color Dfines

#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
	((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

class Graphics{};
