#include "Direct2DLibpch.h"
#include "Texture.h"

namespace D2DLib
{
	
	Texture::Texture(const String& filePath, const RectangleStyle& style, Graphics* gfx) :
		m_FilePath(filePath), 
		m_RenderTarget(gfx ? gfx->GetDeviceContext() : GetMainGraphics()->GetDeviceContext()),
		m_Style(style)
	{
		HRESULT hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_WICImagingFactory)
		);

		if (SUCCEEDED(hr))
		{
			IWICBitmapDecoder* pBitmapDecoder = nullptr;
			hr = m_WICImagingFactory->CreateDecoderFromFilename(
				m_FilePath.c_str(),
				nullptr,
				GENERIC_READ,
				WICDecodeMetadataCacheOnLoad,
				&pBitmapDecoder
			);

			if (SUCCEEDED(hr))
			{
				IWICBitmapFrameDecode* pBitmapFrameDecode = nullptr;
				hr = pBitmapDecoder->GetFrame(0, &pBitmapFrameDecode);
			
				if (SUCCEEDED(hr))
				{
					IWICFormatConverter* pFormatConverter = nullptr;
					hr = m_WICImagingFactory->CreateFormatConverter(&pFormatConverter);

					if (SUCCEEDED(hr))
					{
						hr = pFormatConverter->Initialize(
							pBitmapFrameDecode,
							GUID_WICPixelFormat32bppPRGBA,
							WICBitmapDitherTypeNone,
							nullptr,
							0.0f,
							WICBitmapPaletteTypeCustom
						);
					
						if (SUCCEEDED(hr))
						{
							hr = m_RenderTarget->CreateBitmapFromWicBitmap(pFormatConverter, &m_Bitmap);
							
							UInt width = 0, height = 0;
							pFormatConverter->GetSize(&width, &height);

							Vector<unsigned char> buffer(width * height * 4);
							pFormatConverter->CopyPixels(0, width * 4, Cast<UInt>(buffer.size()), buffer.data());

							m_HBitmap = CreateBitmap(width, height, 1, 32, buffer.data());

							if (SUCCEEDED(hr))
							{
								UInt bitmapWidth, bitmapHeight;
								pFormatConverter->GetSize(&bitmapWidth, &bitmapHeight);
								m_LoadedBitmapSize = { Cast<float>(bitmapWidth), Cast<float>(bitmapHeight) };
							}
						}
					}
					SafeRelease(&pFormatConverter);
				}
				SafeRelease(&pBitmapFrameDecode);
			}
			SafeRelease(&pBitmapDecoder);
		}
	}

	Texture::~Texture()
	{
		SafeRelease(&m_WICImagingFactory);
		SafeRelease(&m_Bitmap);
		DeleteObject(m_HBitmap);
	}

	ID2D1BitmapBrush* Texture::GetBrush()
	{
		ID2D1BitmapBrush* pBitmapBrush = nullptr;
		HRESULT hr = m_RenderTarget->CreateBitmapBrush(m_Bitmap, &pBitmapBrush);

		if (SUCCEEDED(hr))
		{
			if (m_Style.Width && m_Style.Height)
			{
				pBitmapBrush->SetTransform(D2D1::Matrix3x2F::Translation(
					D2D1::SizeF(
						m_Style.Width / 2,
						m_Style.Height / 2
					)
				));
			}
		}

		return pBitmapBrush;
	}

	const RectangleStyle Texture::GetBrushStyle()
	{
		RectangleStyle bitmapStyle = m_Style;
		bitmapStyle.BackgroundColor = GetBrush();
		return bitmapStyle;
	}

	void Texture::SetStyle(const RectangleStyle& style)
	{
		m_Style = style;
	}

}