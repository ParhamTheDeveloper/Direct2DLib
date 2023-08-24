#include "pch.h"
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
		if (g_ResourceManager)
		{
			delete g_ResourceManager;
			g_ResourceManager = nullptr;
		}
	}

	ResourceManager* GetMainResourceManager()
	{
		return ResourceManager::s_Instance;
	}

	Resource<ID2D1SolidColorBrush> CreateBrush(const Color& color)
	{
		return g_ResourceManager->CreateBrush(color);
	}

	Resource<ID2D1LinearGradientBrush> CreateBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		float rotation
	)
	{
		return g_ResourceManager->CreateBrush(style, stops, rotation);
	}

	Resource<ID2D1RadialGradientBrush> CreateBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		const Vector2& center,
		bool centered
	)
	{
		return g_ResourceManager->CreateBrush(style, stops, center, centered);
	}

}