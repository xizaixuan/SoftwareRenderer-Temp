#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"
#include <corecrt_math.h>
#include <corecrt_math_defines.h>
#include "RenderContext.h"
#include <vector>
#include "../Mathematics/Float3.h"
#include "../Camera.h"
#include "../Pipeline.h"

using namespace std;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	WinApp::GetSingletonPtr()->Create(hInstance, nCmdShow, width, height, "Render PipeLine");

	RenderDevice::GetSingletonPtr()->InitRenderDevice(WinApp::GetSingletonPtr()->GetHwnd(), width, height);

	m_Camera = new Camera();
	m_Camera->FieldOfView = 60.0f;
	m_Camera->NearPlane = 0.1f;
	m_Camera->FarPlane = 1000.0f;
	m_Camera->Aspect = ((float)width) / height;
}

void Engine::Destroy()
{

}

void Engine::Update(float dt)
{
	RenderDevice::GetSingletonPtr()->RenderBegin();

	RenderScene();

	RenderDevice::GetSingletonPtr()->RenderBuffer();

	RenderDevice::GetSingletonPtr()->RenderEnd();
}


void Engine::RenderScene()
{
	m_Camera->Position = float3(2, 3, 5);
	m_Camera->Target = float3(0, 0, 0);

	vector<float3> vertices{
		float3(-1.0f, -1.0f, -1.0f),
		float3(-1.0f,  1.0f, -1.0f),
		float3(1.0f,  1.0f, -1.0f),
		float3(1.0f, -1.0f, -1.0f),
		float3(-1.0f, -1.0f,  1.0f),
		float3(-1.0f,  1.0f,  1.0f),
		float3(1.0f,  1.0f,  1.0f),
		float3(1.0f, -1.0f,  1.0f)
	};

	vector<int> indices = {
		// Front face.
		0, 1, 2,
		0, 2, 3,

		// Back face.
		4, 6, 5,
		4, 7, 6,

		// Left face.
 		4, 5, 1,
 		4, 1, 0,

		// Right face.
		3, 2, 6,
		3, 6, 7,

		// Top face.
		1, 5, 6,
		1, 6, 2,

		// Bottom face.
		4, 0, 3,
		4, 3, 7,
	};

	Pipeline::Execute(m_Camera, vertices, indices);
}