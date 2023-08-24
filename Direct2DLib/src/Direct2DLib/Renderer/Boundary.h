#pragma once

#include "Direct2DLib/Math/Vector2.h"
#include "ResourceManagerGlobal.h"
#include "RendererGlobal.h"

namespace D2DLib
{

	class Boundary
	{
	public:
		Boundary()
			: Start(), End()
		{
		}

		Boundary(const Vector2& start, const Vector2& end)
			: Start(start), End(end)
		{
		}

		void Draw()
		{
			auto brush = CreateBrush(Color(255.0f, 255.0f, 255.0f));
			LineStyle style;
			style.Outline = Outline(1.0f);
			style.Start = Start;
			style.End = End;
			style.BackgroundColor = brush;
			DrawLine(style);
			SafeRelease(&brush);
		}
	public:
		Vector2 Start, End;
	};

}