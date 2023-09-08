#include "Direct2DLibpch.h"
#include "ResourceManagerGlobal.h"

namespace D2DLib
{

	ResourceManager* g_ResourceManager = nullptr;

	void InitializeVirtualResourceManager()
	{
		g_ResourceManager = new ResourceManager();
	}

	void ShutdownVirtualResourceManager()
	{
		SafeRelease(g_ResourceManager);
	}

	ResourceManager* GetMainResourceManager()
	{
		return ResourceManager::s_Instance;
	}

	const Brush CreateBrush(const Color& color)
	{
		return g_ResourceManager->CreateBrush(color);
	}

	const Brush CreateLinearGradientBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		float rotation
	)
	{
		return g_ResourceManager->CreateLinearGradientBrush(style, stops, rotation);
	}

	const Brush CreateRadialGradientBrush(
		const CircleStyle& style,
		const Vector<GradientStop>& stops,
		const Vector2& center,
		bool centered
	)
	{
		return g_ResourceManager->CreateRadialGradientBrush(style, stops, center, centered);
	}

	const Brush CreateRadialGradientBrush(
		const CircleStyle& style,
		const Vector<GradientStop>& stops,
		bool centered
	)
	{
		return g_ResourceManager->CreateRadialGradientBrush(style, stops, centered);
	}

	D2DLIB_API void ReleaseResource(Resource& resource)
	{
		g_ResourceManager->ReleaseResource(resource);
	}

	const Brush CreateBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		const Vector2& center,
		bool centered
	)
	{
		return g_ResourceManager->CreateRadialGradientBrush(style, stops, center, centered);
	}

	const Brush CreateBrush(
		const CircleStyle& style,
		const Vector<GradientStop>& stops,
		const Vector2& center,
		bool centered = false
	)
	{
		return g_ResourceManager->CreateRadialGradientBrush(style, stops, center, centered);
	}

	const Brush CreateBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		bool centered
	)
	{
		return g_ResourceManager->CreateRadialGradientBrush(style, stops, centered);
	}

}