#include "OpenGLVertexArray.h"

#include <glad/glad.h>
#include <Raven/utils/Assert.h>
#include <raven/utils/Instrumentor.h>

namespace rvn {
	static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		RVN_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &_uid);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		RVN_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &_uid);
	}
	void rvn::OpenGLVertexArray::bind() const
	{
		RVN_PROFILE_FUNCTION();
		glBindVertexArray(_uid);
	}

	void rvn::OpenGLVertexArray::unbind() const
	{
		RVN_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void rvn::OpenGLVertexArray::addVertexBuffer(const ref<VertexBuffer>& vertexBuffer)
	{
		RVN_PROFILE_FUNCTION();
		ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(_uid);
		vertexBuffer->bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.getComponentCount(),
				shaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset);
			index++;
		}
		_vertexBuffers.push_back((ref<VertexBuffer>&)vertexBuffer);
	}

	void rvn::OpenGLVertexArray::setIndexBuffer(const ref<IndexBuffer>& indexBuffer)
	{
		RVN_PROFILE_FUNCTION();
		glBindVertexArray(_uid);
		_indexBuffer = (ref<IndexBuffer>&)indexBuffer;
		_indexBuffer->bind();
	}

	const std::vector<ref<VertexBuffer>> OpenGLVertexArray::getVertexBuffers() const
	{
		return _vertexBuffers;
	}

	const ref<IndexBuffer> rvn::OpenGLVertexArray::getIndexBuffer() const
	{
		return _indexBuffer;
	}
}