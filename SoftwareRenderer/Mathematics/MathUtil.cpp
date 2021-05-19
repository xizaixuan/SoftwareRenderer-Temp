#include "MathUtil.h"

float MathUtil::AngelToRadian(float ang)
{
	return ((ang)*PI / 180.0f);
}

float MathUtil::RadianToAngel(float rads)
{
	return ((rads)*180.0f / PI);
}

float MathUtil::Length(const float2& v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

float MathUtil::Length(const float3& v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

float MathUtil::Length(const float4& v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

float2 MathUtil::Normalize(float2 v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > EPSILON)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
	}

	return v;
}

float3 MathUtil::Normalize(float3 v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > EPSILON)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
		v.z = v.z*lengthInv;
	}

	return v;
}

float4 MathUtil::Normalize(float4 v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > EPSILON)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
		v.z = v.z*lengthInv;
	}

	return v;
}

float2 MathUtil::Cross(const float2& a, const float2& b)
{
	return float2(
		a.y*b.x - a.x*b.y,
		a.x*b.y - a.y*b.x);
}

float3 MathUtil::Cross(const float3& a, const float3& b)
{
	return float3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
}

bool MathUtil::IsEqual(float a, float b)
{
	return (fabs(a - b) <= EPSILON);
}

Matrix MathUtil::Inverse(Matrix mat)
{
	Matrix imat;

	float det = (
		mat.c0.x * (mat.c1.y * mat.c2.z - mat.c1.z * mat.c2.y) -
		mat.c0.y * (mat.c1.x * mat.c2.z - mat.c1.z * mat.c2.x) +
		mat.c0.z * (mat.c1.x * mat.c2.y - mat.c1.y * mat.c2.x));

	// 检查除零
	if (fabs(det) > MathUtil::EPSILON)
	{
		float det_inv = 1.0f / det;

		imat.c0.x = det_inv * (mat.c1.y * mat.c2.z - mat.c1.z * mat.c2.y);
		imat.c0.y = -det_inv * (mat.c0.y * mat.c2.z - mat.c0.z * mat.c2.y);
		imat.c0.z = det_inv * (mat.c0.y * mat.c1.z - mat.c0.z * mat.c1.y);
		imat.c0.w = 0.0f;

		imat.c1.x = -det_inv * (mat.c1.x * mat.c2.z - mat.c1.z * mat.c2.x);
		imat.c1.y = det_inv * (mat.c0.x * mat.c2.z - mat.c0.z * mat.c2.x);
		imat.c1.z = -det_inv * (mat.c0.x * mat.c1.z - mat.c0.z * mat.c1.x);
		imat.c1.w = 0.0f;

		imat.c2.x = det_inv * (mat.c1.x * mat.c2.y - mat.c1.y * mat.c2.x);
		imat.c2.y = -det_inv * (mat.c0.x * mat.c2.y - mat.c0.y * mat.c2.x);
		imat.c2.z = det_inv * (mat.c0.x * mat.c1.y - mat.c0.y * mat.c1.x);
		imat.c2.w = 0.0f;

		imat.c3.x = -(mat.c3.x * mat.c0.x + mat.c3.y * mat.c1.x + mat.c3.z * mat.c2.x);
		imat.c3.y = -(mat.c3.x * mat.c0.y + mat.c3.y * mat.c1.y + mat.c3.z * mat.c2.y);
		imat.c3.z = -(mat.c3.x * mat.c0.z + mat.c3.y * mat.c1.z + mat.c3.z * mat.c2.z);
		imat.c3.w = 1.0f;
	}

	return mat;
}
