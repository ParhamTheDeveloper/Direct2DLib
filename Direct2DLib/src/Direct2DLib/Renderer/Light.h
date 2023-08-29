#pragma once

#include "Ray.h"
#include "Shadow.h"
#include "Direct2DLib/Transitions/InterpolatorTransition.h"

namespace D2DLib
{

    class D2DLIB_API Light
    {
    public:
        Light(
            const CircleStyle& light,
            const ShapeStyle& shadowStyle,
            bool noShadowLimitation = false
        );

        void Update(const Vector2& position);
        
        template<typename ShapeType>
        void Look(const Vector<ShapeType>& shapes)
        {
            const Vector2 position = m_Style.Position + m_Style.Radius;
            const float radius = (m_Style.Radius.X + m_Style.Radius.Y) / 2.0f;

            for (Ray& ray : m_Rays)
            {
                Vector2 closest;
                float record = D2D1::FloatMax();
                for (const Boundary& boundary : GetBoundaryByType(shapes))
                {
                    Vector2 point = ray.Cast(boundary);
                    if (point)
                    {
                        const float distance = Vector2::Distance(position, point);
                        if (distance < record)
                        {
                            record = distance;
                            closest = point;
                            Vector2 a = boundary.Start;
                            Vector2 b = boundary.End;
                            Shadow shadow(a, b, m_Style, ShadowStyle);
                            if (NoShadowLimitation || distance < radius * 2.0f)
                            {
                                shadow.Draw();
                            }
                        }
                    }
                }
            }
        }
    private:
        const Vector<Boundary> GetBoundaryByType(const Vector<RectangleStyle>& shapes);
        const Vector<Boundary> GetBoundaryByType(const Vector<TriangleStyle>& shapes);
    public:
        ShapeStyle ShadowStyle;
        bool NoShadowLimitation;
    private:
        Vector<Ray> m_Rays;
        CircleStyle m_Style;
    };

}