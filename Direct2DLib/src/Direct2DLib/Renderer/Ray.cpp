#include "pch.h"
#include "Ray.h"

namespace D2DLib
{

    Ray::Ray(const Vector2& position, float angle)
        : Position(position), Direction(Vector2::FromAngle(angle))
    {
    }

    void Ray::LookAt(const Vector2& direction)
    {
        Direction = direction - Position;
        Direction.Normalize();
    }

    const Vector2 Ray::Cast(const Boundary& wall)
    {
        const float x1 = wall.Start.X;
        const float y1 = wall.Start.Y;
        const float x2 = wall.End.X;
        const float y2 = wall.End.Y;

        const float x3 = Position.X;
        const float y3 = Position.Y;
        const float x4 = Position.X + Direction.X;
        const float y4 = Position.Y + Direction.Y;

        const float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (!denominator)
        {
            return Vector2();
        }

        const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
        const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

        if (t > 0 && t < 1 && u > 0)
        {
            Vector2 point;
            point.X = x1 + t * (x2 - x1);
            point.Y = y1 + t * (y2 - y1);
            return point;
        }
        else
        {
            return Vector2();
        }
    }

}