#include "Mipch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform\OpenGL\OpenGLShader.h"

namespace Micro
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
			break;
		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
			break;
		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}