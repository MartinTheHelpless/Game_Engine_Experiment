#include "precHeaders.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace Amber
{
	
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				AM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				break;
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(filepath);

			default:
				AM_CORE_ASSERT(false, "Unknown Renderer API!");
				return nullptr;
				break;
		}

		return nullptr;
	} 

}