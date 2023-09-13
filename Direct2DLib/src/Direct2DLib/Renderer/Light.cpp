#include "Direct2DLibpch.h"
#include "Light.h"

namespace D2DLib
{

    Light::Light(
        const CircleStyle& style,
        const ShapeStyle& shadowStyle,
        bool noShadowLimitation
    ) :
        m_Style(style),
        ShadowStyle(shadowStyle),
        NoShadowLimitation(noShadowLimitation)
    {
    }

    void Light::Update(const Vector2& position)
    {
        if (m_Style.Position != position)
        {
            m_Style.Position = position;
        }
    }

    const Vector<Boundary> Light::GetBoundaryByType(const Vector<RectangleStyle>& shapes)
    {
        Vector<Boundary> boundaries;
        for (const auto& shape : shapes)
        {
            Vector<Boundary> bounds;
            bounds.reserve(4);

            const Vector2 pos = shape.Position;
            bounds.emplace_back(Boundary(pos, pos + Vector2(0.0f, shape.Height))); // left side
            bounds.emplace_back(Boundary(pos + Vector2(shape.Width, 0.0f),
                pos + Vector2(shape.Width, shape.Height))); // right side
            bounds.emplace_back(Boundary(pos, pos + Vector2(shape.Width, 0.0f))); // top
            bounds.emplace_back(Boundary(pos + Vector2(0.0f, shape.Height),
                pos + Vector2(shape.Width, shape.Height))); // bottom

            for (auto& bound : bounds)
            {
                boundaries.push_back(bound);
            }
        }

        return boundaries;
    }

    const Vector<Boundary> Light::GetBoundaryByType(const Vector<TriangleStyle>& shapes)
    {
        Vector<Boundary> boundaries;
        for (const auto& shape : shapes)
        {
            Vector<Boundary> bounds;
            bounds.reserve(3);

            bounds.emplace_back(Boundary(shape.VertexA, shape.VertexB));
            bounds.emplace_back(Boundary(shape.VertexB, shape.VertexC));
            bounds.emplace_back(Boundary(shape.VertexC, shape.VertexA));
            
            for (auto& bound : bounds)
            {
                boundaries.push_back(bound);
            }
        }
        return boundaries;
    }

}