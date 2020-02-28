#include "Mipch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform\OpenGL\OpenGLBuffer.h"
namespace Micro
{
	//Vertex Buffer -------------------------------------------------------
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
			break;
		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	//Index Buffer -------------------------------------------------------
	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indicies, size);
			break;
		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

