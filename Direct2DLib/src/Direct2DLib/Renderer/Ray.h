#pragma once

#include "Boundary.h"
#include "RendererGlobal.h"

namespace D2DLib
{

    class D2DLIB_API Ray
    {
    public:
        Ray(const Vector2& position, float angle);

        void LookAt(const Vector2& direction);
        const Vector2 Cast(const Boundary& wall);
    public:
        Vector2 Position, Direction;
    };

}