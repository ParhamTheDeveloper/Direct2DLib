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
			const ShapeStyle& style
		) :
			m_VertexA(vertexA),
			m_VertexB(vertexB),
			m_Style(style),
			m_LightStyle(lightStyle)
		{
		}

		void Draw()
		{
			const Vector2 lightPosition = m_LightStyle.Position + m_LightStyle.Radius;
			const float lightRadius = (m_LightStyle.Radius.X + m_LightStyle.Radius.Y) / 2.0f;
			const Vector2 sa = (m_VertexA - lightPosition) * lightRadius;
			const Vector2 ea = m_VertexA + sa;

			const Vector2 sb = (m_VertexB - lightPosition) * lightRadius;
			const Vector2 eb = m_VertexB + sb;
			
			DrawTriangle(m_VertexA, ea, eb, m_Style);
			DrawTriangle(m_VertexA, m_VertexB, eb, m_Style);
		}
	private:
		Vector2 m_VertexA, m_VertexB;
		ShapeStyle m_Style;
		CircleStyle m_LightStyle;
	};

}