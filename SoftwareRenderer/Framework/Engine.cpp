#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"

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

	RenderDevice::getSingletonPtr()->RenderBuffer();

	RenderDevice::getSingletonPtr()->RenderEnd();
}