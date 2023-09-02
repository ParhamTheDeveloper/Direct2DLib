#include "pch.h"
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
        Vector2 position = m_Style.Position + m_Style.Radius;
        m_Rays.reserve(360);
        for (float i = 0; i < 360; i += 1.0f)
        {
            m_Rays.emplace_back(position, DegreesToRadians(i));
        }
    }

    void Light::Update(const Vector2& position)
    {
        m_Style.Position = position;
        for (Ray& ray : m_Rays)
        {
            ray.Position = position + m_Style.Radius;
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
            bounds.emplace_back(Boundary(pos, pos + Vector2(0.0f, shape.Height)));
            bounds.emplace_back(Boundary(pos + Vector2(shape.Width, 0.0f),
                pos + Vector2(shape.Width, shape.Height)));
            bounds.emplace_back(Boundary(pos, pos + Vector2(shape.Width, 0.0f)));
            bounds.emplace_back(Boundary(pos + Vector2(shape.Height, 0.0f),
                pos + Vector2(shape.Width, shape.Height)));

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