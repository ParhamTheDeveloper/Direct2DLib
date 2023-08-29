#pragma once

#include "ResourceManager.h"

namespace D2DLib
{

	D2DLIB_API void InitializeVirtualResourceManager();
	D2DLIB_API void ShutdownVirtualResourceManager();
	D2DLIB_API ResourceManager* GetMainResourceManager();

	D2DLIB_API const Brush CreateBrush(const Color& color);
	D2DLIB_API const Brush CreateLinearGradientBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		float rotation
	);
	D2DLIB_API const Brush CreateRadialGradientBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		const Vector2& center,
		bool centered = false
	);
	D2DLIB_API const Brush CreateRadialGradientBrush(
		const CircleStyle& style,
		const Vector<GradientStop>& stops,
		const Vector2& center,
		bool centered = false
	);
	D2DLIB_API const Brush CreateRadialGradientBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		bool centered = true
	);
	D2DLIB_API const Brush CreateRadialGradientBrush(
		const CircleStyle& style,
		const Vector<GradientStop>& stops,
		bool centered = true
	);

	D2DLIB_API inline void ReleaseResource(Resource& resource);

}