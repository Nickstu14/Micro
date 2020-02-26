#include <Micro.h>
#include "imgui\imgui.h"

class ExampleLayer : public Micro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CamPosition(0.0f)
	{
		m_VertexArray.reset(Micro::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f, 0.0f, 1.0f, 0.01f, 1.0f, 1.0f,
			0.5f,-0.5f, 0.0f, 0.0f, 0.01f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.01f, 0.0f, 1.0f
		};

		std::shared_ptr<Micro::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Micro::VertexBuffer::Create(vertices, sizeof(vertices)));
		Micro::BufferLayout layout = {
			{ Micro::ShaderDataType::Float3, "a_Position" },
		{ Micro::ShaderDataType::Float4, "a_Colour" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Micro::IndexBuffer> indexBuffer;
		indexBuffer.reset(Micro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Micro::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Micro::VertexBuffer> squareVB;// = std::make_shared<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
											   //Vertex Array ep 32 @ 33.55

		squareVB.reset(Micro::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(
			{
				{ Micro::ShaderDataType::Float3, "a_Position" }
			}
		);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<Micro::IndexBuffer> squareIB;
		squareIB.reset(Micro::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Colour;

			uniform mat4 u_ViewPorjection;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewPorjection * vec4(a_Position, 1.0);
			}
			
			)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 colour;
			in vec3 v_Position;
			in vec4 v_Colour;
			void main()
			{
				colour = vec4(v_Position * 0.5 + 0.5, 1.0);
				colour = v_Colour;
			}
			
			)";

		m_Shader.reset(new Micro::Shader(vertexSrc, fragmentSrc));

		std::string blueShadervertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			
			uniform mat4 u_ViewPorjection;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
			
				gl_Position = u_ViewPorjection * vec4(a_Position, 1.0);
			}
			
			)";
		std::string blueShaderfragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 colour;
		
		
			void main()
			{
				colour = vec4(0.2,0.3,0.8,1.0);
			
			}
			
			)";

		m_BlueShader.reset(new Micro::Shader(blueShadervertexSrc, blueShaderfragmentSrc));
	}
	void OnUpdate(Micro::TimeStep ts) override
	{

		MC_TRACE("DelterTime: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Micro::Input::IsKeyPressed(MC_KEY_A))
			m_CamPosition.x -= m_CamSpeed * ts;
		else if (Micro::Input::IsKeyPressed(MC_KEY_D))
			m_CamPosition.x += m_CamSpeed * ts;
		if (Micro::Input::IsKeyPressed(MC_KEY_S))
			m_CamPosition.y -= m_CamSpeed * ts;
		else if (Micro::Input::IsKeyPressed(MC_KEY_W))
			m_CamPosition.y += m_CamSpeed * ts;

		if (Micro::Input::IsKeyPressed(MC_KEY_Q))
			m_CamRot += m_CamRotSpeed * ts;
		else if (Micro::Input::IsKeyPressed(MC_KEY_E))
			m_CamRot -= m_CamRotSpeed * ts;


		Micro::RendererCommand::SetClearColour({ 0.2f, 0.2f, 0.2f, 1 });
		Micro::RendererCommand::Clear();

		m_Camera.SetPosition(m_CamPosition);
		m_Camera.SetRoation(m_CamRot);

		Micro::Renderer::BeginScene(m_Camera);

		Micro::Renderer::Submit(m_BlueShader, m_SquareVA);
		Micro::Renderer::Submit(m_Shader, m_VertexArray);

		Micro::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Micro::Event& event) override
	{

	}



private:
	std::shared_ptr<Micro::Shader> m_Shader;
	std::shared_ptr<Micro::VertexArray>m_VertexArray;

	std::shared_ptr<Micro::Shader> m_BlueShader;
	std::shared_ptr<Micro::VertexArray>m_SquareVA;

	Micro::OrthographicCamera m_Camera;
	glm::vec3 m_CamPosition;
	float m_CamSpeed = 5.0f;
	float m_CamRot = 0;
	float m_CamRotSpeed = 180.0f;

};


class Sandbox : public Micro::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Micro::Application* Micro::CreateApplication()
{
	return new Sandbox();
}