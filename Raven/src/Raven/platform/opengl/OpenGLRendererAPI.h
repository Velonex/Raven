#pragma once

#include <Raven/rendering/RendererAPI.h>
#include <Raven/core/Core.h>

namespace rvn {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void setClearColorRGBA(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const ref<VertexArray>& vertexArray) override;

		virtual void init() override;
	};

}