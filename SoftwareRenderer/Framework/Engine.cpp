#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"
#include <corecrt_math.h>
#include <corecrt_math_defines.h>
#include "RenderContext.h"

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
	int w = 1920;
	int h = 1080;
	float cx = w * 0.5f - 0.5f;
	float cy = h * 0.5f - 0.5f;

	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	for (int j = 0; j < 5; j++)
	{
		float r1 = fminf(w, h) * (j + 0.5f) * 0.085f;
		float r2 = fminf(w, h) * (j + 1.5f) * 0.085f;
		float t = j * M_PI / 64.0f;
		for (int i = 1; i <= 64; i++, t += 2.0f * M_PI / 64)
		{
			float ct = cosf(t), st = sinf(t);
			RenderContext::DrawLine(cx + r1 * ct, cy - r1 * st, cx + r2 * ct, cy - r2 * st, color);
		}
	}
}