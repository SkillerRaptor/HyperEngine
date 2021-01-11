#include "OpenGL33VertexArray.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hyperion
{
	OpenGL33VertexArray::OpenGL33VertexArray(VertexLayout vertexLayout)
		: m_RendererId(0), m_VertexLayout(vertexLayout)
	{
		glGenVertexArrays(1, &m_RendererId);
		glBindVertexArray(m_RendererId);
		glBindVertexArray(0);
	}

	OpenGL33VertexArray::~OpenGL33VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGL33VertexArray::Init()
	{
		switch (m_VertexLayout)
		{
		case VertexLayout::Vertex2D:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Color));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TextureCoords));
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TextureId));
			glEnableVertexAttribArray(3);
			break;

		case VertexLayout::Vertex3D:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void*)offsetof(Vertex3D, Position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void*)offsetof(Vertex3D, Color));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void*)offsetof(Vertex3D, TextureCoords));
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex3D), (const void*)offsetof(Vertex3D, TextureId));
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void*)offsetof(Vertex3D, Normals));
			glEnableVertexAttribArray(4);

			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void*)offsetof(Vertex3D, Tangent));
			glEnableVertexAttribArray(5);

			glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void*)offsetof(Vertex3D, Bitangent));
			glEnableVertexAttribArray(6);
			break;
		}
	}

	void OpenGL33VertexArray::Bind()
	{
		glBindVertexArray(m_RendererId);
	}

	void OpenGL33VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	uint32_t OpenGL33VertexArray::GetRendererId() const
	{
		return m_RendererId;
	}

	VertexLayout OpenGL33VertexArray::GetVertexLayout() const
	{
		return m_VertexLayout;
	}
}
