#include "RenderDevice.h"
#include <wingdi.h>

RenderDevice::RenderDevice(void)
	: mWindowWidth(0)
	, mWindowHeight(0)
	, mHWND(nullptr)
	, mFactory(nullptr)
	, mRenderTarget(nullptr)
	, mBitmap(nullptr)
	, mDataBuffer(nullptr)
{
}

RenderDevice::~RenderDevice(void)
{
	SAFE_DELETE_ARRAY(mDataBuffer);

	SAFE_RELEASE(mRenderTarget);
	SAFE_RELEASE(mFactory);
	SAFE_RELEASE(mBitmap);
}

void RenderDevice::InitRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight)
{
	//���и�ֵ
	mWindowWidth = WindowWidth;
	mWindowHeight= WindowHeight;

	mHWND = hWndMain;

	if (mRenderTarget == nullptr)
	{
		HRESULT hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory);
		if (FAILED(hr))
		{
			MessageBox(mHWND, "Create D2D factory failed!", "Error", 0);
			return;
		}

		D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE
		);

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties();
		props.pixelFormat = pixelFormat;

		hr = mFactory->CreateHwndRenderTarget(
			props,
			D2D1::HwndRenderTargetProperties(mHWND, D2D1::SizeU(mWindowWidth, mWindowHeight)),
			&mRenderTarget
		);

		if (FAILED(hr))
		{
			MessageBox(mHWND, "Create render target failed!", "Error", 0);
			return;
		}

		//����λͼ    
		D2D1_SIZE_U imgsize = D2D1::SizeU(mWindowWidth, mWindowHeight);
		D2D1_BITMAP_PROPERTIES prop =  
		{
			pixelFormat,
			(float)imgsize.width,
			(float)imgsize.height
		};
		long pitch = imgsize.width;
		mDataBuffer = new DWORD[imgsize.width * imgsize.height];
		memset(mDataBuffer, 0, imgsize.width * imgsize.height * sizeof(DWORD));
		mRenderTarget->CreateBitmap(imgsize, mDataBuffer, pitch, &prop, &mBitmap);
	}
}

void RenderDevice::RenderBegin()
{
	mRenderTarget->BeginDraw();

	// ���ñ���ɫ
	mRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	memset(mDataBuffer, 0, mWindowWidth * mWindowHeight * sizeof(DWORD));
}

void RenderDevice::RenderEnd()
{
	mRenderTarget->EndDraw();
}

void RenderDevice::RenderBuffer()
{
	D2D1_RECT_U rect2 = D2D1::RectU(0, 0, mWindowWidth, mWindowHeight);
	mBitmap->CopyFromMemory(&rect2, mDataBuffer, mWindowWidth * sizeof(DWORD));
	mRenderTarget->DrawBitmap(mBitmap, D2D1::RectF(0.0f, 0.0f, mWindowWidth-1, mWindowHeight-1));
}

void RenderDevice::DrawPixel(DWORD x, DWORD y, DWORD color)
{
	if (x < mWindowWidth && y < mWindowHeight)
	{
		auto index = x + y*mWindowWidth;
		mDataBuffer[index] = color;
	}
}