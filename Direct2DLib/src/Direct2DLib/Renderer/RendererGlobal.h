#pragma once

#include "Renderer.h"

namespace D2DLib
{

	Renderer* InitializeVirtualRenderer();
	void ShutdownVirtualRenderer();
	Renderer* GetMainRenderer();

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

}