#pragma once
/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   ��Ⱦ������
/// \author  xizaixuan
/// \date    2021-03
/////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

class RenderContext
{
public:
	/// brief ����ֱ��
	static void DrawLine(int startX, int startY, int endX, int endY, DWORD color);
};