#include "Direct2DLibpch.h"
#include "Window.h"

namespace D2DLib
{

	Window* Window::s_Instance = nullptr;

	Window::Window(const String& title, const WindowStyle& style)
		: m_Style(style)
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
		Create(style, title);
		
		try
		{
			m_Gfx = CreateScoped<Graphics>(m_HWnd);
		}
		catch (const std::exception& err)
		{
			MessageBoxA(nullptr, err.what(), "Graphics Error", MB_ICONERROR);
		}

		// Determining the size of the window at the window creation time
		if (m_Style.IsMaximized)
		{
			Maximize();
		}
		else
		{
			ShowWindow(m_HWnd, SW_SHOW);
		}

		// We can't use C++'s intrinsic bool type, because BOOL is typedef for int.
		BOOL isDwmEnabled = true;
		DwmIsCompositionEnabled(&isDwmEnabled);
		
		DWM_PRESENT_PARAMETERS presentParams = { };
		presentParams.cbSize = sizeof(DWM_PRESENT_PARAMETERS);
		presentParams.fQueue = true;
		
		DwmSetPresentParameters(m_HWnd, &presentParams);

		InitializeVirtualRenderer();
		InitializeVirtualResourceManager();
	}

	Window::~Window()
	{
		ShutdownVirtualRenderer();
		ShutdownVirtualResourceManager();
	}

	bool Window::ShouldClose()
	{
		MSG msg = { };
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return true;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return false;
	}

	void Window::Update()
	{
		InvalidateRect(m_HWnd, nullptr, false);
	}

	void Window::SetStyle(const WindowStyle& style)
	{
		m_Style = style;
		Update();
	}

	void Window::SetIcon(const String& filePath)
	{
		HANDLE hIcon = LoadImage(nullptr, filePath.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hIcon) {
			// Change both icons to the same icon handle.
			SendMessage(m_HWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			SendMessage(m_HWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

			// This will ensure that the application icon gets changed too.
			SendMessage(m_HWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			SendMessage(m_HWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
		DeleteObject(hIcon);
	}

	const Style Window::GetClientSize()
	{
		RECT rc;
		GetClientRect(m_HWnd, &rc);
		return { Cast<float>(rc.right - rc.left), Cast<float>(rc.bottom - rc.top) };
	}

	void Window::Maximize()
	{
		ShowWindow(m_HWnd, SW_MAXIMIZE);
	}

	void Window::Minimize()
	{
		ShowWindow(m_HWnd, SW_MINIMIZE);
	}

	void Window::Restore()
	{
		ShowWindow(m_HWnd, SW_RESTORE);
	}

	void Window::CreateTimer(
		bool canUpdate,
		UInt64 timerId,
		UInt frameRate,
		const Function<void(const WindowTimerEvent&)>& callbackFn
	)
	{
		SetTimer(m_HWnd, Cast<UINT_PTR>(timerId), 1000 / frameRate, nullptr);
		Function<void(const WindowTimerEvent& e)> listener;
		if (canUpdate)
		{
			listener = [callbackFn](const WindowTimerEvent& e)
			{
				e.Target.Update();
				callbackFn(e);
			};
		}
		else
		{
			listener = [callbackFn](const WindowTimerEvent& e)
			{
				callbackFn(e);
			};
		}
		m_Timers.insert({ timerId, listener });
	}

	void Window::DestroyTimer(UInt64 timerId)
	{
		KillTimer(m_HWnd, Cast<UINT_PTR>(timerId));
	}

	void Window::OnPaint(Event& event)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_HWnd, &ps);
		m_Gfx->BeginPaint();
		m_Gfx->ClearScreen(m_Style.BackgroundColor);
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			WindowUpdateEvent, WindowUpdate,
			listenerEvent.DeltaTime = GetDeltaTime();
		)
		m_Gfx->EndPaint();
		EndPaint(m_HWnd, &ps);
	}

	void Window::OnResize(Event& event)
	{
		UInt width = LOWORD(event.Data);
		UInt height = HIWORD(event.Data);
		
		// Resizing the window render target so we're not facing any scaling issues
		m_Gfx->Resize(width, height);
		Update();

		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			WindowResizeEvent, WindowResize,
			listenerEvent.Width = Cast<float>(width);
			listenerEvent.Height = Cast<float>(height);
		)
	}

	void Window::OnClose(Event& event)
	{
		// Unlike the other event handlers, OnClose calls the event listener for WindowCloseEvent before
		// closing the window. (calls the event listener before the event handler's operation
		// which is not the same for the other event handlers.)
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			WindowCloseEvent, WindowClose,
			listenerEvent.ExitCode = 0;
		)
		PostQuitMessage(0);
	}

	void Window::OnTimer(Event& event)
	{
		for (auto& [timerId, listener] : m_Timers)
		{
			if (timerId == event.Param)
			{
				listener(event.Get<WindowTimerEvent>());
				break;
			}
		}

		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			WindowTimerEvent, WindowTimer,
			listenerEvent.TimerId = event.Param;
		)
	}

	void Window::OnMouseDown(Event& event)
	{
		bool isRight = event.Message == WM_RBUTTONDOWN;
		float mouseX = Cast<float>(LOWORD(event.Data));
		float mouseY = Cast<float>(HIWORD(event.Data));
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			MouseDownEvent, MouseDown,
			listenerEvent.Position = { mouseX, mouseY };
			listenerEvent.IsRight = isRight;
		)
	}

	void Window::OnMouseUp(Event& event)
	{
		bool isRight = event.Message == WM_RBUTTONUP;
		float mouseX = Cast<float>(LOWORD(event.Data));
		float mouseY = Cast<float>(HIWORD(event.Data));
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			MouseUpEvent, MouseUp,
			listenerEvent.Position = { mouseX, mouseY };
			listenerEvent.IsRight = isRight;
		)
	}

	void Window::OnMouseMove(Event& event)
	{
		bool isRight = false;
		float mouseX = Cast<float>(LOWORD(event.Data));
		float mouseY = Cast<float>(HIWORD(event.Data));
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			MouseMoveEvent, MouseMove,
			listenerEvent.Position = { mouseX, mouseY };
			listenerEvent.IsRight = isRight;
		)
	}

	void Window::OnKeyDown(Event& event)
	{
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			KeyDownEvent, KeyDown,
			listenerEvent.Character = Cast<int>(event.Param);
		)
	}

	void Window::OnKeyUp(Event& event)
	{
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			KeyDownEvent, KeyDown,
			listenerEvent.Character = Cast<int>(event.Param);
		)
	}

	void Window::OnKeyPress(Event& event)
	{
		D2DLIB_IMPLEMENT_EVENT_LISTENER(
			KeyPressEvent, KeyPress,
			listenerEvent.Character = Cast<int>(event.Param);
		)
	}

	Window* GetMainWindow()
	{
		return Window::s_Instance;
	}

}