#include "Camera.h"
#include "Mathematics/MathUtil.h"

void Camera::BuildViewMatrix()
{
	m_Forward = MathUtil::Normalize((m_Target - m_Position));
	m_Right = MathUtil::Normalize(MathUtil::Cross(Float3::Up, m_Forward));
	m_Up = MathUtil::Normalize(MathUtil::Cross(m_Forward, m_Right));

	m_ViewMatrix = Matrix(
		m_Right.x,			m_Up.x,			m_Forward.x,	0,
		m_Right.y,			m_Up.y,			m_Forward.y,	0,
		m_Right.z,			m_Up.z,			m_Forward.z,	0,
		-m_Position.x,	   -m_Position.y,  -m_Position.z,	0);
}

void Camera::BuildPerspectiveMatrix()
{
	auto N = m_NearPlane;
	auto F = m_FarPlane;
	auto a = (2 * N * F) / (N - F);
	auto b = (-N - F) / (N - F);

	auto W = 2 * N * tan(MathUtil::AngelToRadian(m_FieldOfView * 0.5f));
	auto H = W / m_Aspect;

	m_PerspectiveMatrix.Set(
		2 * N / W,	0,			0,	0,
		0,			2 * N / H,	0,  0,
		0,			0,			b,	1,
		0,			0,			a,	0);
}