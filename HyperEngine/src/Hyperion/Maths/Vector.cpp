#include "Vector.hpp"

namespace Hyperion
{
	namespace Vector
	{
		Vec2 Normalize(Vec2& vector)
		{
			Vec2 vec;
			vec.x = vector.x / vector.Magnitude();
			vec.y = vector.y / vector.Magnitude();
			return vec;
		}

		Vec3 Normalize(Vec3& vector)
		{
			Vec3 vec;
			vec.x = vector.x / vector.Magnitude();
			vec.y = vector.y / vector.Magnitude();
			vec.z = vector.z / vector.Magnitude();
			return vec;
		}

		Vec4 Normalize(Vec4& vector)
		{
			Vec4 vec;
			vec.x = vector.x / vector.Magnitude();
			vec.y = vector.y / vector.Magnitude();
			vec.z = vector.z / vector.Magnitude();
			vec.w = vector.w / vector.Magnitude();
			return vec;
		}

		float Dot(Vec2& vectorOne, Vec2& vectorTwo)
		{
			Vec2 vec = Normalize(vectorOne) * Normalize(vectorTwo);
			return vec.x + vec.y;
		}

		float Dot(Vec3& vectorOne, Vec3& vectorTwo)
		{
			Vec3 vec = Normalize(vectorOne) * Normalize(vectorTwo);
			return vec.x + vec.y + vec.z;
		}

		float Dot(Vec4& vectorOne, Vec4& vectorTwo)
		{
			Vec4 vec = Normalize(vectorOne) * Normalize(vectorTwo);
			return vec.x + vec.y + vec.z + vec.w;
		}

		Vec3 Cross(Vec3& vectorOne, Vec3& vectorTwo)
		{
			Vec3 vec;
			vec.x = vectorOne.y * vectorTwo.z - vectorOne.z * vectorTwo.y;
			vec.y = vectorOne.z * vectorTwo.x - vectorOne.x * vectorTwo.z;
			vec.z = vectorOne.x * vectorTwo.y - vectorOne.y * vectorTwo.x;
			return vec;
		}
	}
}