#pragma once

#include "Base.h"
#include "Utils.h"
#include "Style.h"
#include "Direct2DLib/Renderer/Renderer.h"

#define D2DLIB_DEBUG_DECLARE_LOG_METHOD(name)										\
	template<typename ...Args>														\
	static void name(Args&&... args)												\
	{																				\
		Logger::Print<DebugLogLevel::name>(std::forward<Args>(args)...);			\
	}

namespace D2DLib
{

	enum class DebugLogLevel : UInt8
	{
		Log,
		Info,
		Error,
		Warning,
		Success,
		Progress
	};

	class Logger
	{
	public:
		static void Print()
		{
			std::wcout << L'\n';
		}

		template <DebugLogLevel level = DebugLogLevel::Log, typename Arg, typename... Args>
		static void Print(Arg&& arg, Args&&... args)
		{
			static bool isFirst = true;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
			GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
			WORD originalAttributes = consoleInfo.wAttributes;
			WORD textColor;
			const char* levelStr = "";

			switch (level)
			{
				case DebugLogLevel::Log:
					{
						textColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
						levelStr = "Log";
					}
					break;

				case DebugLogLevel::Info:
					{
						textColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
						levelStr = "Info";
					}
					break;

				case DebugLogLevel::Error:
					{
						textColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
						levelStr = "Error";
					}
					break;

				case DebugLogLevel::Warning:
					{
						textColor = FOREGROUND_RED | FOREGROUND_GREEN;
						levelStr = "Warning";
					}
					break;

				case DebugLogLevel::Success:
					{
						textColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
						levelStr = "Success";
					}
					break;

				case DebugLogLevel::Progress:
					{
						textColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
						levelStr = "Progress";
					}
					break;
			}
			SetConsoleTextAttribute(hConsole, textColor);
			std::wcout << "[" << levelStr << "] " << arg << "\n";

			if constexpr (sizeof...(args))
			{
				Print<level>(std::forward<Args>(args)...);
			}
			SetConsoleTextAttribute(hConsole, originalAttributes);
		}
	};

	class Debug
	{
	public:
		// Logging methods
		
		D2DLIB_DEBUG_DECLARE_LOG_METHOD(Log)
		D2DLIB_DEBUG_DECLARE_LOG_METHOD(Info)
		D2DLIB_DEBUG_DECLARE_LOG_METHOD(Error)
		D2DLIB_DEBUG_DECLARE_LOG_METHOD(Warning)
		D2DLIB_DEBUG_DECLARE_LOG_METHOD(Success)
		D2DLIB_DEBUG_DECLARE_LOG_METHOD(Progress)

		static void Assert(bool condition);
			
		// Logging methods

		class Console
		{
		public:
			static Style GetClientStyle();
			static const Vector2 GetMousePosition();
			static void SetStyle(const Style& style);
			static void SetTitle(const String& title);
		};
	};

	// Platform and Configuration specifiers

	namespace Configuration
	{
		#ifdef D2DLIB_DEBUG
			static constexpr const bool IsOnDebugMode = D2DLIB_DEBUG;
		#else
			static constexpr const bool IsOnDebugMode = 0;
		#endif // D2DLIB_DEBUG

		#ifdef D2DLIB_RELEASE
			static constexpr const bool IsOnReleaseMode = D2DLIB_RELEASE;
		#else
			static constexpr const bool IsOnReleaseMode = 0;
		#endif // D2DLIB_RELEASE
	}

	namespace Platform
	{
		#ifdef D2DLIB_64BIT
			static constexpr const bool IsOn64BitMode = D2DLIB_64BIT;
		#else
			static constexpr const bool IsOn64BitMode = 0;
		#endif // D2DLIB_64BIT

		#ifdef D2DLIB_32BIT
			static constexpr const bool IsOn32BitMode = D2DLIB_32BIT;
		#else
			static constexpr const bool IsOn32BitMode = 0;
		#endif // D2DLIB_32BIT

		#if D2DLIB_X64
			static constexpr const bool IsOnX64Mode = D2DLIB_X64;
		#else
			static constexpr const bool IsOnX64Mode = 0;
		#endif // D2DLIB_X64

		#ifdef D2DLIB_X32
			static constexpr const bool IsOnX32Mode = D2DLIB_X32;
		#else
			static constexpr const bool IsOnX32Mode = 0;
		#endif // D2DLIB_X32

		static constexpr const bool IsWin32 = D2DLIB_WIN32;
		static constexpr const bool IsWin64 = !D2DLIB_WIN32; // D2DLIB_WIN64
	}

}