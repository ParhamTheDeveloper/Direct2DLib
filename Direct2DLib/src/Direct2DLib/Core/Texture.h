#pragma once

#include "Graphics.h"
#include "Styles.h"

namespace D2DLib
{
	
	class D2DLIB_API Texture
	{
	public:
		Texture(const String& filePath, const RectangleStyle& style, Graphics* gfx = nullptr);
		~Texture();

		ID2D1Bitmap* GetBitmap() const { return m_Bitmap; }
		const RectangleStyle& GetStyle() const { return m_Style; }
		const RectangleStyle& GetLoadedTextureStyle() const { return m_LoadedBitmapSize; }
		const String& GetFilePath() const { return m_FilePath; }
		HBITMAP GetBitmapHandle() const { return m_HBitmap; };
		ID2D1BitmapBrush* GetBrush();
		const RectangleStyle GetBrushStyle();
		void SetStyle(const RectangleStyle& style);
	private:
		ID2D1DeviceContext6* m_RenderTarget = nullptr;
		IWICImagingFactory* m_WICImagingFactory = nullptr;
		ID2D1Bitmap* m_Bitmap = nullptr;
		HBITMAP m_HBitmap = nullptr;
		String m_FilePath;
		RectangleStyle m_Style;
		RectangleStyle m_LoadedBitmapSize;
	};

}