#include "OpenGLVertexArray.h"

#include <glad/glad.h>
#include <NightFall/utils/Assert.h>

namespace nfe {
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
	void nfe::OpenGLVertexArray::bind() const
	{
		glBindVertexArray(_uid);
	}

	void nfe::OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void nfe::OpenGLVertexArray::addVertexBuffer(const VertexBuffer* vertexBuffer)
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
		_vertexBuffers.push_back((VertexBuffer*)vertexBuffer);
	}

	void nfe::OpenGLVertexArray::setIndexBuffer(const IndexBuffer* indexBuffer)
	{
		glBindVertexArray(_uid);
		_indexBuffer = (IndexBuffer*)indexBuffer;
		_indexBuffer->bind();
	}

	const std::vector<VertexBuffer*> OpenGLVertexArray::getVertexBuffers() const
	{
		return _vertexBuffers;
	}

	const IndexBuffer* nfe::OpenGLVertexArray::getIndexBuffer() const
	{
		return _indexBuffer;
	}
}