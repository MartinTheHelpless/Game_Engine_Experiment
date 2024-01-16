#include "precHeaders.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Amber
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AM_CORE_ASSERT(false, "Renderer not recognized while loading texture");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);

		default:
			AM_CORE_ASSERT(false, "Renderer not recognized while loading texture");
			return nullptr;
		}

		return Ref<Texture2D>();
	}



	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AM_CORE_ASSERT(false, "Renderer not recognized while loading texture");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);

		default:
			AM_CORE_ASSERT(false, "Renderer not recognized while loading texture");
			return nullptr;
		}

		return Ref<Texture2D>();
	}
	 
}