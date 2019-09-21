#pragma once

#include <NightFall/rendering/RendererAPI.h>
#include <NightFall/core/Core.h>

namespace nfe {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void setClearColorRGBA(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const ref<VertexArray>& vertexArray) override;

		virtual void init() override;
	};

}