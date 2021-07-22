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
#include "../Mathematics/MathUtil.h"


#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "../GLTF/tiny_gltf.h"
#include "Mesh.h"
#include "../GLTF/gltf-loader.h"
#include "Material.h"

using namespace std;

Engine::Engine()
	: m_Camera(nullptr)
	, m_Theta(0.1f)
	, m_Phi(0.1f)
	, m_Radius(8.0f)
	, m_LastMousePos(0.0f, 0.0f)
{
}

Engine::~Engine()
{
}

std::vector<Mesh> meshes;
std::vector<Texture> textures;
std::vector<Material> materials;

void Engine::Init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	WinApp::GetSingletonPtr()->Create(hInstance, nCmdShow, width, height, "Render PipeLine");

	RenderDevice::GetSingletonPtr()->InitRenderDevice(WinApp::GetSingletonPtr()->GetHwnd(), width, height);

	m_Camera = new Camera();
	m_Camera->FieldOfView = 60.0f;
	m_Camera->NearPlane = 0.1f;
	m_Camera->FarPlane = 1000.0f;
	m_Camera->Aspect = ((float)width) / height;
	m_Camera->ViewPortWidth = 1024.0f;
	m_Camera->viewPortHeight = 768.0f;

	LoadModel();
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
	auto x = m_Radius * sinf(m_Phi) * cosf(m_Theta);
	auto z = m_Radius * sinf(m_Phi) * sinf(m_Theta);
	auto y = m_Radius * cosf(m_Phi);

	m_Camera->Position = float3(x, y, z);
	m_Camera->Target = float3(0, 0, 0);
	
	for(auto mesh : meshes)
	{
		Pipeline::Execute(m_Camera, mesh);
	}
}

void Engine::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		float dx = MathUtil::AngelToRadian(0.25f * static_cast<float>(x - m_LastMousePos.x));
		float dy = MathUtil::AngelToRadian(0.25f * static_cast<float>(y - m_LastMousePos.y));

		// Update angles based on input to orbit camera around box.
		m_Theta += dx;
		m_Phi += dy;

		// Restrict the angle mPhi.
		m_Phi = MathUtil::Clamp(m_Phi, 0.1f, MathUtil::pi - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.005 unit in the scene.
		float dx = 0.005f * static_cast<float>(x - m_LastMousePos.x);
		float dy = 0.005f * static_cast<float>(y - m_LastMousePos.y);

		// Update the camera radius based on input.
		m_Radius += dx - dy;

		// Restrict the radius.
		m_Radius = MathUtil::Clamp(m_Radius, 3.0f, 15.0f);
	}

	m_LastMousePos.x = static_cast<float>(x);
	m_LastMousePos.y = static_cast<float>(y);
}

void Engine::LoadModel()
{
	LoadGLTF("../SoftwareRenderer/Model/Helmet/DamagedHelmet.gltf", &meshes, &textures, &materials);
}