#include "Mipch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform\OpenGL\OpenGLTexture.h"

namespace Micro
{
	 Ref<Texture2D> Texture2D::Create(const std::string& path)
	 {
		
			 switch (Renderer::GetAPI())
			 {
			 case RendererAPI::API::None: MC_CORE_ASSERT(false, "RendererAPI::None is currently not suported") return nullptr;
				 break;
			 case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
				 break;
			 }

			 MC_CORE_ASSERT(false, "Unknown RendererAPI!");
			 return nullptr;
	 }
}