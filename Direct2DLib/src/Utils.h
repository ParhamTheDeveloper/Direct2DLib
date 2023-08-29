#pragma once

#include "Direct2DLib/Core/Base.h"
#include "Direct2DLib/Core/Timestep.h"

namespace D2DLib
{

	/// <summary>
	/// This function is used the free the allocated memory inside COM objects.
	/// </summary>
	/// <typeparam name="Interface"></typeparam>
	/// <param name="ppInterface"></param>
	template<typename Interface>
	inline void SafeRelease(Interface** ppInterface)
	{
		if ((*ppInterface))
		{
			(*ppInterface)->Release();
			(*ppInterface) = nullptr;
		}
	}

	inline void SafeRelease(void* pBlock)
	{
		if (pBlock)
		{
			delete pBlock;
			pBlock = nullptr;
		}
	}

	/// <summary>
	/// <para>This function is generally used for casting numeric type values NOT pointers,
	/// If you want to cast pointer values use SafeCast function instead.</para>
	/// </summary>
	/// <typeparam name="To"></typeparam>
	/// <typeparam name="From"></typeparam>
	/// <param name="from"></param>
	/// <returns>The casted value</returns>
	template<typename To, typename From>
	inline To Cast(From from)
	{
		return static_cast<To>(from);
	}
	
	/// <summary>
	/// <para>This function is used for casting pointer type values NOT non pointers.</para>
	/// </summary>
	/// <typeparam name="To"></typeparam>
	/// <typeparam name="From"></typeparam>
	/// <param name="pFrom"></param>
	/// <returns>The casted pointer value</returns>
	template<typename To, typename From>
	inline To* SafeCast(From* pFrom)
	{
		return static_cast<To*>(pFrom);
	}

	/// <summary>
	/// Returns and Creates a scoped pointer.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<typename T, typename ...Args>
	inline Scoped<T> CreateScoped(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	/// <summary>
	/// Returns and Creates a shared pointer.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<typename T, typename ...Args>
	inline Shared<T> CreateShared(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename FirstType, typename SecondType>
	inline Pair<FirstType, SecondType> CreatePair(FirstType&& first, SecondType&& second)
	{
		return std::make_pair(std::forward<FirstType>(first), std::forward<SecondType>(second));
	}

	inline UInt GetRandomNumber(UInt min = 0, UInt max = 0)
	{
		static bool isFirst = true;
		if (isFirst)
		{
			srand(Cast<UInt>(time(nullptr)));
			isFirst = false;
		}
		return min + rand() % ((max + 1) - min);
	}

	/// <summary>
	/// Returns the time spend between every frame.
	/// </summary>
	/// <returns></returns>
	inline float GetDeltaTime()
	{
		static Timestep lastFrameTime;
		Timestep currentTime;
		float deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		return deltaTime;
	}

	/// <summary>
	/// Returns the refresh rate of the current screen.
	/// </summary>
	/// <returns></returns>
	inline int GetScreenRefreshRate()
	{
		HDC hdc = GetDC(nullptr);
		int refreshRate = GetDeviceCaps(hdc, VREFRESH);
		ReleaseDC(nullptr, hdc);
		return refreshRate;
	}

	// Transition timing functions

	inline float Lerp(float start, float end, float progress)
	{
		return start + (end - start) * progress;
	}

	inline float Ease(float progress)
	{
		return Cast<float>(std::pow(progress, 2.0f)) / (2.0f * progress - progress + 1.0f);
	}

	inline float EaseIn(float progress)
	{
		return Cast<float>(pow(progress, 2.0f));
	}

	inline float EaseOut(float progress) {
		return 1.0f - Cast<float>(pow(1.0f - progress, 2.0f));
	}

	inline float EaseInOut(float progress) {
		return progress < 0.5f ? 4.0f * progress * progress * progress :
			1.0f - Cast<float>(pow(-2.0f * progress + 2.0f, 3.0f)) / 2.0f;
	}

}