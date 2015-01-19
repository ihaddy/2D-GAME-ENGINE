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

//This needs to be researched more, the syntax is atrocious, there could be a better way to implement
#define SETCOLOR_ARGB(a,r,g,b) \
	((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))


//class prototype, built upon in graphics.cpp

class Graphics{

	//these are private, and only the graphics class itself can access them
	//ALTHOUGH ALL PRIVATE VARIABLES ARE TRANSFERRED TO ANY INHERITANCES, THEY ARE JUST NO EDITABLE IN THE INHERITANCE
	// on a final note, the private members ARE accessible from WITHIN the public members of the graphics class

private: 

// The pointers for directX
	LP_3D	direct2d;
	LP_3DDEVICE device3d;
	D3DPRESENT_PARAMETERS d3dpp;

	//other varriables needed

	HRESULT	result; //This is the standard window handler return code
	HWND	hwnd; //Standard windows handler
	bool	fullscreen; //undefined initially
	int		width; //undefined initially, and then filled in from the constructor in graphics.cpp
	int		height; // undefined intially, and then filled in from the constructor in graphics.cpp

	//this part is supposedly for internal engine use only. "no user serviceable parts inside.)
	//Initialization of the D3D presentation parameters

	void initD3Dpp();

	//These parts of the class are, meaning they are accessible to anything
public:

	//The constructor 

	Graphics();

	//The Destructor

	virtual ~Graphics();

	//How to release the direct3d and device3d

	void releaseAll();

	//How to initialize the DirectX graphics
	//If there's an error, it'll throw GameError
	// hw = handle to the window
	// width is in PIXELS
	// height in PIXELS
	//fullscreen = true for yes, false for windowed
	//note the void means that the function does NOT return a value.
	void initialize(HWND hw, int width, int height, bool fullscreen);

	//Display the offscreen backbuffer to the screen, similar to "flipping the screen"

	HRESULT showBackbuffer();


	
};

#endif