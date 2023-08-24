#include "pch.h"
#include "Renderer.h"

namespace D2DLib
{

	Renderer* Renderer::s_Instance = nullptr;

	Renderer::Renderer(Graphics* gfx) :
		m_Factory(gfx ? gfx->GetFactory() : GetMainGraphics()->GetFactory()),
		m_RenderTarget(gfx ? gfx->GetDeviceContext() : GetMainGraphics()->GetDeviceContext())
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
		HRESULT hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_DWriteFactory)
		);

		if (FAILED(hr))
		{
			throw std::runtime_error("Can not create the DirectWrite factory!");
		}
	}

	void Renderer::BeginDraw()
	{
		m_RenderTarget->BeginDraw();
	}

	void Renderer::EndDraw()
	{
		m_RenderTarget->EndDraw();
	}

	// Backward compatibility for rendering with only shape style

	void Renderer::ClearScreen(const Color& color)
	{
		m_RenderTarget->Clear(color);
	}

	void Renderer::DrawRectangle(
		const ShapeStyle& rectangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (rectangle.Width && rectangle.Height)
		{
			SetTransform(transform);
			D2D1_RECT_F rect = D2D1::RectF(
				rectangle.Position.X - rectangle.Outline.Width / 2,
				rectangle.Position.Y - rectangle.Outline.Width / 2,
				rectangle.Width + rectangle.Position.X + rectangle.Outline.Width / 2,
				rectangle.Height + rectangle.Position.Y + rectangle.Outline.Width / 2
			);
			if (rectangle.BorderRadius)
			{
				D2D1_ROUNDED_RECT roundedRect = D2D1::RoundedRect(
					rect,
					rectangle.BorderRadius.X * 2.0f,
					rectangle.BorderRadius.Y * 2.0f
				);
				if (rectangle.BackgroundColor)
				{
					m_RenderTarget->FillRoundedRectangle(
						roundedRect,
						rectangle.BackgroundColor
					);
				}
				if (rectangle.Outline.Width && rectangle.Outline.Color)
				{
					m_RenderTarget->DrawRoundedRectangle(
						roundedRect,
						rectangle.Outline.Color,
						rectangle.Outline.Width
					);
				}
			}
			else
			{
				if (rectangle.BackgroundColor)
				{
					m_RenderTarget->FillRectangle(
						rect,
						rectangle.BackgroundColor
					);
				}
				if (rectangle.Outline.Width && rectangle.Outline.Color)
				{
					m_RenderTarget->DrawRectangle(
						rect,
						rectangle.Outline.Color,
						rectangle.Outline.Width
					);
				}
			}
			ResetTranform();
		}
	}

	void Renderer::DrawCircle(
		const ShapeStyle& circle,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (circle.BackgroundColor)
		{
			SetTransform(transform);
			D2D1_ELLIPSE ellipse = D2D1::Ellipse(
				D2D1::Point2F(
					(circle.Width / 2) + circle.Position.X + circle.Outline.Width,
					(circle.Height / 2) + circle.Position.Y + circle.Outline.Width
				),
				min(circle.Width, circle.Height) / 2,
				min(circle.Width, circle.Height) / 2
			);
			m_RenderTarget->FillEllipse(
				ellipse,
				circle.BackgroundColor
			);

			if (circle.Outline.Width && circle.Outline.Color)
			{
				m_RenderTarget->DrawEllipse(
					ellipse,
					circle.Outline.Color,
					circle.Outline.Width
				);
			}
			ResetTranform();
		}
	}

	void Renderer::DrawTriangle(
		const ShapeStyle& triangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (triangle.BackgroundColor && triangle.Width && triangle.Height)
		{
			SetTransform(transform);
			ID2D1PathGeometry* pPathGeometry = nullptr;
			HRESULT hr = m_Factory->CreatePathGeometry(&pPathGeometry);

			if (SUCCEEDED(hr))
			{
				ID2D1GeometrySink* pSink = nullptr;
				hr = pPathGeometry->Open(&pSink);

				if (SUCCEEDED(hr))
				{
					float outlineWidth = triangle.Outline.Width ? triangle.Outline.Width : 0.0f;
					pSink->BeginFigure(
						D2D1::Point2F(
							triangle.Position.X + outlineWidth,
							triangle.Height + triangle.Position.Y + outlineWidth
						),
						D2D1_FIGURE_BEGIN_FILLED
					);
					pSink->AddLine(
						D2D1::Point2F(
							triangle.Position.X + outlineWidth + (triangle.Width) * 0.5f,
							triangle.Position.Y
						)
					);
					pSink->AddLine(
						D2D1::Point2F(
							triangle.Width + triangle.Position.X + outlineWidth,
							triangle.Height + triangle.Position.Y + outlineWidth
						)
					);
					pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
					hr = pSink->Close();

					if (SUCCEEDED(hr))
					{
						m_RenderTarget->FillGeometry(
							pPathGeometry,
							triangle.BackgroundColor
						);

						if (outlineWidth && triangle.Outline.Color)
						{
							D2D1_CAP_STYLE capStyle = triangle.BorderRadius.IsNonZero() ?
								D2D1_CAP_STYLE_ROUND : D2D1_CAP_STYLE_FLAT;
							D2D1_LINE_JOIN lineJoin = triangle.BorderRadius.IsNonZero() ?
								D2D1_LINE_JOIN_ROUND : D2D1_LINE_JOIN_MITER;
							ID2D1StrokeStyle* pStrokeStyle = CreateStrokeStyle(capStyle, lineJoin, D2D1_DASH_STYLE_SOLID);

							if (SUCCEEDED(hr))
							{
								if (outlineWidth)
								{
									m_RenderTarget->DrawGeometry(
										pPathGeometry,
										triangle.Outline.Color,
										outlineWidth,
										pStrokeStyle
									);
								}
							}
							SafeRelease(&pStrokeStyle);
						}
					}
				}
				SafeRelease(&pSink);
			}
			SafeRelease(&pPathGeometry);
			SetTransform(transform);
		}
	}

	void Renderer::DrawTriangle(
		const Vector2& vertexA,
		const Vector2& vertexB,
		const Vector2& vertexC,
		const ShapeStyle& style,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (style.BackgroundColor)
		{
			SetTransform(transform);
			ID2D1PathGeometry* pPathGeometry = nullptr;
			HRESULT hr = m_Factory->CreatePathGeometry(&pPathGeometry);

			if (SUCCEEDED(hr))
			{
				ID2D1GeometrySink* pSink = nullptr;
				hr = pPathGeometry->Open(&pSink);

				if (SUCCEEDED(hr))
				{
					float outlineWidth = style.Outline.Width ? style.Outline.Width : 0.0f;
					pSink->BeginFigure(
						D2D1::Point2F(
							vertexA.X + style.Position.X + outlineWidth,
							vertexA.Y + style.Position.Y + outlineWidth
						),
						D2D1_FIGURE_BEGIN_FILLED
					);
					pSink->AddLine(
						D2D1::Point2F(
							vertexB.X + style.Position.X + outlineWidth,
							vertexB.Y + style.Position.Y + outlineWidth
						)
					);
					pSink->AddLine(
						D2D1::Point2F(
							vertexC.X + style.Position.X + outlineWidth,
							vertexC.Y + style.Position.Y + outlineWidth
						)
					);
					pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
					hr = pSink->Close();

					if (SUCCEEDED(hr))
					{
						m_RenderTarget->FillGeometry(
							pPathGeometry,
							style.BackgroundColor
						);

						if (style.Outline.Width && style.Outline.Color)
						{
							D2D1_CAP_STYLE capStyle = style.BorderRadius.IsNonZero() ?
								D2D1_CAP_STYLE_ROUND : D2D1_CAP_STYLE_FLAT;
							D2D1_LINE_JOIN lineJoin = style.BorderRadius.IsNonZero() ?
								D2D1_LINE_JOIN_ROUND : D2D1_LINE_JOIN_MITER;
							ID2D1StrokeStyle* pStrokeStyle = CreateStrokeStyle(capStyle, lineJoin, D2D1_DASH_STYLE_SOLID);
							

							if (SUCCEEDED(hr))
							{
								if (outlineWidth)
								{
									m_RenderTarget->DrawGeometry(
										pPathGeometry,
										style.Outline.Color,
										outlineWidth,
										pStrokeStyle
									);
								}
							}
							SafeRelease(&pStrokeStyle);
						}
					}
				}
				SafeRelease(&pSink);
			}
			SafeRelease(&pPathGeometry);
			SetTransform(transform);
		}
	}

	void Renderer::DrawLine(
		const ShapeStyle& line,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (line.BackgroundColor)
		{
			SetTransform(transform);

			D2D1_CAP_STYLE capStyle = line.BorderRadius.IsNonZero() ?
				D2D1_CAP_STYLE_ROUND : D2D1_CAP_STYLE_FLAT;
			D2D1_LINE_JOIN lineJoin = line.BorderRadius.IsNonZero() ?
				D2D1_LINE_JOIN_ROUND : D2D1_LINE_JOIN_MITER;
			ID2D1StrokeStyle* pStrokeStyle = CreateStrokeStyle(capStyle, lineJoin, D2D1_DASH_STYLE_SOLID);
			m_RenderTarget->DrawLine(
				D2D1::Point2F(line.Width, line.Height),
				D2D1::Point2F(line.Position.X, line.Position.Y),
				line.BackgroundColor,
				line.Outline.Width,
				pStrokeStyle
			);
			
			ResetTranform();
		}
	}

	// Rendering with a specific shape style

	void Renderer::ClearScreen(
		ID2D1Brush* brush,
		bool immediate
	)
	{
		D2D1_SIZE_F windowSize = m_RenderTarget->GetSize();
		m_RenderTarget->Clear();
		m_RenderTarget->FillRectangle(D2D1::RectF(
			-GetMainCamera()->Position.X,
			-GetMainCamera()->Position.Y,
			-GetMainCamera()->Position.X + windowSize.width,
			-GetMainCamera()->Position.Y + windowSize.height
		), brush);
		
		// This line ensures that the screen gets cleared without any delays.
		// Using immediate drawing can cause performance issues.
		// Note: You should only set the immediate parameter to true if you experience screen flickering.
		if (immediate)
		{
			m_RenderTarget->Flush();
		}
	}

	void Renderer::DrawRectangle(
		const RectangleStyle& rectangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		ShapeStyle style = rectangle;
		DrawRectangle(style, transform);
	}

	void Renderer::DrawCircle(
		const CircleStyle& circle,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (circle.BackgroundColor)
		{
			SetTransform(transform);
			D2D1_ELLIPSE ellipse = {
				D2D1::Point2F(
					(circle.Radius.X) + circle.Position.X + circle.Outline.Width,
					(circle.Radius.Y) + circle.Position.Y + circle.Outline.Width
				),
				circle.Radius.X,
				circle.Radius.Y
			};
			m_RenderTarget->FillEllipse(
				ellipse,
				circle.BackgroundColor
			);

			if (circle.Outline.Width && circle.Outline.Color)
			{
				m_RenderTarget->DrawEllipse(
					ellipse,
					circle.Outline.Color,
					circle.Outline.Width
				);
			}
			ResetTranform();
		}
	}

	void Renderer::DrawTriangle(
		const TriangleStyle& triangle,
		const D2D1::Matrix3x2F& transform
	)
	{
		DrawTriangle(
			triangle.VertexA,
			triangle.VertexB,
			triangle.VertexC,
			triangle,
			transform
		);
	}

	void Renderer::DrawLine(
		const LineStyle& line,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (line.BackgroundColor)
		{
			SetTransform(transform);

			D2D1_CAP_STYLE capStyle = line.BorderRadius.IsNonZero() ?
				D2D1_CAP_STYLE_ROUND : D2D1_CAP_STYLE_FLAT;
			D2D1_LINE_JOIN lineJoin = line.BorderRadius.IsNonZero() ?
				D2D1_LINE_JOIN_ROUND : D2D1_LINE_JOIN_MITER;
			ID2D1StrokeStyle* pStrokeStyle = CreateStrokeStyle(capStyle, lineJoin, D2D1_DASH_STYLE_SOLID);
			m_RenderTarget->DrawLine(
				D2D1::Point2F(line.Start.X, line.Start.Y),
				D2D1::Point2F(line.End.X, line.End.Y),
				line.BackgroundColor,
				line.Outline.Width,
				pStrokeStyle
			);

			ResetTranform();
		}
	}

	void Renderer::RenderText(
		const String& text,
		const TextStyle& style,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (style.Color)
		{
			SetTransform(transform);
			IDWriteTextFormat* pTextFormat = nullptr;
			HRESULT hr = m_DWriteFactory->CreateTextFormat(
				style.Font.FontFamily.c_str() ? style.Font.FontFamily.c_str() : L"Arial",
				nullptr,
				style.Font.FontWeight ? style.Font.FontWeight : DWRITE_FONT_WEIGHT_LIGHT,
				style.Font.FontStyle ? style.Font.FontStyle : DWRITE_FONT_STYLE_NORMAL,
				style.Font.FontStretch ? style.Font.FontStretch : DWRITE_FONT_STRETCH_NORMAL,
				style.Font.FontSize ? style.Font.FontSize : 16.0f, L"",
				&pTextFormat
			);

			if (SUCCEEDED(hr))
			{
				IDWriteTextLayout* pTextLayout = nullptr;
				hr = m_DWriteFactory->CreateTextLayout(
					text.c_str(), Cast<UInt>(text.size()), pTextFormat,
					style.Width ? style.Width : FLT_MAX, FLT_MAX,
					&pTextLayout
				);

				if (SUCCEEDED(hr))
				{
					if (style.BackgroundColor)
					{
						DWRITE_TEXT_METRICS textMetrics;
						pTextLayout->GetMetrics(&textMetrics);

						D2D1_RECT_F rect = {
							style.Position.X,
							style.Position.Y,
							style.Width ? style.Width + style.Position.X : textMetrics.widthIncludingTrailingWhitespace + style.Position.X,
							textMetrics.height + style.Position.Y
						};
						D2D1_ROUNDED_RECT roundedRect = { rect, style.BorderRadius, style.BorderRadius };

						m_RenderTarget->FillRoundedRectangle(
							roundedRect,
							style.BackgroundColor
						);
					}

					m_RenderTarget->DrawTextLayout(
						D2D1::Point2F(style.Position.X, style.Position.Y),
						pTextLayout, style.Color
					);
				}
				SafeRelease(&pTextLayout);
			}
			SafeRelease(&pTextFormat);
			ResetTranform();
		}
	}

	void Renderer::RenderTexture(
		Texture& texture,
		const D2D1::Matrix3x2F& transform
	)
	{
		if (texture.GetBrush())
		{
			SetTransform(transform);
			if (texture.GetStyle().BorderRadius)
			{
				DrawRectangle(texture.GetBrushStyle());
			}
			else
			{
				D2D1_RECT_F rect = {
					texture.GetStyle().Position.X, texture.GetStyle().Position.Y,
					texture.GetStyle().Width + texture.GetStyle().Position.X,
					texture.GetStyle().Height + texture.GetStyle().Position.Y
				};
				m_RenderTarget->DrawBitmap(texture.GetBitmap(), rect);
			}
			ResetTranform();
		}
	}

	ID2D1StrokeStyle* Renderer::CreateStrokeStyle(
		D2D1_CAP_STYLE capStyle, 
		D2D1_LINE_JOIN lineJoin, 
		D2D1_DASH_STYLE dashStyle
	)
	{
		ID2D1StrokeStyle* pStrokeStyle = nullptr;
		m_Factory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties(
				capStyle,
				capStyle,
				capStyle,
				lineJoin,
				0.0f,
				dashStyle
			),
			nullptr,
			0,
			&pStrokeStyle
		);

		return pStrokeStyle;
	}

	void Renderer::SetTransform(const D2D1::Matrix3x2F& transform)
	{
		if (!transform.IsIdentity())
		{
			if (GetMainCamera())
			{
				m_RenderTarget->SetTransform(transform * GetMainCamera()->GetViewMatrix());
			}
			else
			{
				m_RenderTarget->SetTransform(transform);
			}
		}
	}

	void Renderer::ResetTranform()
	{
		if (GetMainCamera())
		{
			m_RenderTarget->SetTransform(GetMainCamera()->GetViewMatrix());
		}
		else
		{
			m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		}
	}

}