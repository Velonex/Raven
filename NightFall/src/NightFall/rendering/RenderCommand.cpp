#include "RenderCommand.h"
#include <NightFall/platform/opengl/OpenGLRendererAPI.h>

namespace nfe {
		
	scope<RendererAPI> RenderCommand::s_api = createScope<OpenGLRendererAPI>();

}