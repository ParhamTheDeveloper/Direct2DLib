#pragma once

#include "Direct2DLib/Core/Base.h"
#include "Direct2DLib/Core/Styles.h"
#include "Event.h"

namespace D2DLib
{

	template<typename DerivedWindow>
	class MessageManager
	{
	public:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			DerivedWindow* pWindow = nullptr;
			if (uMsg == WM_NCCREATE)
			{
				LPCREATESTRUCT pCreate = reinterpret_cast<LPCREATESTRUCT>(lParam);
				pWindow = reinterpret_cast<DerivedWindow*>(pCreate->lpCreateParams);
				SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
				pWindow->m_HWnd = hwnd;
			}
			else
			{
				pWindow = reinterpret_cast<DerivedWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			}
			if (pWindow)
			{
				return pWindow->HandleMessage(uMsg, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
		}

		/// <summary>
		/// Creates the window with the given parameters blow
		/// </summary>
		/// <param name="wndStyle"></param>
		/// <param name="windowName"></param>
		/// <param name="hwndParent"></param>
		/// <param name="hMenu"></param>
		void Create(
			const WindowStyle& wndStyle,
			const String& windowName,
			HWND hwndParent = nullptr,
			HMENU hMenu = nullptr
			)
		{
			WNDCLASS wndClass = { 0 };
			wndClass.lpszClassName = GetWindowClassName();
			wndClass.lpfnWndProc = WindowProc; // We want the derived window to only use the MessageManager's Window Procedure
			wndClass.hInstance = GetModuleHandle(nullptr);

			RegisterClass(&wndClass);

			m_HWnd = CreateWindowEx(
				wndStyle.ExtraWindowStyles,
				GetWindowClassName(),
				windowName.c_str(),
				wndStyle.WindowStyles,
				Cast<int>(wndStyle.Position.X), Cast<int>(wndStyle.Position.Y),
				Cast<int>(wndStyle.Width), Cast<int>(wndStyle.Height),
				hwndParent, hMenu,
				GetModuleHandle(nullptr),
				this
			);

			if (!m_HWnd)
			{
				throw std::runtime_error("Can not create the window!");
			}
		}
		
		Event* MakeEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, Window* target)
		{
			Event* pEvent = new Event(
				*target, m_HWnd,
				uMsg, wParam, lParam
			);
			return pEvent;
		}

		HWND GetWindow() const { return m_HWnd; }
	protected:
		virtual const wchar_t* GetWindowClassName() const = 0;
		virtual LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	protected:
		HWND m_HWnd = nullptr;
	};

}

#define D2DLIB_BEGIN_MSG_MAP															\
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override	\
	{																					\
		Event* pEvent = MakeEvent(uMsg, wParam, lParam, this);							\
		switch (uMsg)																	\
		{																				\
			case WM_NULL:																\
				return 0;

#define D2DLIB_HANDLE_MSG(message, handlerCallbackFn)									\
			case message:																\
			{																			\
				handlerCallbackFn(*pEvent);												\
				delete pEvent;															\
				return 0;																\
			}

#define D2DLIB_END_MSG_MAP																\
		}																				\
		return DefWindowProc(m_HWnd, uMsg, wParam, lParam);								\
	}