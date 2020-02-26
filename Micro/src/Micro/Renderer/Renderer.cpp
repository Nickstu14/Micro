#include "Mipch.h"
#include "Renderer.h"

namespace Micro {
	
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewPorjection", m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}

}