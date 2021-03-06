#pragma once

#include "Micro\Renderer\RendererAPI.h"

namespace Micro
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		//OpenGLRendererAPI();
		//~OpenGLRendererAPI();
		virtual void Init() override;
		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear()override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray)override;

	private:

	};

	/*OpenGLRendererAPI::OpenGLRendererAPI()
	{
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}*/
}