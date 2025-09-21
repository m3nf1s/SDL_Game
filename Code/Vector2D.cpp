#include "Vector2D.h"

#include <format>

Vector2D::Vector2D(const float x, const float y)
	: X(x), Y(y)
{
}

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.X + rhs.X, lhs.Y + rhs.Y);
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.X - rhs.X, lhs.Y - rhs.Y);
}

Vector2D operator*(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.X * rhs.X, lhs.Y * rhs.Y);
}

Vector2D operator/(const Vector2D& lhs, const Vector2D& rhs)
{
	if (rhs.X == 0 || rhs.Y == 0)
	{
		throw std::runtime_error("Division by zero");
	}

	return Vector2D(lhs.X / rhs.X, lhs.Y / rhs.Y);
}

Vector2D Vector2D::operator+=(const Vector2D& other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

Vector2D Vector2D::operator-=(const Vector2D& other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}

Vector2D Vector2D::operator*=(const Vector2D& other)
{
	X *= other.X;
	Y *= other.Y;
	return *this;
}

Vector2D Vector2D::operator/=(const Vector2D& other)
{
	if (other.X == 0 || other.Y == 0)
	{
		throw std::runtime_error("Division by zero");
	}

	X /= other.X;
	Y /= other.Y;
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vector)
{
	return stream << std::format("({},{})", vector.X, vector.Y);
}
