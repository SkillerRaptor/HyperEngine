#pragma once

#include <queue>

#include "HyperMath/Matrix.hpp"
#include "HyperMath/Vector.hpp"
#include "HyperUtilities/NonCopyable.hpp"
#include "HyperUtilities/NonMoveable.hpp"

namespace Hyperion
{
	struct ShaderData
	{
		std::string VertexShaderPath = "";
		std::string FragmentShaderPath = "";
		std::string GeometryShaderPath = "";
	};

	class ShaderManager : public NonCopyable, NonMoveable
	{
	protected:
		std::queue<uint32_t> m_ShaderIds;

	public:
		ShaderManager() = default;
		virtual ~ShaderManager() = default;

		virtual uint32_t CreateShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "") = 0;
		virtual bool UseShader(uint32_t handle) = 0;
		virtual bool DeleteShader(uint32_t handle) = 0;

		virtual void SetInteger(uint32_t handle, const std::string& name, int value) = 0;
		virtual void SetUnsignedInteger(uint32_t handle, const std::string& name, unsigned int value) = 0;
		virtual void SetIntegerArray(uint32_t handle, const std::string& name, size_t count, int* values) = 0;

		virtual void SetFloat(uint32_t handle, const std::string& name, float value) = 0;
		virtual void SetFloatArray(uint32_t handle, const std::string& name, size_t count, float* values) = 0;

		virtual void SetVector2(uint32_t handle, const std::string& name, float x, float y) = 0;
		virtual void SetVector2(uint32_t handle, const std::string& name, const Vec2& vector) = 0;

		virtual void SetVector3(uint32_t handle, const std::string& name, float x, float y, float z) = 0;
		virtual void SetVector3(uint32_t handle, const std::string& name, const Vec3& vector) = 0;

		virtual void SetVector4(uint32_t handle, const std::string& name, float x, float y, float z, float w) = 0;
		virtual void SetVector4(uint32_t handle, const std::string& name, const Vec4& vector) = 0;

		virtual void SetMatrix2(uint32_t handle, const std::string& name, const Mat2& matrix) = 0;
		virtual void SetMatrix3(uint32_t handle, const std::string& name, const Mat3& matrix) = 0;
		virtual void SetMatrix4(uint32_t handle, const std::string& name, const Mat4& matrix) = 0;

		virtual const std::string GetVertexShaderPath(uint32_t handle) = 0;
		virtual const std::string GetFragmentShaderPath(uint32_t handle) = 0;
		virtual const std::string GetGeometryShaderPath(uint32_t handle) = 0;
	};
}
