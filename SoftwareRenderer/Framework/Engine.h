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
};


#endif