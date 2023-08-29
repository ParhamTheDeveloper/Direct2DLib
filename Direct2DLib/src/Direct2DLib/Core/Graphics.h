#pragma once

#include "Utils.h"

namespace D2DLib
{
	class D2DLIB_API Graphics
	{
	public:
		Graphics(HWND hwnd);
		~Graphics();
		
		void Init();
		void BeginPaint();
		void EndPaint();
		void ClearScreen(const D2D1::ColorF& color);
		void Resize(UInt width, UInt height);

		ID2D1HwndRenderTarget* GetRenderTarget() const { return m_RenderTarget; }
		ID2D1Factory7* GetFactory() const { return m_Factory; }
		ID2D1DeviceContext6* GetDeviceContext() const { return m_DeviceContext; }
	private:
		HWND m_HWnd;
		ID2D1HwndRenderTarget* m_RenderTarget = nullptr;
		ID2D1Factory7* m_Factory = nullptr;
		ID2D1DeviceContext6* m_DeviceContext = nullptr;
		static Graphics* s_Instance;
	private:
		friend D2DLIB_API Graphics* GetMainGraphics();
	};

	D2DLIB_API Graphics* GetMainGraphics();
}