// Winmain.cpp

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_ESCAPE 0x1B
#define VK_SPACE 0x20
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28


#define VK_LSHIFT 0xA0
#define VK_RSHIFT 0xA1
#define VK_LCONTROL 0xA2
#define VK_RCONTROL 0xA3
#define VK_LMENU 0xA4
#define VK_RMENU 0xA5

// Numpad keys
#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69

//Function Keys
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B



//Function Prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HINSTANCE, int);

LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable

HINSTANCE hinst;
HDC hdc;
TCHAR ch = ' ';
RECT rect;
PAINTSTRUCT ps;


//Constants

const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello World";
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;


//==========================================================
// Starting point for a Windows Application
// Parameters are:
// hInstance = Handle to the current instance of the application
// hPrevInstance = Always NULL, obsolete Parameter
// lpCmdLine = Pointer to null-terminated string of command line arguments
// nCmdShow = specifies how the window is to be shown

//===========================================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{
	//Declares an instance of the MSG class i think
	MSG msg;

	//Create the Window

	if (!CreateMainWindow(hInstance, nCmdShow))
		return false;

	//Main Message Loop

	int done = 0;
	while (!done)
	{
		//PeekMessage is used instead of GetMessage because Getmessage halts and waits for a reply whereas PeekMessage can continue without a reply

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Look for Quit Message

			if (msg.message == WM_QUIT)
				done = 1;
			//Decode and Pass messages on to WinProc (Windows Processing)

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
	}
	return msg.wParam;


}

//================================
// Window event callback function
//================================

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	switch (msg)
	{
	case WM_DESTROY:
		// Tell Windows to kill this program
		PostQuitMessage(0);
		return 0;

	case WM_CHAR: // A character was entered by the keyboard
		switch (wParam)		// the character is in wParam
		{
		case 0x08:			// Backspace
		case 0x09:			// Tab
		case 0x0A:			//LineFeed
		case 0x0D:			//Carriage return
		case 0x1B:			// Escape
			MessageBeep((UINT)-1);		// Beep but do not display
			return 0;
		default:
			ch = (TCHAR)wParam;		// Get the character
			InvalidateRect(hWnd, NULL, TRUE);  // Force WM_PAINT
			return 0;
		}
	case WM_PAINT:					// Window needs to be redrawn
		hdc = BeginPaint(hWnd, &ps); // Get Handle to device context
		GetClientRect(hWnd, &rect);	 // Get the Window Rectangle

		// Displaying the actual character

		TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);
		EndPaint(hWnd, &ps);
		return 0;


	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_KEYDOWN:		//KEY DOWN
		vkKeyes(wParam) = true;
		switch (wParam)
		{
		case VK_SHIFT:								// Shift Key
			nVirtKey = GetKeyState(VK_LSHIFT);		//Get State of Left

			if (nVirtKey & SHIFTED)					// If Left Shift
				vkKeys(VK_LSHIFT) = true;
			nVirtKey = GetKeyState(VK_RSHIFT);		// Get State of Right Shift

			if (nVirtKey & SHIFTED)
				vkKeys(VK_RSHIFT) = true;
			break;
		case VK_CONTROL: // Control key
			nVirtKey = GetKeyState(VK_LCONTROL);
			if (nVirtKey & SHIFTED)					// Left control
				vkKeys(VK_LCONTROL) = true;
			nVirtKey = GetKeyState(VK_RCONTROL);
			if (nVirtKey & SHIFTED)					// Right Control
				vkKeys(VK_RCONTROL) = true;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);			// FORCE WM_PAINT
		return 0;
		break;
	case WM_KEYUP:								// Key UP
		vkKeys(wParam) = false;

		switch (wParam)
		{
		case VK_SHIFT:
			nVirtKey = GetKeyState(VK_LSHIFT);
			if ((nVirtKey & SHIFTED) == 0) //if LEFT shift key UP
				vkKeys(VK_LCONTROL) = false;
			nVirtKey = GetKeyState(VK_RSHIFT); 
			if ((nVirtKey & SHIFTED) == 0) // if RIGHT shift key UP
				vkKeys(VK_RSHIFT) = false;
			break;
		case VK_CONTROL:
			nVirtKey = GetKeyState(VK_LCONTROL);
			if ((nVirtKey & SHIFTED) == 0) // IF LEFT CONTROL 
				vkKeys(VK_LCONTROL) = false;
			nVirtKey = GetKeyState(VK_RCONTROL);
			if ((nVirtKey &SHIFTED) == 0)	//If RIGHT control up
				vkKeys[VK_RCONTROL] = false;
			break;

		}
	}

}

//================================
// Create the Window
// Returns: false on error
//================================

bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

	// Fill in the window class structure with parameters that describe the main window

	wcx.cbSize = sizeof(wcx);	// Size of structure
	wcx.style = CS_HREDRAW | CS_VREDRAW; // Redraw if size changes
	wcx.lpfnWndProc = WinProc; // Points to windows procedure WinProc
	wcx.cbClsExtra = 0; // No extra class memory
	wcx.cbWndExtra = 0;	// no extra window memory
	wcx.hInstance = hInstance; //Handle to the current instance
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW); // Predefined arrow
	//	BACKGROUND BRUSH
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL; //name of the menu resource
	wcx.lpszClassName = CLASS_NAME; // name of the window class
	wcx.hIconSm = NULL;			//Small class icon

	//REGISTERING THE WINDOW CLASS
	// RegisterClassEx returns 0 on error

	if (RegisterClassEx(&wcx) == 0) // If error
		return false;

	//CREATING THE WINDOW

	hwnd = CreateWindow(
		CLASS_NAME,		//Name of the window class
		APP_TITLE,		// Tite Bar text
		WS_OVERLAPPEDWINDOW,	//Window style
		CW_USEDEFAULT,			// Default horizontal position of window
		CW_USEDEFAULT,			// Default vertical position of window
		WINDOW_WIDTH,			// Width of Window
		WINDOW_HEIGHT,			// Height of the window
		(HWND)NULL,			// No parent window
		(HMENU)NULL,			// No menu
		hInstance,				// Handle to application instance
		(LPVOID)NULL);			// No window parameters

		//If there was an error creating the window
		if (!hwnd)
			return false;

	//show the window

	ShowWindow(hwnd, nCmdShow);

	// Send a WM_paint message to the window procedure

	UpdateWindow(hwnd);
	return true;

}