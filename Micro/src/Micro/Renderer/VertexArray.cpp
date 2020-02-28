#include "Mipch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform\OpenGL\OpenGLVertexArray.h"

namespace Micro {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
			break;
		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}