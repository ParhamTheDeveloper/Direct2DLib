#include "pch.h"
#include "Light.h"

namespace D2DLib
{

    Light::Light(
        const Vector2& position,
        const ShapeStyle& shadowStyle,
        float radius,
        bool noShadowLimitation
    ) :
        Position(position),
        ShadowStyle(shadowStyle),
        Radius(radius),
        NoShadowLimitation(noShadowLimitation)
    {
        for (float i = 0; i < 360; i += 1.0f)
        {
            Ray ray(Position, DegreesToRadians(i));
            m_Rays.push_back(ray);
        }
    }

    void Light::Update(const Vector2& position)
    {
        Position = position;
        for (Ray& ray : m_Rays)
        {
            ray.Position = position;
        }
    }

    void Light::Look(
        const Vector<Boundary>& boundaries,
        bool drawCastedLines,
        const LineStyle& castedLinesStyle
    )
    {
        for (Ray& ray : m_Rays)
        {
            Vector2 closest;
            float record = D2D1::FloatMax();
            for (const Boundary boundary : boundaries)
            {
                Vector2 point = ray.Cast(boundary);
                if (point)
                {
                    const float distance = Vector2::Distance(Position, point);
                    if (distance < record)
                    {
                        record = distance;
                        closest = point;
                        Vector2 a = boundary.Start;
                        Vector2 b = boundary.End;
                        Shadow shadow(a, b, Position, Radius, ShadowStyle);
                        if (NoShadowLimitation)
                        {
                            shadow.Draw();
                        }
                        else if (distance < Radius * 2.0f)
                        {
                            shadow.Draw();
                        }
                    }
                }
            }
            if (closest && drawCastedLines)
            {
                LineStyle lineStyle = castedLinesStyle;
                lineStyle.Start = Position;
                lineStyle.End = closest;
                DrawLine(lineStyle);
            }
        }
    }

    void Light::Draw(
        const LineStyle& raysStyle,
        const ShapeStyle& lightCenterStyle,
        const Vector2& rayNumerator
    )
    {
        ShapeStyle lightCircleStyle = lightCenterStyle;
        lightCircleStyle.Position = Position;
        DrawCircle(lightCircleStyle);
        for (Ray& ray : m_Rays)
        {
            ray.Draw(raysStyle, rayNumerator);
        }
    }

}