#pragma once

#include <ostream>

class Vector2D
{
public:
    explicit Vector2D() = default;
    explicit Vector2D(const float x, const float y);

    friend Vector2D operator+ (const Vector2D& lhs, const Vector2D& rhs);
    friend Vector2D operator- (const Vector2D& lhs, const Vector2D& rhs);
    friend Vector2D operator* (const Vector2D& lhs, const Vector2D& rhs);
    friend Vector2D operator/ (const Vector2D& lhs, const Vector2D& rhs);

    Vector2D operator+=(const Vector2D& other);
    Vector2D operator-=(const Vector2D& other);
    Vector2D operator*=(const Vector2D& other);
    Vector2D operator/=(const Vector2D& other);

    friend std::ostream& operator<< (std::ostream& stream, const Vector2D& vector);

public:
    float X = 0;
    float Y = 0;
};

