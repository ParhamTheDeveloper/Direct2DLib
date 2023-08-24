#pragma once

#include "RendererGlobal.h"

namespace D2DLib
{

	class Shadow
	{
	public:
		Shadow(
			const Vector2& vertexA,
			const Vector2& vertexB,
			const Vector2& lightPosition,
			float lightRadius,
			const ShapeStyle& style
		) :
			VertexA(vertexA),
			VertexB(vertexB),
			LightPosition(lightPosition),
			Style(style),
			LightRadius(lightRadius)
		{
		}

		void Draw()
		{
			Vector2 sa = (VertexA - LightPosition) * 200.0f;
			Vector2 ea = VertexA + sa;

			Vector2 sb = (VertexB - LightPosition) * 200.0f;
			Vector2 eb = VertexB + sb;
			DrawTriangle(
				VertexA,
				ea,
				eb,
				Style
			);
			DrawTriangle(
				VertexA,
				VertexB,
				eb,
				Style
			);
		}
	public:
		float LightRadius;
	private:
		Vector2 VertexA, VertexB, LightPosition;
		ShapeStyle Style;
	};

}