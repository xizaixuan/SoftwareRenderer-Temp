#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"
#include <corecrt_math.h>
#include <corecrt_math_defines.h>

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	WinApp::getSingletonPtr()->Create(hInstance, nCmdShow, width, height, "Render PipeLine");

	RenderDevice::getSingletonPtr()->InitRenderDevice(WinApp::getSingletonPtr()->GetHwnd(), width, height);
}

void Engine::Destroy()
{

}

void Engine::Update(float dt)
{
	RenderDevice::getSingletonPtr()->RenderBegin();

	RenderScene();

	RenderDevice::getSingletonPtr()->RenderBuffer();

	RenderDevice::getSingletonPtr()->RenderEnd();
}

void Engine::DrawLine(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;

	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	while (x0 != x1 || y0 != y1)
	{
		RenderDevice::getSingletonPtr()->DrawPixel(x0, y0, color);

		int e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 <  dy) { err += dx; y0 += sy; }
	}
}

void Engine::RenderScene()
{
	int w = 1920;
	int h = 1080;
	float cx = w * 0.5f - 0.5f;
	float cy = h * 0.5f - 0.5f;
	for (int j = 0; j < 5; j++)
	{
		float r1 = fminf(w, h) * (j + 0.5f) * 0.085f;
		float r2 = fminf(w, h) * (j + 1.5f) * 0.085f;
		float t = j * M_PI / 64.0f;
		for (int i = 1; i <= 64; i++, t += 2.0f * M_PI / 64)
		{
			float ct = cosf(t), st = sinf(t);
			DrawLine(cx + r1 * ct, cy - r1 * st, cx + r2 * ct, cy - r2 * st);
		}
	}
}