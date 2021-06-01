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
	Camera();

	void BuildViewMatrix();

	void BuildPerspectiveMatrix();

	void BuildViewPortMatrix();

	Matrix GetViewMatrix();

	Matrix GetPerspectiveMatrix();

	Matrix GetViewPortMatrix();

public:
	float3 Position;
	float3 Target;
	float3 Forward;
	float3 Up;
	float3 Right;

	float FieldOfView;
	float NearPlane;
	float FarPlane;
	float Aspect;

	Matrix ViewMatrix;
	Matrix PerspectiveMatrix;
	Matrix ViewPortMatrix;
};

#endif