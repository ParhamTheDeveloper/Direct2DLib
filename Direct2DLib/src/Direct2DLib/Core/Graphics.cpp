#include "pch.h"
#include "Graphics.h"

namespace D2DLib
{

	Graphics* Graphics::s_Instance = nullptr;

	Graphics::Graphics(HWND hwnd)
		: m_HWnd(hwnd)
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
	}

	Graphics::~Graphics()
	{
		// Direct2D interfaces

		SafeRelease(&m_Factory);
		SafeRelease(&m_RenderTarget);
		SafeRelease(&m_DeviceContext);
	}


	void Graphics::Init()
	{
		// Direct2D Initialization

		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&m_Factory
		);

		if (SUCCEEDED(hr))
		{
			RECT clientRect;
			GetClientRect(m_HWnd, &clientRect);

			D2D1_SIZE_U renderTargetSize = {
				Cast<UInt>(clientRect.right - clientRect.left),
				Cast<UInt>(clientRect.bottom - clientRect.top)
			};

			// Basiclly rendering things as fast as possible the goal here so we don't need to retain anything,
			// Something like setting the third parameter of the InvalidateRect function to true
			// which would render things immediately, So we want the D2D1_PRESENT_OPTIONS_IMMEDIATELY option.
			hr = m_Factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(
					m_HWnd,
					renderTargetSize,
					D2D1_PRESENT_OPTIONS_IMMEDIATELY
				),
				&m_RenderTarget
			);

			if (FAILED(hr))
			{
				throw std::runtime_error("Can not create the render target!");
			}

			if (FAILED(hr))
			{
				throw std::runtime_error("Can not create the DXGI factory!");
			}

			m_RenderTarget->QueryInterface(&m_DeviceContext);
		}
	}

	void Graphics::BeginPaint()
	{
		m_RenderTarget->BeginDraw();
	}

	void Graphics::EndPaint()
	{
		m_RenderTarget->EndDraw();
	}

	void Graphics::ClearScreen(const D2D1::ColorF& color)
	{
		m_RenderTarget->Clear(color);
	}

	void Graphics::Resize(UInt width, UInt height)
	{
		D2D1_SIZE_U renderTargetSize = { width, height };
		m_RenderTarget->Resize(renderTargetSize);
	}

	Graphics* GetMainGraphics()
	{
		return Graphics::s_Instance;
	}

}