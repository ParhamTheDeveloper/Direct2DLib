#pragma once

// Disabling the C4251 warning for STD dll-interfaces
#pragma warning(disable: 4251)

#include "pch.h"

// Core macros

// Configuration

#ifdef _DEBUG
	#define D2DLIB_DEBUG 1
#else
	#define D2DLIB_RELEASE 1
#endif // _DEBUG

// Platform

#ifdef _M_X64
	#define D2DLIB_X64 1
	#define D2DLIB_64BIT 1
#else
	#define D2DLIB_X32 1
	#define D2DLIB_32BIT 1
#endif // _M_X64

#ifdef _WIN32
	#define D2DLIB_WIN32 1
	#ifdef _WIN64
		#define D2DLIB_WIN64 1
	#endif
#endif // _WIN32

#ifdef _WIN32_WINNT_WIN7
	#ifdef _WIN32_WINNT_WIN8		
		#ifdef _WIN32_WINNT_WIN10
			#define D2DLIB_WIN7_10
			#define D2DLIB_WIN8_10
			#define D2DLIB_WIN10
		#else
			#define D2DLIB_WIN7_8
			#define D2DLIB_WIN_8	
		#endif // _WIN32_WINNT_WIN10
	#elif
		#define D2DLIB_WIN7
	#endif // _WIN32_WINNT_WIN8
#endif // _WIN32_WINNT_WIN7

// DLL export and import API

#ifdef D2DLIB_WIN32
	#ifdef D2DLIB_EXPORTS
		#ifdef D2DLIB_CLIENT_IMPORTS
			#define D2DLIB_API __declspec(dllimport)
		#else
			#define D2DLIB_API __declspec(dllexport)
		#endif
	#else
		#define D2DLIB_API
	#endif
#endif

#define D2DLIB_BEGIN_HEADER_FILE pragma warning(disable: 4251)
#define D2DLIB_END_HEADER_FILE pragma warning(default: 4251)

// Win32 Custom Events

#define D2DLIB_WM_APPLICATION_RENDER (WM_APP + 1)

namespace D2DLib
{

	// Using declaration for STL containers, other classes

	using String = std::wstring;
	using StringStream = std::wstringstream;
	using OStream = std::wostream;
	using IStream = std::wistream;
	using Thread = std::thread;

	template<typename T>
	using Vector = std::vector<T>;

	template<typename T>
	using Deque = std::deque<T>;

	template<typename T>
	using Function = std::function<T>;
	
	template<typename T>
	using Stack = std::stack<T>;

	template<typename T, typename Deleter = std::default_delete<T>>
	using Scoped = std::unique_ptr<T, Deleter>;

	template<typename T>
	using Shared = std::shared_ptr<T>;

	template<typename KeyType, typename ValueType>
	using Map = std::map<KeyType, ValueType>;

	template<typename FirstType, typename SecondType>
	using Pair = std::pair<FirstType, SecondType>;

	// Using declaration for Numeric types

	using Int = int;
	using Int8 = signed char;
	using Int16 = short;
	using Int32 = int;
	using Int64 = long long;

	using UInt = unsigned int;
	using UInt8 = unsigned char;
	using UInt16 = unsigned short;
	using UInt32 = unsigned int;
	using UInt64 = unsigned long long;

}