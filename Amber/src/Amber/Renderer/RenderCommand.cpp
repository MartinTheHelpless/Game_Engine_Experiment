#include "precHeaders.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Amber
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
 
}