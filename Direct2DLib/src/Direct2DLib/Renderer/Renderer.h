#pragma once

#include "Direct2DLib/Core/Graphics.h"
#include "Direct2DLib/Core/Styles.h"
#include "Direct2DLib/Core/Texture.h"
#include "Direct2DLib/Renderer/Camera.h"

namespace D2DLib
{

	class Renderer
	{
	public:
		Renderer(Graphics* gfx = nullptr);

		void BeginDraw();
		void EndDraw();

		// Backward compatibility for rendering with only shape style

		void ClearScreen(const Color& color = Color());
		void DrawRectangle(
			const ShapeStyle& rectangle,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void DrawCircle(
			const ShapeStyle& circle,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void DrawTriangle(
			const ShapeStyle& triangle,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void DrawTriangle(
			const Vector2& vertexA,
			const Vector2& vertexB,
			const Vector2& vertexC,
			const ShapeStyle& style,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void DrawLine(
			const ShapeStyle& line,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);

		// Rendering with a specific shape style

		void ClearScreen(
			ID2D1Brush* brush,
			bool immediate = false
		);
		void DrawRectangle(
			const RectangleStyle& rectangle,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void DrawCircle(
			const CircleStyle& circle,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void DrawTriangle(
			const TriangleStyle& triangle,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void DrawLine(
			const LineStyle& line,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void RenderText(
			const String& text,
			const TextStyle& style,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
		void RenderTexture(
			Texture& texture,
			const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
		);
	private:
		ID2D1StrokeStyle* CreateStrokeStyle(
			D2D1_CAP_STYLE capStyle,
			D2D1_LINE_JOIN lineJoin,
			D2D1_DASH_STYLE dashStyle
		);
		void SetTransform(const D2D1::Matrix3x2F& transform);
		void ResetTranform();
	private:
		ID2D1DeviceContext6* m_RenderTarget = nullptr;
		ID2D1Factory* m_Factory = nullptr;
		IDWriteFactory* m_DWriteFactory = nullptr;
		static Renderer* s_Instance;
	private:
		friend Renderer* InitVirtualRenderer();
		friend void ShutdownVirtualRenderer();
		friend Renderer* GetMainRenderer();
	};

}