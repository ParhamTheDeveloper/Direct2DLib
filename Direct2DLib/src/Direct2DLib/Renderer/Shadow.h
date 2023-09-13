#pragma once

#include "RendererGlobal.h"

namespace D2DLib
{

	class D2DLIB_API Shadow
	{
	public:
		Shadow(
			const Vector2& vertexA,
			const Vector2& vertexB,
			const CircleStyle& lightStyle,
			const ShapeStyle& style,
			bool soft = false
		) :
			m_Factory(GetMainGraphics()->GetFactory()),
			m_RenderTarget(GetMainGraphics()->GetDeviceContext()),
			m_VertexA(vertexA),
			m_VertexB(vertexB),
			m_Style(style),
			m_LightStyle(lightStyle),
			m_Soft(soft)
		{
			HRESULT hr = m_RenderTarget->CreateCompatibleRenderTarget(&m_BitmapRenderTarget);
			
			if (FAILED(hr))
			{
				throw std::runtime_error("Can not create a D2D1 Compatible Render Target (ID2DBitmapRenderTarget)!");
			}

			const Vector2 lightPosition = m_LightStyle.Position + m_LightStyle.Radius;
			m_SA = (m_VertexA - lightPosition) * m_LightStyle.Radius;
			m_EA = m_VertexA + m_SA;

			m_SB = (m_VertexB - lightPosition) * m_LightStyle.Radius;
			m_EB = m_VertexB + m_SB;
		}

		~Shadow()
		{
			SafeRelease(&m_MultiThread);
			
			if (!m_Soft)
			{
				SafeRelease(&m_BitmapRenderTarget);
			}
		}

		void Draw()
		{
			if (m_LightStyle.BackgroundColor)
			{
				HRESULT hr = m_Factory->QueryInterface(&m_MultiThread);

				if (SUCCEEDED(hr))
				{
					m_MultiThread->Enter();
					
					if (m_Soft)
					{
						m_BitmapRenderTarget->BeginDraw();
						DrawShadowTriangle(m_VertexA, m_EA, m_EB, m_Style);
						DrawShadowTriangle(m_VertexA, m_VertexB, m_EB, m_Style);
						m_BitmapRenderTarget->EndDraw();
						DrawBitmap();
					}
					else
					{
						DrawTriangle(m_VertexA, m_EA, m_EB, m_Style);
						DrawTriangle(m_VertexA, m_VertexB, m_EB, m_Style);
					}
					m_MultiThread->Leave();
				}
			}
		}
	private:
		void DrawBitmap()
		{
			ID2D1Bitmap* pBitmap = nullptr;
			ID2D1Effect* pBlurEffect = nullptr;
			HRESULT hr = m_RenderTarget->CreateEffect(CLSID_D2D1GaussianBlur, &pBlurEffect);

			if (SUCCEEDED(hr))
			{
				hr = m_BitmapRenderTarget->GetBitmap(&pBitmap);

				if (SUCCEEDED(hr))
				{
					pBlurEffect->SetInput(0, pBitmap);
					hr = pBlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 2.5f);

					if (SUCCEEDED(hr))
					{
						m_RenderTarget->DrawImage(pBlurEffect);
					}
					SafeRelease(&m_BitmapRenderTarget);
				}
				SafeRelease(&pBitmap);
			}
			SafeRelease(&pBlurEffect);
		}
		
		void DrawShadowTriangle(
			const Vector2& vertexA,
			const Vector2& vertexB,
			const Vector2& vertexC,
			const ShapeStyle& style
		)
		{
			ID2D1PathGeometry* pPathGeometry = nullptr;
			HRESULT hr = m_Factory->CreatePathGeometry(&pPathGeometry);
			
			if (SUCCEEDED(hr))
			{
				ID2D1GeometrySink* pSink = nullptr;
				hr = pPathGeometry->Open(&pSink);
				
				if (SUCCEEDED(hr))
				{
					const float positionX = style.Position.X;
					const float positionY = style.Position.Y;

					pSink->BeginFigure(D2D1::Point2F(vertexA.X + positionX, vertexA.Y + positionY), D2D1_FIGURE_BEGIN_FILLED);
					pSink->AddLine(D2D1::Point2F(vertexB.X + positionX, vertexB.Y + positionY));
					pSink->AddLine(D2D1::Point2F(vertexC.X + positionX, vertexC.Y + positionY));
					pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
					hr = pSink->Close();

					if (SUCCEEDED(hr))
					{
						m_BitmapRenderTarget->FillGeometry(pPathGeometry, style.BackgroundColor);
					}
				}
				SafeRelease(&pSink);
			}
			SafeRelease(&pPathGeometry);
		}
	private:
		ID2D1Factory* m_Factory = nullptr;
		ID2D1DeviceContext6* m_RenderTarget = nullptr;
		ID2D1BitmapRenderTarget* m_BitmapRenderTarget = nullptr;
		ID2D1Multithread* m_MultiThread = nullptr;
		Vector2 m_VertexA, m_VertexB, m_SA, m_SB, m_EA, m_EB;
		ShapeStyle m_Style;
		CircleStyle m_LightStyle;
		bool m_Soft;
	};

}