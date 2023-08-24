#pragma once

#include "ResourceManager.h"

namespace D2DLib
{

	void InitializeVirtualResourceManager();
	void ShutdownVirtualResourceManager();
	ResourceManager* GetMainResourceManager();

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

}