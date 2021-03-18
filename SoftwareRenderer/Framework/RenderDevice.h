/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   ������
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderDevice_H_
#define _RenderDevice_H_

#include <windows.h>
#include <D2D1_1.h>
#include "..\Utility\Singleton.h"


#define SAFE_RELEASE(P) if(P != nullptr){P->Release() ; P = nullptr;}
#define SAFE_DELETE(P) if(P != nullptr){delete P; P = nullptr;}
#define SAFE_DELETE_ARRAY(P) if(P != nullptr){delete[] P; P = nullptr;}

class RenderDevice :public Singleton <RenderDevice>
{
	SINGLETON_DEFINE(RenderDevice)
private:
	RenderDevice(void);
	~RenderDevice(void);

public:
	/// \brief ��ʼ����Ⱦ�豸
	void InitRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight);

	/// brief ��Ⱦ��ʼ
	void RenderBegin();

	/// brief ��Ⱦ����
	void RenderEnd();

	/// \brief ����Buffer
	void RenderBuffer();
	
	/// \brief ����color
	void DrawPixel(DWORD x, DWORD y, DWORD color);

private:
	///	���ڿ��
	DWORD	m_WindowWidth;

	///	���ڸ߶�
	DWORD	m_WindowHeight;

	///	���ھ��
	HWND	m_HWND;

	/// ʵ������
	ID2D1Factory*			m_Factory;

	/// ��ȾĿ��
	ID2D1HwndRenderTarget*	m_RenderTarget;

	/// λͼ
	ID2D1Bitmap*			m_Bitmap;

	/// ��Ⱦ����
	DWORD*					m_DataBuffer;
};

#endif
