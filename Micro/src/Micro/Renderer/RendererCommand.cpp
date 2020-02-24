#include "Mipch.h"
#include"RendererCommand.h"

#include "Platform\OpenGL\OpenGLRendererAPI.h"

namespace Micro
{
	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}