#pragma once

#include "Shadow.h"

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

            for (const Boundary& boundary : GetBoundaryByType(shapes))
            {
                Vector2 a = boundary.Start;
                Vector2 b = boundary.End;
                Shadow shadow(a, b, m_Style, ShadowStyle);
                if (NoShadowLimitation)
                {
                    shadow.Draw();
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
        CircleStyle m_Style;
    };

}