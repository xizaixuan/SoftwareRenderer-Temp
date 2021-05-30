/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   Па»ъ
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Mathematics\Float3.h"
#include "Mathematics\Matrix.h"

class Camera
{
public:
	void BuildViewMatrix();

	void BuildPerspectiveMatrix();

	void BuildViewPortMatrix();

private:
	float3 m_Position;
	float3 m_Target;
	float3 m_Forward;
	float3 m_Up;
	float3 m_Right;

	float m_FieldOfView;
	float m_NearPlane;
	float m_FarPlane;
	float m_Aspect;

	Matrix m_ViewMatrix;
	Matrix m_PerspectiveMatrix;
	Matrix m_ViewPortMatrix;
};

#endif