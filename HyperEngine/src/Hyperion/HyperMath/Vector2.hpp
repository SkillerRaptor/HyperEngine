#pragma once

#include <cmath>
#include <iostream>
#include <type_traits>

namespace Hyperion 
{
	template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	class Vector2
	{
	public:
		T x, y;

	public:
		Vector2()
			: x(0), y(0) {}
		Vector2(const Vector2<T>& xy)
			: x(xy.x), y(xy.y) {}
		explicit Vector2(T xy)
			: x(xy), y(xy) {}
		Vector2(T x, T y)
			: x(x), y(y) {}

		float Magnitude() const
		{
			return sqrt(x * x + y * y);
		}

		/* Negate */
		Vector2<T> operator-() const
		{
			Vector2 vec;
			vec.x = -x;
			vec.y = -y;
			return vec;
		}

		/* Adding */
		Vector2<T> operator+(T value) const
		{
			Vector2<T> vec;
			vec.x = x + value;
			vec.y = y + value;
			return vec;
		}

		Vector2<T> operator+(const Vector2<T>& vector) const
		{
			Vector2<T> vec;
			vec.x = x + vector.x;
			vec.y = y + vector.y;
			return vec;
		}

		Vector2<T>& operator+=(T value)
		{
			x += value;
			y += value;
			return *this;
		}

		Vector2<T>& operator+=(const Vector2<T>& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		/* Subtracting */
		Vector2<T> operator-(T value) const
		{
			Vector2<T> vec;
			vec.x = x - value;
			vec.y = y - value;
			return vec;
		}

		Vector2<T> operator-(const Vector2<T>& vector) const
		{
			Vector2<T> vec;
			vec.x = x - vector.x;
			vec.y = y - vector.y;
			return vec;
		}

		Vector2<T>& operator-=(T value)
		{
			x -= value;
			y -= value;
			return *this;
		}

		Vector2<T>& operator-=(const Vector2<T>& vector)
		{
			x -= vector.x;
			y -= vector.y;
			return *this;
		}

		/* Multiplying */
		Vector2<T> operator*(T value) const
		{
			Vector2<T> vec;
			vec.x = x * value;
			vec.y = y * value;
			return vec;
		}

		Vector2<T> operator*(const Vector2<T>& vector) const
		{
			Vector2<T> vec;
			vec.x = x * vector.x;
			vec.y = y * vector.y;
			return vec;
		}

		Vector2<T>& operator*=(T value)
		{
			x *= value;
			y *= value;
			return *this;
		}

		Vector2<T>& operator*=(const Vector2<T>& vector)
		{
			x *= vector.x;
			y *= vector.y;
			return *this;
		}

		/* Dividing */
		Vector2<T> operator/(T value) const
		{
			Vector2<T> vec;
			vec.x = x / value;
			vec.y = y / value;
			return vec;
		}

		Vector2<T> operator/(const Vector2<T>& vector) const
		{
			Vector2<T> vec;
			vec.x = x / vector.x;
			vec.y = y / vector.y;
			return vec;
		}

		Vector2<T>& operator/=(T value)
		{
			x /= value;
			y /= value;
			return *this;
		}

		Vector2<T>& operator/=(const Vector2<T>& vector)
		{
			x /= vector.x;
			y /= vector.y;
			return *this;
		}

		/* Comparsion */
		bool operator==(const Vector2<T>& vector)
		{
			return (x == vector.x && y == vector.y);
		}

		bool operator!=(const Vector2<T>& vector)
		{
			return (x != vector.x || y != vector.y);
		}

		/* Conversion */
		operator float* ()
		{
			return reinterpret_cast<float*>(this);
		}
	};
}
