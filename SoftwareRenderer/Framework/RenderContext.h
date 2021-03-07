#pragma once
/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   渲染上下文
/// \author  xizaixuan
/// \date    2021-03
/////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

class RenderContext
{
public:
	/// brief 绘制直线
	static void DrawLine(int startX, int startY, int endX, int endY, DWORD color);
};