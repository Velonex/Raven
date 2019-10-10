#include "OpenGLVertexArray.h"

#include <glad/glad.h>
#include <Raven/utils/Assert.h>

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
		glCreateVertexArrays(1, &_uid);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &_uid);
	}
	void rvn::OpenGLVertexArray::bind() const
	{
		glBindVertexArray(_uid);
	}

	void rvn::OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void rvn::OpenGLVertexArray::addVertexBuffer(const ref<VertexBuffer>& vertexBuffer)
	{
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
#pragma warning(push)
#pragma warning(disable : 4312)
				(const void*)element.offset);
#pragma warning(pop)
			index++;
		}
		_vertexBuffers.push_back((ref<VertexBuffer>&)vertexBuffer);
	}

	void rvn::OpenGLVertexArray::setIndexBuffer(const ref<IndexBuffer>& indexBuffer)
	{
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