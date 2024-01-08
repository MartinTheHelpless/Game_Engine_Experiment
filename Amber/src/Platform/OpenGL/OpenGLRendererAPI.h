#pragma once

#include "Amber/Renderer/RendererAPI.h"

namespace Amber
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}
