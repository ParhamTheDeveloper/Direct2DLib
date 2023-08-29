#pragma once

#include "Renderer.h"

namespace D2DLib
{

	D2DLIB_API Renderer* InitializeVirtualRenderer();
	D2DLIB_API void ShutdownVirtualRenderer();
	D2DLIB_API Renderer* GetMainRenderer();

	D2DLIB_API void BeginDraw();
	D2DLIB_API void EndDraw();

	// Backward compatibility for rendering with only shape style

	D2DLIB_API void ClearScreen(const Color& color = Color());

	D2DLIB_API void DrawRectangle(
		const ShapeStyle& rectangle,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawCircle(
		const ShapeStyle& circle,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawTriangle(
		const ShapeStyle& triangle,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawTriangle(
		const Vector2& vertexA,
		const Vector2& vertexB,
		const Vector2& vertexC,
		const ShapeStyle& style,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawLine(
		const ShapeStyle& line,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	// Rendering with a specific shape style

	D2DLIB_API void ClearScreen(
		ID2D1Brush* brush,
		bool immediate = false
	);

	D2DLIB_API void DrawRectangle(
		const RectangleStyle& rectangle,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawCircle(
		const CircleStyle& circle,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawTriangle(
		const TriangleStyle& triangle,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawLine(
		const LineStyle& line,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void DrawMesh(const Mesh<MeshType::Rectangle>& mesh);
	D2DLIB_API void DrawMesh(const Mesh<MeshType::Circle>& mesh);
	D2DLIB_API void DrawMesh(const Mesh<MeshType::Triangle>& mesh);
	D2DLIB_API void DrawMesh(const Mesh<MeshType::Custom>& mesh);

	D2DLIB_API void RenderText(
		const String& text,
		const TextStyle& style,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

	D2DLIB_API void RenderTexture(
		Texture& texture,
		const D2D1::Matrix3x2F& transform = D2D1::Matrix3x2F::Identity()
	);

}