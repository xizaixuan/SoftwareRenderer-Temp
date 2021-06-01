#include "Matrix.h"
#include <memory.h>

Matrix::Matrix(void)
	: r0(1.0f, 0.0f, 0.0f, 0.0f)
	, r1(0.0f, 1.0f, 0.0f, 0.0f)
	, r2(0.0f, 0.0f, 1.0f, 0.0f)
	, r3(0.0f, 0.0f, 0.0f, 1.0f)
{
}

Matrix::Matrix(float4 r0, float4 r1, float4 r2, float4 r3)
	: r0(r0)
	, r1(r1)
	, r2(r2)
	, r3(r3)
{
}


Matrix::Matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13, 
	float m20, float m21, float m22, float m23, 
	float m30, float m31, float m32, float m33)
	: r0(m00, m01, m02, m03)
	, r1(m10, m11, m12, m13)
	, r2(m20, m21, m22, m23)
	, r3(m30, m31, m32, m33)
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
	return Matrix(mat.r0 * a, mat.r1 * a, mat.r2 * a, mat.r3 * a);
}

void Matrix::Identity()
{
	r0 = r1 = r2 = r3 = Float4(0.0f, 0.0f, 0.0f, 0.0f);
	r0.x = r1.y = r2.z = r3.w = 1.0f;
}

void Matrix::Set(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	r0 = float4(m00, m01, m02, m03);
	r1 = float4(m10, m11, m12, m13);
	r2 = float4(m20, m21, m22, m23);
	r3 = float4(m30, m31, m32, m33);
}