#include <Micro.h>
#include "Platform\OpenGL\OpenGLShader.h"
#include "imgui\imgui.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


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

		Micro::Ref<Micro::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Micro::VertexBuffer::Create(vertices, sizeof(vertices)));
		Micro::BufferLayout layout = {
			{ Micro::ShaderDataType::Float3, "a_Position" },
		{ Micro::ShaderDataType::Float4, "a_Colour" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		Micro::Ref<Micro::IndexBuffer> indexBuffer;
		indexBuffer.reset(Micro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Micro::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Micro::Ref<Micro::VertexBuffer> squareVB;// = std::make_shared<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
											   //Vertex Array ep 32 @ 33.55

		squareVB.reset(Micro::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(
			{
				{ Micro::ShaderDataType::Float3, "a_Position" },
				{ Micro::ShaderDataType::Float2, "a_TexCoord" }
			}
		);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0,1,2,2,3,0 };
		Micro::Ref<Micro::IndexBuffer> squareIB;
		squareIB.reset(Micro::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Colour;

			uniform mat4 u_ViewPorjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewPorjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader.reset(Micro::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShadervertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			
			uniform mat4 u_ViewPorjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
			
				gl_Position = u_ViewPorjection * u_Transform *  vec4(a_Position, 1.0);
			}
			
			)";
		std::string flatColourShaderFragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 colour;
			
			uniform vec3 u_Colour;
		
			void main()
			{
				colour = vec4(u_Colour, 1.0);
			
			}
			
			)";

		m_flatColourShader.reset(Micro::Shader::Create(blueShadervertexSrc, flatColourShaderFragmentSrc));

		std::string textureShadervertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=0) in vec2 a_TextCoord;
			
			uniform mat4 u_ViewPorjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TextCoord;
			
				gl_Position = u_ViewPorjection * u_Transform *  vec4(a_Position, 1.0);
			}
			
			)";
		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 colour;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
		
			void main()
			{
				colour = texture(u_Texture, v_TexCoord);
			
			}
			
			)";

		m_TextureShader.reset(Micro::Shader::Create(textureShadervertexSrc, textureShaderFragmentSrc));

		m_Texture = (Micro::Texture2D::Create("assets/textures/Checkerboard.png"));

		std::dynamic_pointer_cast<Micro::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Micro::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}
	void OnUpdate(Micro::TimeStep ts) override
	{

		//MC_TRACE("DelterTime: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

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

		//Micro::Material* material = new Micro::Material(m_flatColourShader);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Micro::OpenGLShader>(m_flatColourShader)->Bind();
		std::dynamic_pointer_cast<Micro::OpenGLShader>(m_flatColourShader)->UploadUniformFloat3("u_Colour", m_SquareColour);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)* scale;
				Micro::Renderer::Submit(m_flatColourShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Micro::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle		
		//Micro::Renderer::Submit(m_Shader, m_VertexArray);

		Micro::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("settings");
		ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColour));
		ImGui::End();
	}

	void OnEvent(Micro::Event& event) override
	{

	}



private:
	Micro::Ref<Micro::Shader> m_Shader;
	Micro::Ref<Micro::VertexArray>m_VertexArray;

	Micro::Ref<Micro::Shader> m_flatColourShader;
	Micro::Ref<Micro::Shader> m_TextureShader;
	Micro::Ref<Micro::VertexArray>m_SquareVA;

	Micro::Ref<Micro::Texture2D> m_Texture;

	Micro::OrthographicCamera m_Camera;
	glm::vec3 m_CamPosition;
	float m_CamSpeed = 5.0f;
	float m_CamRot = 0;
	float m_CamRotSpeed = 180.0f;

	glm::vec3 m_SquareColour = { 0.2f, 0.3f , 0.8f };



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