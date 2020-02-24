#include "Mipch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform\OpenGL\OpenGLContext.h"
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
	/*

	VertexArray::~VertexArray()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);

		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
	}
*/
}