#include "OpenGLRenderer.h"

#include <glad/glad.h>

namespace nfe {

	void OpenGLRenderer::setClearColorRGBA(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

}