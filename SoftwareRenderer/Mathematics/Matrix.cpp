#include "Matrix.h"
#include <memory.h>

Matrix::Matrix(void)
	: c0(0.0f, 0.0f, 0.0f, 0.0f)
	, c1(0.0f, 0.0f, 0.0f, 0.0f)
	, c2(0.0f, 0.0f, 0.0f, 0.0f)
	, c3(0.0f, 0.0f, 0.0f, 0.0f)
{
}

Matrix::Matrix(float4 c0, float4 c1, float4 c2, float4 c3)
	: c0(c0)
	, c1(c1)
	, c2(c2)
	, c3(c3)
{
}


Matrix::Matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13, 
	float m20, float m21, float m22, float m23, 
	float m30, float m31, float m32, float m33)
	: c0(m00, m10, m20, m30)
	, c1(m01, m11, m21, m31)
	, c2(m02, m12, m22, m32)
	, c3(m03, m13, m23, m33)
{
}

Matrix::~Matrix(void)
{
}

Matrix& Matrix::operator =(const Matrix& a)
{
	memcpy((void*)(this), (void*)(&a), sizeof(Matrix));

	return *this;
}

Matrix Matrix::operator *(const Matrix& a) const
{
	Matrix mat = (*this);
	return Matrix(a.c0 * mat, a.c1 * mat, a.c2 * mat, a.c3 * mat);
}

void Matrix::Identity()
{
	c0 = c1 = c2 = c3 = Float4(0.0f, 0.0f, 0.0f, 0.0f);
	c0.x = c1.y = c2.z = c3.w = 1.0f;
}

void Matrix::Set(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	c0 = float4(m00, m10, m20, m30);
	c1 = float4(m01, m11, m21, m31);
	c2 = float4(m02, m12, m22, m32);
	c3 = float4(m03, m13, m23, m33);
}