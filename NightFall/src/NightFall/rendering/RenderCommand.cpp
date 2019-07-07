#include "RenderCommand.h"
#include <NightFall/platform/opengl/OpenGLRendererAPI.h>

namespace nfe {
		
	RendererAPI* RenderCommand::s_api = new OpenGLRendererAPI();

}