#pragma once

#include "Direct2DLib/Core/Graphics.h"
#include "Direct2DLib/Core/Color.h"
#include "Direct2DLib/Core/Styles.h"

namespace D2DLib
{

	struct ResourceDeleter
	{
		template<typename T>
		void operator() (T* pResource)
		{
			SafeRelease(&pResource);
		}
	};

	template<typename T>
	using Resource = T*;

	struct GradientStop
	{
		float Position;
		Color Color;
	};

	class ResourceManager
	{
	public:
		ResourceManager(Graphics* gfx = nullptr);

		Resource<ID2D1SolidColorBrush> CreateBrush(const Color& color);
		Resource<ID2D1LinearGradientBrush> CreateBrush(
			const ShapeStyle& style,
			const Vector<GradientStop>& stops,
			float rotation = 0.0f
		);
		Resource<ID2D1RadialGradientBrush> CreateBrush(
			const ShapeStyle& style,
			const Vector<GradientStop>& stops,
			const Vector2& center,
			bool centered = false
		);
	private:
		ID2D1DeviceContext6* m_RenderTarget = nullptr;
		ID2D1Factory* m_Factory = nullptr;
		static ResourceManager* s_Instance;
	private:
		friend void InitializeVirtualResourceManager();
		friend void ShutdownVirtualResourceManager();
		friend ResourceManager* GetMainResourceManager();
	};

}