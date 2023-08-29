#pragma once

#include "Direct2DLib/Core/Graphics.h"
#include "Direct2DLib/Core/Styles.h"
#include "Boundary.h"

namespace D2DLib
{

	enum class D2DLIB_API MeshType
	{
		Rectangle,
		Triangle,
		Circle,
		Custom
	};

	template<MeshType Type>
	class D2DLIB_API Mesh
	{
	public:
		Mesh(ShapeStyle& style, Graphics* gfx = nullptr) :
			m_Factory(gfx ? gfx->GetFactory() : GetMainGraphics()->GetFactory()),
			m_RenderTarget(gfx ? gfx->GetDeviceContext() : GetMainGraphics()->GetDeviceContext()),
			m_Style(style)
		{
			HRESULT hr = m_Factory->CreatePathGeometry(&m_Path);
			if (SUCCEEDED(hr))
			{
				hr = m_Path->Open(&m_Sink);

				if (FAILED(hr))
				{
					throw std::runtime_error("Can not create the geometry sink!");
				}
			}
		}

		void AddLine(const Vector2& point)
		{
			if (!m_HasBegun)
			{
				m_Sink->BeginFigure(Vector2ToPoint2F(point), D2D1_FIGURE_BEGIN_FILLED);
				m_HasBegun = true;
			}
			else
			{
				m_Sink->AddLine(Vector2ToPoint2F(point));
			}
		}

		ID2D1PathGeometry* GetGeometry() const
		{
			m_Sink->EndFigure(D2D1_FIGURE_END_CLOSED);
			m_Sink->Close();
			return m_Path;
		}

		const ShapeStyle& GetStyle() const { return m_Style; }
		const MeshType GetType() const { return Type; }
	private:
		const D2D1_POINT_2F Vector2ToPoint2F(const Vector2& vec) const
		{
			return D2D1::Point2F(vec.X, vec.Y);
		}
	private:
		ID2D1PathGeometry* m_Path = nullptr;
		ID2D1GeometrySink* m_Sink = nullptr;
		ID2D1Factory* m_Factory = nullptr;
		ID2D1DeviceContext6* m_RenderTarget = nullptr;
		ShapeStyle& m_Style = nullptr;
		bool m_HasBegun = false;
	};

}