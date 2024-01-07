#include "precHeaders.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Amber
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AM_CORE_ASSERT(false, "Renderer not recognized while loading texture");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);

		default:
			AM_CORE_ASSERT(false, "Renderer not recognized while loading texture");
			return nullptr;
		}

		return Ref<Texture2D>();
	}

	Texture2D::Texture2D(const std::string& path)
	{ 
		Create(path); 
	}
}