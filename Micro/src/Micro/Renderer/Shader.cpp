#include "Mipch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform\OpenGL\OpenGLShader.h"

namespace Micro
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::API::OpenGL: return std::make_shared< OpenGLShader>(filepath);
			break;
		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
			break;
		case RendererAPI::API::OpenGL: return std::make_shared< OpenGLShader>(name, vertexSrc, fragmentSrc);
			break;
		}

		MC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name,const Ref<Shader>& shader)
	{
		MC_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shader[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string & filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string & name, const std::string & filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string & name)
	{
		MC_CORE_ASSERT(Exists(name), "Shadernot found!");
		return m_Shader[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shader.find(name) != m_Shader.end();
	}

}