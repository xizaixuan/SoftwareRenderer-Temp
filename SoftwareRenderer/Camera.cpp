#include "Camera.h"
#include "Mathematics/MathUtil.h"
#include "Mathematics/Float3.h"

Camera::Camera()
	: Position(Float3::Zero)
	, Target(Float3::Zero)
	, Forward(Float3::Zero)
	, Up(Float3::Zero)
	, Right(Float3::Zero)
	, FieldOfView(0.0f)
	, NearPlane(0.0f)
	, FarPlane(0.0f)
	, Aspect(0.0f)
	, ViewPortWidth(0.0f)
	, viewPortHeight(0.0f)
{
	ViewMatrix.Identity();
	PerspectiveMatrix.Identity();
	ViewPortMatrix.Identity();
}

void Camera::BuildViewMatrix()
{
	Forward = MathUtil::Normalize((Target - Position));
	Right = MathUtil::Normalize(MathUtil::Cross(Float3::Up, Forward));
	Up = MathUtil::Normalize(MathUtil::Cross(Forward, Right));

	auto matT = Matrix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		Position.x, Position.y, Position.z, 1.0f);

	auto matR = Matrix(
		Right.x,	Right.y,	Right.z,	0.0f,
		Up.x,		Up.y,		Up.z,		0.0f,
		Forward.x,	Forward.y,	Forward.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);

	Matrix invView = matR * matT;

	ViewMatrix = MathUtil::Inverse(invView);
}

void Camera::BuildPerspectiveMatrix()
{
	auto N = NearPlane;
	auto F = FarPlane;
	auto a = (F + N) / (F - N);
	auto b = (-2 * N * F) / (F - N);

	auto W = 2 * N * tan(MathUtil::AngelToRadian(FieldOfView * 0.5f));
	auto H = W / Aspect;

	PerspectiveMatrix.Set(
		2 * N / W,	0,			0,	0,
		0,			2 * N / H,	0,  0,
		0,			0,			a,	1,
		0,			0,			b,	0);
}

void Camera::BuildViewPortMatrix()
{
	float alpha = 0.5f * ViewPortWidth;
	float beta = 0.5f * viewPortHeight;

	ViewPortMatrix.Set(
		alpha, 0.0f, 0.0f,	0.0f,
		0.0f,  beta, 0.0f,	0.0f,
		0.0f,  0.0f, 1.0f,	0.0f,
		alpha, beta, 0.0f,	1.0f);
}

Matrix Camera::GetViewMatrix()
{
	return ViewMatrix;
}

Matrix Camera::GetPerspectiveMatrix()
{
	return PerspectiveMatrix;
}

Matrix Camera::GetViewPortMatrix()
{
	return ViewPortMatrix;
}