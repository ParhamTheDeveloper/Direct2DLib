#include "pch.h"
#include "ResourceManager.h"

namespace D2DLib
{

	ResourceManager* ResourceManager::s_Instance = nullptr;

	ResourceManager::ResourceManager(Graphics* gfx) :
		m_Factory(gfx ? gfx->GetFactory() : GetMainGraphics()->GetFactory()),
		m_RenderTarget(gfx ? gfx->GetDeviceContext() : GetMainGraphics()->GetDeviceContext())
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
	}

	const Brush ResourceManager::CreateBrush(const Color& color)
	{
		ID2D1SolidColorBrush* pSolidColorBrush = nullptr;
		m_RenderTarget->CreateSolidColorBrush(color, &pSolidColorBrush);
		return pSolidColorBrush;
	}

	const Brush ResourceManager::CreateLinearGradientBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		float rotation
	)
	{
		ID2D1GradientStopCollection* pCollection = nullptr;
		D2D1_GRADIENT_STOP* gradientStops = new D2D1_GRADIENT_STOP[stops.size()];
		for (size_t i = 0; i < stops.size(); i++)
		{
			gradientStops[i].position = stops[i].Position;
			gradientStops[i].color = stops[i].Color;
		}
		HRESULT hr = m_RenderTarget->CreateGradientStopCollection(
			gradientStops,
			static_cast<UInt32>(stops.size()),
			&pCollection
		);

		delete[] gradientStops;

		if (SUCCEEDED(hr))
		{
			ID2D1LinearGradientBrush* pBrush = nullptr;
			hr = m_RenderTarget->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(style.Position.X, style.Position.Y + style.Height / 2.0f),
					D2D1::Point2F(style.Position.X + style.Width, style.Position.Y + style.Height / 2.0f)
				),
				pCollection,
				&pBrush
			);
			pCollection->Release(); // Release the gradient stop collection after creating the brush
			if (SUCCEEDED(hr))
			{
				return pBrush;
			}
		}
		return nullptr;
	}

	const Brush ResourceManager::CreateRadialGradientBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		const Vector2& center,
		bool centered
	)
	{
		ID2D1GradientStopCollection* pCollection = nullptr;
		D2D1_GRADIENT_STOP* gradientStops = new D2D1_GRADIENT_STOP[stops.size()];
		for (size_t i = 0; i < stops.size(); i++)
		{
			gradientStops[i].position = stops[i].Position;
			gradientStops[i].color = stops[i].Color;
		}
		HRESULT hr = m_RenderTarget->CreateGradientStopCollection(
			gradientStops,
			static_cast<UInt32>(stops.size()),
			&pCollection
		);

		delete[] gradientStops;

		if (SUCCEEDED(hr))
		{
			ID2D1RadialGradientBrush* pBrush = nullptr;
			float radius = min(style.Width, style.Height) / 2.0f;
			D2D1_POINT_2F centerPoint = centered ?
				D2D1::Point2F(style.Width / 2.0f + style.Position.X, style.Height / 2.0f + style.Position.Y) :
				D2D1::Point2F(center.X + style.Position.X, center.Y + style.Position.Y);

			hr = m_RenderTarget->CreateRadialGradientBrush(
				D2D1::RadialGradientBrushProperties(
					centerPoint,
					D2D1::Point2F(), radius, radius
				),
				pCollection,
				&pBrush
			);
			pCollection->Release(); // Release the gradient stop collection after creating the brush
			
			if (SUCCEEDED(hr))
			{
				return pBrush;
			}
		}
		return nullptr;
	}

	const Brush ResourceManager::CreateRadialGradientBrush(const CircleStyle& style, const Vector<GradientStop>& stops, const Vector2& center, bool centered)
	{
		ID2D1GradientStopCollection* pCollection = nullptr;
		D2D1_GRADIENT_STOP* gradientStops = new D2D1_GRADIENT_STOP[stops.size()];
		for (size_t i = 0; i < stops.size(); i++)
		{
			gradientStops[i].position = stops[i].Position;
			gradientStops[i].color = stops[i].Color;
		}
		HRESULT hr = m_RenderTarget->CreateGradientStopCollection(
			gradientStops,
			static_cast<UInt32>(stops.size()),
			&pCollection
		);

		delete[] gradientStops;

		if (SUCCEEDED(hr))
		{
			ID2D1RadialGradientBrush* pBrush = nullptr;
			D2D1_POINT_2F centerPoint = centered ?
				D2D1::Point2F(style.Radius.X + style.Position.X, style.Radius.Y + style.Position.Y) :
				D2D1::Point2F(center.X + style.Position.X, center.Y + style.Position.Y);

			hr = m_RenderTarget->CreateRadialGradientBrush(
				D2D1::RadialGradientBrushProperties(
					centerPoint,
					D2D1::Point2F(), style.Radius.X, style.Radius.Y
				),
				pCollection,
				&pBrush
			);
			pCollection->Release(); // Release the gradient stop collection after creating the brush

			if (SUCCEEDED(hr))
			{
				return pBrush;
			}
		}
		return nullptr;
	}

	const Brush ResourceManager::CreateRadialGradientBrush(
		const ShapeStyle& style,
		const Vector<GradientStop>& stops,
		bool centered
	)
	{
		return CreateRadialGradientBrush(style, stops, 0.0f, centered);
	}

	const Brush ResourceManager::CreateRadialGradientBrush(
		const CircleStyle& style,
		const Vector<GradientStop>& stops,
		bool centered
	)
	{
		return CreateRadialGradientBrush(style, stops, 0.0f, centered);
	}

	void ResourceManager::ReleaseResource(Resource& resource)
	{
		resource.Release();
	}

}
