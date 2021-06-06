/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   ���������
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_H_
#define Engine_H_

#include <Windows.h>
#include "..\Utility\Singleton.h"
#include "..\Mathematics\Float2.h"

class Camera;

class Engine : public Singleton<Engine>
{
	SINGLETON_DEFINE(Engine)
private:
	Engine();
	~Engine();

public:
	/// \brief ��ʼ��
	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height);

	/// \brief ��Դ����
	void Destroy();

	/// \brief ����
	void Update(float dt);

	/// \brief ��������
	void RenderScene();

	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	Camera* m_Camera;

	float m_Theta;
	float m_Phi;
	float m_Radius;

	float2 m_LastMousePos;
};


#endif