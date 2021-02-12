#pragma once

#include <cmath>
#include <iostream>
#include <type_traits>

#include "HyperMath/Vector2.hpp"

namespace HyperMath 
{
	template <typename T>
	class Vector3
	{
	public:
		T x, y, z;

		static_assert(std::is_same<T, int>() || std::is_same<T, long>() || std::is_same<T, long long>() || std::is_same<T, float>()
			|| std::is_same<T, double>() || std::is_same<T, long double>(), "Invalid scalar type for Vector3");

	public:
		Vector3()
			: x(0), y(0), z(0) {}
		Vector3(const Vector3<T>& xyz)
			: x(xyz.x), y(xyz.y), z(xyz.z) {}
		explicit Vector3(T xyz)
			: x(xyz), y(xyz), z(xyz) {}
		Vector3(T x, T y, T z)
			: x(x), y(y), z(z) {}
		Vector3(const Vector2<T>& xy, T z)
			: x(xy.x), y(xy.y), z(z) {}
		Vector3(T x, const Vector2<T>& yz)
			: x(x), y(yz.y), z(yz.z) {}

		float Magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		/* Negate */
		Vector3<T> operator-() const
		{
			Vector3<T> vec;
			vec.x = -x;
			vec.y = -y;
			vec.z = -z;
			return vec;
		}

		/* Adding */
		Vector3<T> operator+(T value) const
		{
			Vector3<T> vec;
			vec.x = x + value;
			vec.y = y + value;
			vec.z = z + value;
			return vec;
		}

		Vector3<T> operator+(const Vector3<T>& vector) const
		{
			Vector3<T> vec;
			vec.x = x + vector.x;
			vec.y = y + vector.y;
			vec.z = z + vector.z;
			return vec;
		}

		Vector3<T>& operator+=(T value)
		{
			x += value;
			y += value;
			z += value;
			return *this;
		}

		Vector3<T>& operator+=(const Vector3<T>& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		/* Subtracting */
		Vector3<T> operator-(T value) const
		{
			Vector3<T> vec;
			vec.x = x - value;
			vec.y = y - value;
			vec.z = z - value;
			return vec;
		}

		Vector3<T> operator-(const Vector3<T>& vector) const
		{
			Vector3<T> vec;
			vec.x = x - vector.x;
			vec.y = y - vector.y;
			vec.z = z - vector.z;
			return vec;
		}

		Vector3<T>& operator-=(T value)
		{
			x -= value;
			y -= value;
			z -= value;
			return *this;
		}

		Vector3<T>& operator-=(const Vector3<T>& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}

		/* Multiplying */
		Vector3<T> operator*(T value) const
		{
			Vector3<T> vec;
			vec.x = x * value;
			vec.y = y * value;
			vec.z = z * value;
			return vec;
		}

		Vector3<T> operator*(const Vector3<T>& vector) const
		{
			Vector3<T> vec;
			vec.x = x * vector.x;
			vec.y = y * vector.y;
			vec.z = z * vector.z;
			return vec;
		}

		Vector3<T>& operator*=(T value)
		{
			x *= value;
			y *= value;
			z *= value;
			return *this;
		}

		Vector3<T>& operator*=(const Vector3<T>& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
			return *this;
		}

		/* Dividing */
		Vector3<T> operator/(T value) const
		{
			Vector3<T> vec;
			vec.x = x / value;
			vec.y = y / value;
			vec.z = z / value;
			return vec;
		}

		Vector3<T> operator/(const Vector3<T>& vector) const
		{
			Vector3<T> vec;
			vec.x = x / vector.x;
			vec.y = y / vector.y;
			vec.z = z / vector.z;
			return vec;
		}

		Vector3<T>& operator/=(T value)
		{
			x /= value;
			y /= value;
			z /= value;
			return *this;
		}

		Vector3<T>& operator/=(const Vector3<T>& vector)
		{
			x /= vector.x;
			y /= vector.y;
			z /= vector.z;
			return *this;
		}

		/* Comparsion */
		bool operator==(const Vector3<T>& vector)
		{
			return (x == vector.x && y == vector.y && z == vector.z);
		}

		bool operator!=(const Vector3<T>& vector) 
		{
			return (x != vector.x || y != vector.y || z != vector.z);
		}

		/* Conversion */
		operator float*()
		{
			return reinterpret_cast<float*>(this);
		}
	};
}
