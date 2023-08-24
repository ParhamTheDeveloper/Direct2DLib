#pragma once

#include "Ray.h"
#include "Shadow.h"
#include "Direct2DLib/Transitions/InterpolatorTransition.h"

namespace D2DLib
{

    class Light
    {
    public:
        Light(
            const Vector2& position,
            const ShapeStyle& shadowStyle,
            float radius,
            bool noShadowLimitation = false
        );

        void Update(const Vector2& position);
        void Look(
            const Vector<Boundary>& boundaries,
            bool drawCastedLines = false,
            const LineStyle& castedLinesStyle = LineStyle()
        );
        void Draw(
            const LineStyle& raysStyle,
            const ShapeStyle& lightCenterStyle,
            const Vector2& rayNumerator = Vector2(10.0f)
        );
    public:
        Vector2 Position;
        ShapeStyle ShadowStyle;
        float Radius;
        bool NoShadowLimitation;
    private:
        Vector<Ray> m_Rays;
    };

}