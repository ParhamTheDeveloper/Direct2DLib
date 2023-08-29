#pragma once

#include "Direct2DLib/Core/Graphics.h"
#include "Direct2DLib/Core/Color.h"
#include "Direct2DLib/Core/Styles.h"

namespace D2DLib
{

	struct D2DLIB_API ResourceDeleter
	{
		template<typename T>
		void operator() (T* pResource)
		{
			SafeRelease(&pResource);
		}
	};

	struct D2DLIB_API GradientStop
	{
		float Position;
		Color Color;
	};

	class D2DLIB_API ResourceManager
	{
	public:
		ResourceManager(Graphics* gfx = nullptr);

		const Brush CreateBrush(const Color& color);
		const Brush CreateLinearGradientBrush(
			const ShapeStyle& style,
			const Vector<GradientStop>& stops,
			float rotation
		);
		const Brush CreateRadialGradientBrush(
			const ShapeStyle& style,
			const Vector<GradientStop>& stops,
			const Vector2& center,
			bool centered = false
		);
		const Brush CreateRadialGradientBrush(
			const CircleStyle& style,
			const Vector<GradientStop>& stops,
			const Vector2& center,
			bool centered = false
		);
		const Brush CreateRadialGradientBrush(
			const ShapeStyle& style,
			const Vector<GradientStop>& stops,
			bool centered = true
		);
		const Brush CreateRadialGradientBrush(
			const CircleStyle& style,
			const Vector<GradientStop>& stops,
			bool centered = true
		);

		void ReleaseResource(Resource& resource);
	private:
		ID2D1DeviceContext6* m_RenderTarget = nullptr;
		ID2D1Factory* m_Factory = nullptr;
		static ResourceManager* s_Instance;
	private:
		friend D2DLIB_API void InitializeVirtualResourceManager();
		friend D2DLIB_API void ShutdownVirtualResourceManager();
		friend D2DLIB_API ResourceManager* GetMainResourceManager();
	};

}