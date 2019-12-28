#include "OpenGLBuffer.h"
#include <glad/glad.h>
#include <Raven/utils/Instrumentor.h>

namespace rvn {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		RVN_PROFILE_FUNCTION();
		glGenBuffers(1, &_id);
		glBindBuffer(GL_ARRAY_BUFFER, _id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::bind() const
	{
		RVN_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, _id);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		RVN_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
	{
		_layout = layout;
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		RVN_PROFILE_FUNCTION();
		glDeleteBuffers(1, &_id);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	{
		RVN_PROFILE_FUNCTION();
		_count = count;
		glGenBuffers(1, &_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
	}

	void OpenGLIndexBuffer::bind() const
	{
		RVN_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		RVN_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		RVN_PROFILE_FUNCTION();
		glDeleteBuffers(1, &_id);
	}
}