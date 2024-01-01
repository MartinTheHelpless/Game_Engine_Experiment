#include "precHeaders.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Amber
{ 
	 
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			AM_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();

		default:
			AM_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
		}
	}
}