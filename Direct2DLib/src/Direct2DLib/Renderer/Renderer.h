#pragma once

#include "Direct2DLib/Core/Graphics.h"
#include "Direct2DLib/Core/Styles.h"
#include "Direct2DLib/Core/Texture.h"
#include "Direct2DLib/Renderer/Camera.h"
#include "Direct2DLib/Renderer/Mesh.h"

namespace D2DLib
{

	class D2DLIB_API Renderer
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

		template<MeshType Type>
		void DrawMesh(const Mesh<Type>& mesh)
		{
			ShapeStyle style = mesh.GetStyle();
			switch (Type)
			{
				case MeshType::Rectangle:
					{
						DrawRectangle(*SafeCast<RectangleStyle>(&style));
					}
					break;

				case MeshType::Circle:
					{
						DrawCircle(*SafeCast<CircleStyle>(&style));
					}
					break;
				
				case MeshType::Triangle:
					{
						DrawTriangle(*SafeCast<TriangleStyle>(&style));
					}
					break;

				case MeshType::Custom:
					{
						auto pathGeometry = mesh.GetGeometry();
						if (style.Outline.Width && style.Outline.Color)
						{
							D2D1_CAP_STYLE capStyle = style.BorderRadius.IsNonZero() ? D2D1_CAP_STYLE_ROUND : D2D1_CAP_STYLE_FLAT;
							D2D1_LINE_JOIN lineJoin = style.BorderRadius.IsNonZero() ? D2D1_LINE_JOIN_ROUND : D2D1_LINE_JOIN_MITER;
							ID2D1StrokeStyle* pStrokeStyle = CreateStrokeStyle(capStyle, lineJoin, D2D1_DASH_STYLE_SOLID);

							if (pStrokeStyle)
							{
								if (style.Outline.Width)
								{
									m_RenderTarget->DrawGeometry(
										pathGeometry,
										style.Outline.Color,
										style.Outline.Width,
										pStrokeStyle
									);
								}
								SafeRelease(&pStrokeStyle);
							}
						}
						m_RenderTarget->FillGeometry(
							pathGeometry,
							style.BackgroundColor
						);
					}
					break;
			}
		}

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
		friend D2DLIB_API Renderer* InitVirtualRenderer();
		friend D2DLIB_API void ShutdownVirtualRenderer();
		friend D2DLIB_API Renderer* GetMainRenderer();
	};

}