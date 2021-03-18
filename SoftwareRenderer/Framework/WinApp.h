/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   ���ڹ�����
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef WinApp_H_
#define WinApp_H_

#include <windows.h>
#include "..\Utility\Singleton.h"

class WinApp : public Singleton<WinApp>
{
	SINGLETON_DEFINE(WinApp)
private:
	WinApp();
	~WinApp();

public:
	/// \brief ��������
	void	Create(HINSTANCE hInstance, int nCmdShow, int width, int height, LPCSTR caption);	

	/// \brief ��ȡ���ڵĿ�
	int		GetWidth();

	/// \brief ��ȡ���ڵĳ�
	int		GetHeight();

	/// \brief ��ȡ���ھ��
	HWND	GetHwnd();

private:
	/// \brief ����ע��
	WORD	RegisterClass(HINSTANCE hInstance);

	/// \brief ��ʼ��
	bool	Init(HINSTANCE hInstance, int nCmdShow);

	/// \brief ��Ϣ�ص�����
	static	LRESULT CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	///	��������
	LPCSTR	m_Caption;

	///	���ڸ߶�
	int		m_Height;

	///	���ڿ��
	int		m_Width;

	///	���ھ��
	HWND	m_HWND;
};

#endif