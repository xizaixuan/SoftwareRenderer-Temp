#include "WinApp.h"
#include "Engine.h"
#include <windowsx.h>


WinApp::WinApp()
	:m_Width(0),
	m_Height(0),
	m_Caption(NULL),
	m_HWND(NULL)
{
}

WinApp::~WinApp()
{
}

void WinApp::Create(HINSTANCE hInstance, int nCmdShow, int width, int height, LPCSTR caption)
{
	m_Width		= width;
	m_Height		= height;
	m_Caption	= caption;

	RegisterClass(hInstance);

	Init(hInstance,nCmdShow);
}

int	WinApp::GetWidth()
{
	return m_Width;
}

int	WinApp::GetHeight()
{
	return m_Height;
}

HWND WinApp::GetHwnd()
{
	return m_HWND;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_MOUSEMOVE:
		Engine::GetSingletonPtr()->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

WORD WinApp::RegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= m_Caption;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

bool WinApp::Init(HINSTANCE hInstance, int nCmdShow)
{
	m_HWND = CreateWindow(
		m_Caption, 
		m_Caption, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		0, 
		m_Width,
		m_Height, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	if (!m_HWND)
		return false;

	ShowWindow(m_HWND, nCmdShow);

	return true;
}