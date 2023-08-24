#include "pch.h"
#include "RendererGlobal.h"

namespace D2DLib
{

	// Global namespace functions

	Renderer* GetMainRenderer()
	{
		return Renderer::s_Instance;
	}

	// Initializer

	Renderer* g_Renderer = nullptr;

	Renderer* InitializeVirtualRenderer()
	{
		g_Renderer = new Renderer();
		return g_Renderer;
	}

	void ShutdownVirtualRenderer()
	{
		SafeRelease(g_Renderer);
	}

	// Initializer

	void BeginDraw()
	{
		g_Renderer->BeginDraw();
	}

	void EndDraw()
	{
		g_Renderer->EndDraw();
	}

	void ClearScreen(const Color& color)
	{
		g_Renderer->ClearScreen(color);
	}

	void DrawRectangle(
		const ShapeStyle& rectangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawRectangle(rectangle, transform);
	}

	void DrawCircle(
		const ShapeStyle& circle,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawCircle(circle, transform);
	}

	void DrawTriangle(
		const ShapeStyle& triangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawTriangle(triangle, transform);
	}

	void DrawTriangle(
		const Vector2& vertexA,
		const Vector2& vertexB,
		const Vector2& vertexC,
		const ShapeStyle& style,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawTriangle(
			vertexA,
			vertexB,
			vertexC,
			style,
			transform
		);
	}

	void DrawLine(
		const ShapeStyle& line,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawLine(line, transform);
	}

	void ClearScreen(
		ID2D1Brush* brush,
		bool immediate
	)
	{
		g_Renderer->ClearScreen(brush, immediate);
	}

	void DrawRectangle(
		const RectangleStyle& rectangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawRectangle(rectangle, transform);
	}

	void DrawCircle(
		const CircleStyle& circle,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawCircle(circle, transform);
	}

	void DrawTriangle(
		const TriangleStyle& triangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawTriangle(triangle, transform);
	}

	void DrawLine(
		const LineStyle& line,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->DrawLine(line, transform);
	}

	void RenderText(
		const String& text,
		const TextStyle& style,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->RenderText(text, style, transform);
	}

	void RenderTexture(
		Texture& texture,
		const D2D1::Matrix3x2F& transform
	)
	{
		g_Renderer->RenderTexture(texture, transform);
	}

}