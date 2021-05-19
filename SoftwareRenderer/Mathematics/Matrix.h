/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ����
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Matrix_H_
#define _Matrix_H_

#include "Float4.h"

class Matrix
{
public:
	/// \brief Ĭ�Ϲ��캯��
	Matrix(void);

	/// \brief ���������캯��
	Matrix(float4 c0, float4 c1, float4 c2, float4 c3);

	Matrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// \brief ��������
	~Matrix(void);

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Matrix& operator =(const Matrix& a);

	/// \brief ���ض�Ԫ"*"�����
	Matrix operator *(const Matrix& a) const;

public:
	/// \brief ��Ϊ��λ����
	void Identity();

	void Set(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

public:
	float4 c0;
	float4 c1;
	float4 c2;
	float4 c3;
};

#endif
