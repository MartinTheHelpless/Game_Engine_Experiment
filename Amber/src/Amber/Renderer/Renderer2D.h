#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"

namespace Amber
{

	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		  
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const float& scale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const float& scale = 1.0f);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& scale = 1.0f, const glm::vec4& color = { 1.0, 1.0, 1.0, 1.0 });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture , const float& scale = 1.0f, const glm::vec4& color = { 1.0, 1.0, 1.0, 1.0 });
	};
	 
}