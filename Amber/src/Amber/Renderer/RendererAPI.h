#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Amber
{ 


	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DirectX11 = 2, DirectX10 = 3, DirectX9 = 4, DirectX8 = 5
		};
	public: 
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		
		static API s_API;
	}; 
}

