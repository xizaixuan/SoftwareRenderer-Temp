#include "RenderDevice.h"
#include <wingdi.h>

RenderDevice::RenderDevice(void)
	: m_WindowWidth(0)
	, m_WindowHeight(0)
	, m_HWND(nullptr)
	, m_Factory(nullptr)
	, m_RenderTarget(nullptr)
	, m_Bitmap(nullptr)
	, m_DataBuffer(nullptr)
{
}

RenderDevice::~RenderDevice(void)
{
	SAFE_DELETE_ARRAY(m_DataBuffer);

	SAFE_RELEASE(m_RenderTarget);
	SAFE_RELEASE(m_Factory);
	SAFE_RELEASE(m_Bitmap);
}

void RenderDevice::InitRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight)
{
	//进行赋值
	m_WindowWidth = WindowWidth;
	m_WindowHeight= WindowHeight;

	m_HWND = hWndMain;

	if (m_RenderTarget == nullptr)
	{
		HRESULT hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory);
		if (FAILED(hr))
		{
			MessageBox(m_HWND, "Create D2D factory failed!", "Error", 0);
			return;
		}

		D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE
		);

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties();
		props.pixelFormat = pixelFormat;

		hr = m_Factory->CreateHwndRenderTarget(
			props,
			D2D1::HwndRenderTargetProperties(m_HWND, D2D1::SizeU(m_WindowWidth, m_WindowHeight)),
			&m_RenderTarget
		);

		if (FAILED(hr))
		{
			MessageBox(m_HWND, "Create render target failed!", "Error", 0);
			return;
		}

		//创建位图    
		D2D1_SIZE_U imgsize = D2D1::SizeU(m_WindowWidth, m_WindowHeight);
		D2D1_BITMAP_PROPERTIES prop =  
		{
			pixelFormat,
			(float)imgsize.width,
			(float)imgsize.height
		};
		long pitch = imgsize.width;
		m_DataBuffer = new DWORD[imgsize.width * imgsize.height];
		memset(m_DataBuffer, 0, imgsize.width * imgsize.height * sizeof(DWORD));
		m_RenderTarget->CreateBitmap(imgsize, m_DataBuffer, pitch, &prop, &m_Bitmap);
	}
}

void RenderDevice::RenderBegin()
{
	m_RenderTarget->BeginDraw();

	// 设置背景色
	m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	memset(m_DataBuffer, 0, m_WindowWidth * m_WindowHeight * sizeof(DWORD));
}

void RenderDevice::RenderEnd()
{
	m_RenderTarget->EndDraw();
}

void RenderDevice::RenderBuffer()
{
	D2D1_RECT_U rect2 = D2D1::RectU(0, 0, m_WindowWidth, m_WindowHeight);
	m_Bitmap->CopyFromMemory(&rect2, m_DataBuffer, m_WindowWidth * sizeof(DWORD));
	m_RenderTarget->DrawBitmap(m_Bitmap, D2D1::RectF(0.0f, 0.0f, m_WindowWidth-1, m_WindowHeight-1));
}

void RenderDevice::DrawPixel(DWORD x, DWORD y, DWORD color)
{
	if (x < m_WindowWidth && y < m_WindowHeight)
	{
		auto index = x + y*m_WindowWidth;
		m_DataBuffer[index] = color;
	}
}