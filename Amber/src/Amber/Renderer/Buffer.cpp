#include "precHeaders.h"
#include "Buffer.h"

#include "Renderer.h" 

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Amber
{ 

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AM_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
			break;

		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
			break;

		default:
			AM_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
			break;
		} 
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AM_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
			break;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
			break;

		default:
			AM_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
			break;
		}
	}

}