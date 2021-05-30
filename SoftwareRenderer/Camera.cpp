#include "Camera.h"
#include "Mathematics/MathUtil.h"

void Camera::BuildViewMatrix()
{
	m_Forward = MathUtil::Normalize((m_Target - m_Position));
	m_Right = MathUtil::Normalize(MathUtil::Cross(Float3::Up, m_Forward));
	m_Up = MathUtil::Normalize(MathUtil::Cross(m_Forward, m_Right));

	auto transMat = Matrix(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		-m_Position.x, -m_Position.y, -m_Position.z, 0.0f);

	auto rotMat = Matrix(
		m_Right.x,	m_Up.x,	m_Forward.x, 0.0f,
		m_Right.y,	m_Up.y, m_Forward.y, 0.0f,
		m_Right.z,	m_Up.z, m_Forward.z, 0.0f,
		0.0f,		0.0f,	0.0f,		 0.0f);

	m_ViewMatrix = transMat * rotMat;
}

void Camera::BuildPerspectiveMatrix()
{
	auto N = m_NearPlane;
	auto F = m_FarPlane;
	auto a = (F + N) / (F - N);
	auto b = (-2 * N * F) / (F - N);

	auto W = 2 * N * tan(MathUtil::AngelToRadian(m_FieldOfView * 0.5f));
	auto H = W / m_Aspect;

	m_PerspectiveMatrix.Set(
		2 * N / W,	0,			0,	0,
		0,			2 * N / H,	0,  0,
		0,			0,			a,	1,
		0,			0,			b,	0);
}

void Camera::BuildViewPortMatrix()
{
	float W = 1920.0f;
	float H = 1080.0f;

	m_ViewPortMatrix.Set(
		W * 0.5f,	0.0f,		0.0f,	0.0f,
		0.0f,		H * 0.5f,	0.0f,	0.0f,
		0.0f,		0.0f,		1.0f,	0.0f,
		W * 0.5f,	H * 0.5f,	0.0f,	1.0f);
}