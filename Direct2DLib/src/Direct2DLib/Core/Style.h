#pragma once

#include "Base.h"
#include "Color.h"
#include "Resource.h"
#include "Brush.h"
#include "Direct2DLib/Math/Math.h"

#define D2DLIB_DECLARE_STYLE_CTOR(styleName, ...)					\
	styleName(														\
		float width = 0.0f, float height = 0.0f,					\
		const Vector2& position = { 0.0f, 0.0f },					\
		const Brush& backgroundColor = nullptr,						\
		##__VA_ARGS__												\
	) :																\
		Style(														\
			width, height, position,								\
			backgroundColor											\
		),

#define D2DLIB_DECLARE_SHAPE_STYLE_CTOR(styleName, sides, ...)		\
	styleName(														\
		float width = 0.0f, float height = 0.0f,					\
		const Vector2& position = { 0.0f, 0.0f },					\
		const Brush& backgroundColor = nullptr,						\
		const Vector2 borderRadius = Vector2(),						\
		D2DLib::Outline outline = D2DLib::Outline(),				\
		##__VA_ARGS__												\
	) :																\
		ShapeStyle(													\
			width, height, position,								\
			backgroundColor, borderRadius, outline,					\
			sides													\
		),

namespace D2DLib
{

	class D2DLIB_API Style
	{
	public:
		Style(
			float width = 0.0f, float height = 0.0f,
			const Vector2& position = Vector2(),
			const Brush& backgroundColor = nullptr
		)
			:
			Width(width), Height(height), Position(position),
			BackgroundColor(backgroundColor)
		{
		}
	public:
		float Width, Height;
		Vector2 Position;
		Brush BackgroundColor;
	};

}