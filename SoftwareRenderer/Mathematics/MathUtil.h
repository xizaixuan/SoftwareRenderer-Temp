/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ѧ�������㷨
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _MathUtil_H_
#define _MathUtil_H_

#include <math.h>
#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "Matrix.h"
#include <limits>

namespace MathUtil
{
	const float EPSILON = std::numeric_limits<float>::epsilon();
	const float PI = ((float)3.141592654f);

	float AngelToRadian(float ang);
	float RadianToAngel(float rads);

	/// brief ����������
	float Length(const float2& v);
	float Length(const float3& v);
	float Length(const float4& v);

	/// brief ��λ��
	float2 Normalize(float2& v);
	float3 Normalize(float3& v);
	float4 Normalize(float4& v);

	/// brief ���������Ĳ��
	float2 Cross(const float2& a, const float2& b);
	float3 Cross(const float3& a, const float3& b);

	/// brief �Ƚ������������Ƿ����
	bool IsEqual(float a, float b);

	Matrix Inverse(Matrix mat);
}

#endif
