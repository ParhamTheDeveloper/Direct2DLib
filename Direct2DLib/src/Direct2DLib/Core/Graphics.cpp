#include "Direct2DLibpch.h"
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
		Init();
	}

	Graphics::~Graphics()
	{
		// Direct2D interfaces

		SafeRelease(&m_Factory);
		SafeRelease(&m_RenderTarget);
		SafeRelease(&m_DeviceContext);

		// Direct3D interfaces

		SafeRelease(&m_D3DDevice);
		SafeRelease(&m_D3DDeviceContext);

		// DXGI interfaces

		SafeRelease(&m_DXGIFactory);
		SafeRelease(&m_DXGISwapChain);
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
				throw std::runtime_error("Can not create the Render Target!");
			}

			hr = m_RenderTarget->QueryInterface(&m_DeviceContext);
			
			if (FAILED(hr))
			{
				throw std::runtime_error("Can not create the Device Context!");
			}

			m_DeviceContext->GetDevice(&m_Device);

			// Create the D3D11 device and device context
			D3D_FEATURE_LEVEL featureLevel;
			hr = D3D11CreateDevice(
				nullptr,                    // Specify nullptr to use the default adapter
				D3D_DRIVER_TYPE_HARDWARE,    // Use hardware rendering
				nullptr,                    // Specify nullptr because we use hardware rendering
				0,                          // No flags
				nullptr,                    // Default feature level array
				0,                          // Default feature level array size
				D3D11_SDK_VERSION,          // Use the D3D11 SDK version
				&m_D3DDevice,                    // Output device
				&featureLevel,              // Output feature level
				&m_D3DDeviceContext              // Output device context
			);

			if (FAILED(hr))
			{
				throw std::runtime_error("Can not create the Render Target!");
			}

			// Create a DXGI factory
			hr = CreateDXGIFactory(IID_PPV_ARGS(&m_DXGIFactory));
			
			if (FAILED(hr))
			{
				throw std::runtime_error("Can not create the DXGI Factory!");
			}

			// Describe the swap chain
			DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
			swapChainDesc.BufferDesc.Width = 0;
			swapChainDesc.BufferDesc.Height = 0;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Pixel format
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;         // Refresh rate numerator
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;        // Refresh rate denominator
			swapChainDesc.SampleDesc.Count = 1;                           // Number of samples
			swapChainDesc.SampleDesc.Quality = 0;                         // Quality of samples
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // Use the swap chain as a render target
			swapChainDesc.BufferCount = 1;                                // Number of back buffers
			swapChainDesc.OutputWindow = m_HWnd;
			swapChainDesc.Windowed = TRUE;                                // Windowed mode
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;          // Discard the back buffer contents after presenting

			// Create the swap chain
			hr = m_DXGIFactory->CreateSwapChain(m_D3DDevice, &swapChainDesc, &m_DXGISwapChain);

			if (FAILED(hr))
			{
				throw std::runtime_error("Can not create the DXGI Swap Chain!");
			}
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
		m_DXGISwapChain->ResizeBuffers(2, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, 0);
	}

	Graphics* GetMainGraphics()
	{
		return Graphics::s_Instance;
	}

}