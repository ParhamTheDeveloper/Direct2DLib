#pragma once

#include "Base.h"
#include "Color.h"
#include "Direct2DLib/Math/Math.h"

#define D2DLIB_DECLARE_STYLE_CTOR(styleName, ...)				\
	styleName(													\
		float width = 0.0f, float height = 0.0f,				\
		const Vector2& position = { 0.0f, 0.0f },				\
		ID2D1Brush* backgroundColor = nullptr,					\
		##__VA_ARGS__											\
	) :															\
		Style(													\
			width, height, position,							\
			backgroundColor										\
		),

#define D2DLIB_DECLARE_SHAPE_STYLE_CTOR(styleName, sides, ...)		\
	styleName(														\
		float width = 0.0f, float height = 0.0f,					\
		const Vector2& position = { 0.0f, 0.0f },					\
		ID2D1Brush* backgroundColor = nullptr,						\
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

	class Style
	{
	public:
		Style(
			float width = 0.0f, float height = 0.0f,
			const Vector2& position = Vector2(),
			ID2D1Brush* backgroundColor = nullptr
		)
			:
			Width(width), Height(height), Position(position),
			BackgroundColor(backgroundColor)
		{
		}
	public:
		float Width, Height;
		Vector2 Position;
		ID2D1Brush* BackgroundColor;
	};

}