#include "WinApp.h"
#include "Engine.h"
#include <windowsx.h>


WinApp::WinApp()
	:mWidth(0),
	mHeight(0),
	mCaption(NULL),
	mHWND(NULL)
{
}

WinApp::~WinApp()
{
}

void WinApp::Create(HINSTANCE hInstance, int nCmdShow, int width, int height, LPCSTR caption)
{
	mWidth		= width;
	mHeight		= height;
	mCaption	= caption;

	RegisterClass(hInstance);

	Init(hInstance,nCmdShow);
}

int	WinApp::GetWidth()
{
	return mWidth;
}

int	WinApp::GetHeight()
{
	return mHeight;
}

HWND WinApp::GetHwnd()
{
	return mHWND;
}

WORD WinApp::RegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WinApp::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= mCaption;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

bool WinApp::Init(HINSTANCE hInstance, int nCmdShow)
{
	mHWND = CreateWindow(
		mCaption, 
		mCaption, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		0, 
		mWidth,
		mHeight, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	if (!mHWND)
		return false;

	ShowWindow(mHWND, nCmdShow);

	return true;
}

LRESULT CALLBACK  WinApp::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}