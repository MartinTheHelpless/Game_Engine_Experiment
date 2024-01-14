#include "precHeaders.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Amber
{ 
	 
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{ 
			case RendererAPI::API::None:
				AM_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();

			case RendererAPI::API::DirectX11:
				return nullptr;
			case RendererAPI::API::DirectX10:
				return nullptr;
			case RendererAPI::API::DirectX9:
				return nullptr;
			case RendererAPI::API::DirectX8:
				return nullptr;
			default:
				AM_CORE_ASSERT(false, "Unknown renderer API.");
				return nullptr;
			}
		
	}
}