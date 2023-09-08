#include "Direct2DLibpch.h"
#include "Debug.h"

namespace D2DLib
{

	void Debug::Assert(bool condition)
	{
		assert(condition);
	}

	Style Debug::Console::GetClientStyle()
	{
		HWND hConsole = GetConsoleWindow();
		RECT rc;
		GetClientRect(hConsole, &rc);
		POINT position = { };
		ClientToScreen(hConsole, &position);
		return {
			Cast<float>(rc.right - rc.left),
			Cast<float>(rc.bottom - rc.top),
			{ Cast<float>(position.x), Cast<float>(position.y) }
		};
	}

	const Vector2 Debug::Console::GetMousePosition()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		return { Cast<float>(consoleInfo.dwCursorPosition.X), Cast<float>(consoleInfo.dwCursorPosition.Y) };
	}

	void Debug::Console::SetStyle(const Style& style)
	{
		HWND hConsole = GetConsoleWindow();
		SetWindowPos(
			hConsole, nullptr,
			Cast<int>(style.Position.X), Cast<int>(style.Position.Y),
			Cast<int>(style.Width), Cast<int>(style.Height),
			SWP_NOZORDER
		);
	}

	void Debug::Console::SetTitle(const String& title)
	{
		SetConsoleTitle(title.c_str());
	}

}