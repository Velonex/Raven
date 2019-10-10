#include "OpenGLRenderer.h"

#include <glad/glad.h>

namespace rvn {

	void OpenGLRenderer::setClearColorRGBA(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void OpenGLRenderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
}