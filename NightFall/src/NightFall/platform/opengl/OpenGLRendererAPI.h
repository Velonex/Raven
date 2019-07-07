#pragma once

#include <NightFall/rendering/RendererAPI.h>

namespace nfe {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void setClearColorRGBA(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const VertexArray* vertexArray) override;
	};

}