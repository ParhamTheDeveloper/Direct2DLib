#pragma once

#include "Graphics.h"
#include "Styles.h"

namespace D2DLib
{
	
	class Texture
	{
	public:
		Texture(const String& filePath, const RectangleStyle& style, Graphics* gfx = nullptr);
		~Texture();

		ID2D1Bitmap* GetBitmap() const { return m_Bitmap; }
		const RectangleStyle& GetStyle() const { return m_Style; }
		const RectangleStyle& GetLoadedTextureStyle() const { return m_LoadedBitmapSize; }
		const String& GetFilePath() const { return m_FilePath; }
		ID2D1BitmapBrush* GetBrush();
		const RectangleStyle GetBrushStyle();
		void SetStyle(const RectangleStyle& style);
	private:
		IWICImagingFactory* m_WICImagingFactory = nullptr;
		ID2D1Bitmap* m_Bitmap = nullptr;
		String m_FilePath;
		ID2D1DeviceContext6* m_RenderTarget = nullptr;
		RectangleStyle m_Style;
		RectangleStyle m_LoadedBitmapSize;
	};

}