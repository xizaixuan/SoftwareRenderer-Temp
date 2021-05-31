#include "Float4.h"
#include "Matrix.h"
#include "Float3.h"

Float4::Float4(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(1.0f)
{
}

Float4::Float4(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{}

Float4::Float4(const Float3& value, float _w)
	: x(value.x)
	, y(value.y)
	, z(value.z)
	, w(_w)
{

}

Float4::Float4(const Float4& a)
	: x(a.x)
	, y(a.y)
	, z(a.z)
	, w(a.w)
{
}

Float4::~Float4()
{
}

Float4& Float4::operator = (const Float4& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}

Float4 Float4::operator +(const Float4& a) const
{
	return Float4( x+a.x, y+a.y, z+a.z );
}

Float4 Float4::operator -(const Float4& a) const
{
	return Float4( x-a.x, y-a.y, z-a.z );
}

Float4 Float4::operator *(float a) const
{
	return Float4( x*a, y*a, z*a, w*a);
}

float Float4::operator *(const Float4& a) const
{
	return( (x * a.x) + (y * a.y) + (z * a.z) );
}

float4 Float4::operator *(const Matrix& a) const
{
	return Float4(
		x * a.c0.x + y * a.c0.y + z * a.c0.z + w * a.c0.w,
		x * a.c1.x + y * a.c1.y + z * a.c1.z + w * a.c1.w,
		x * a.c2.x + y * a.c2.y + z * a.c2.z + w * a.c2.w,
		x * a.c3.x + y * a.c3.y + z * a.c3.z + w * a.c3.w);
}