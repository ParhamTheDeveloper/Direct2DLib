#pragma once

#include "Style.h"
#include "Utils.h"

namespace D2DLib
{

	class D2DLIB_API WindowStyle
	{
	public:
		WindowStyle(
			float width = 0.0f, float height = 0.0f,
			const Vector2& position = 0.0f,
			const Color& backgroundColor = Color(),
			bool isMaximized = false,
			DWORD extraWindowStyles = 0,
			DWORD windowStyles = WS_OVERLAPPEDWINDOW
		) :
			Width(width), Height(height), Position(position),
			BackgroundColor(backgroundColor),
			IsMaximized(isMaximized),
			WindowStyles(windowStyles),
			ExtraWindowStyles(extraWindowStyles)
		{
		}

		/// <summary>
		/// <para>Returns the actual size of the window after the creation of the window</para>
		/// </summary>
		/// <returns>A style containing the window client's size</returns>
		const Style ComputeClientSize()
		{
			RECT rc = {
				Cast<long>(Position.X),
				Cast<long>(Position.Y),
				Cast<long>(Width - Position.X),
				Cast<long>(Height - Position.Y)
			};

			// We can't use GetClientRect because we don't have access to the window's hwnd,
			// So we use AdjustWindowRectEx to get the client rect which includes the sizes we need

			bool isOk = AdjustWindowRectEx(&rc, WindowStyles, false, ExtraWindowStyles);
			if (isOk)
			{
				UInt clientWidth = rc.right - rc.left;
				UInt clientHeight = rc.bottom - rc.top;
				Style clientStyle = {
					Cast<float>(clientWidth),
					Cast<float>(clientWidth)
				};
				return clientStyle;
			}
			return { }; // Empty style
		}
	public:
		float Width, Height;
		Vector2 Position;
		Color BackgroundColor;
		bool IsMaximized;
		DWORD WindowStyles;
		DWORD ExtraWindowStyles;
	};

	struct D2DLIB_API Outline
	{
		Outline(
			float width = 0.0f,
			const Brush& color = nullptr
		)
			: Width(width), Color(color)
		{
		}

		float Width;
		Brush Color;
	};

	enum class D2DLIB_API ShapeStyleType : UInt8
	{
		Default,
		Rectangle,
		Circle,
		Triangle,
		Text
	};

	class D2DLIB_API ShapeStyle : public Style
	{
	public:
		D2DLIB_DECLARE_STYLE_CTOR(
			ShapeStyle,
			const Vector2& borderRadius = 0.0f,
			Outline outline = D2DLib::Outline(),
			UInt sides = 2.0f
		)
			BorderRadius(borderRadius),
			Outline(outline),
			Sides(sides)
		{
		}

		const UInt& GetSides() const { return Sides; }
		virtual const ShapeStyleType GetType() const { return ShapeStyleType::Default; }
	public:
		Vector2 BorderRadius;
		Outline Outline;
		UInt Sides;
	};
	
	class D2DLIB_API RectangleStyle : public ShapeStyle
	{
	public:
		D2DLIB_DECLARE_SHAPE_STYLE_CTOR(
			RectangleStyle,
			4,
			bool isLine = false
		)
			IsLine(isLine)
		{
		}

		const ShapeStyleType GetType() const override { return ShapeStyleType::Rectangle; }
	private:
		bool IsLine;
	};

	class D2DLIB_API TriangleStyle : public ShapeStyle
	{
	public:
		D2DLIB_DECLARE_SHAPE_STYLE_CTOR(
			TriangleStyle,
			3,
			const Vector2& vertexA = 0.0f,
			const Vector2& vertexB = 0.0f,
			const Vector2& vertexC = 0.0f
		)
			VertexA(vertexA),
			VertexB(vertexB),
			VertexC(vertexC)
		{
		}

		const ShapeStyleType GetType() const override { return ShapeStyleType::Triangle; }
	public:
		Vector2 VertexA;
		Vector2 VertexB;
		Vector2 VertexC;
	};

	class D2DLIB_API CircleStyle : public ShapeStyle
	{
	public:
		D2DLIB_DECLARE_SHAPE_STYLE_CTOR(
			CircleStyle,
			Cast<UInt>(D2D1::FloatMax()),
			const Vector2& radius = Vector2()
		)
			Radius(radius)
		{
		}
	public:
		Vector2 Radius;
	};

	class D2DLIB_API LineStyle : public ShapeStyle
	{
	public:
		D2DLIB_DECLARE_SHAPE_STYLE_CTOR(
			LineStyle,
			1,
			const Vector2& start = Vector2(),
			const Vector2& end = Vector2()
		)
			Start(start),
			End(end)
		{
		}

		const ShapeStyleType GetType() const override { return ShapeStyleType::Circle; }
	public:
		Vector2 Start, End;
	};

	class D2DLIB_API Font
	{
	public:
		Font(
			float fontSize = 16.0f,
			const String& fontFamily = L"Arial",
			DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL
		)
			:
			FontSize(fontSize),
			FontWeight(fontWeight),
			FontStyle(fontStyle),
			FontStretch(fontStretch),
			FontFamily(fontFamily)
		{
		}
	public:
		float FontSize;
		String FontFamily;
		DWRITE_FONT_WEIGHT FontWeight;
		DWRITE_FONT_STYLE FontStyle;
		DWRITE_FONT_STRETCH FontStretch;
	};

	enum class D2DLIB_API TextVerticalAlignment
	{
		Leading,
		Trailing,
		Center,
		Justify
	};

	enum class D2DLIB_API TextHorizontalAlignment
	{
		Near,
		Far,
		Center
	};

	class D2DLIB_API TextStyle : public ShapeStyle
	{
	public:
		D2DLIB_DECLARE_SHAPE_STYLE_CTOR(
			TextStyle,
			0,
			const Brush& Color = nullptr,
			D2DLib::Font font = D2DLib::Font(),
			TextVerticalAlignment verticalAligment = TextVerticalAlignment::Leading,
			TextHorizontalAlignment horizontalAligment = TextHorizontalAlignment::Near
		)
			Font(font),
			Color(Color),
			VerticalAligment(verticalAligment),
			HorizontalAligment(horizontalAligment)
		{
		}

		const ShapeStyleType GetType() const override { return ShapeStyleType::Text; }
	public:
		Font Font;
		Brush Color;
		TextVerticalAlignment VerticalAligment;
		TextHorizontalAlignment HorizontalAligment;
	};

}