#pragma once

#include "Boundary.h"
#include "RendererGlobal.h"

namespace D2DLib
{

    class Ray
    {
    public:
        Ray(const Vector2& position, float angle);

        void LookAt(const Vector2& direction);
        const Vector2 Cast(const Boundary& wall);
        void Draw(const LineStyle& style, const Vector2& sizeNumerator = Vector2(10.0f, 10.0f));
    public:
        Vector2 Position, Direction;
    };

}