#pragma once
#include "Core.h"
#include "Window.h"
#include "Events\Event.h"
#include "LayerStack.h"
#include "Micro\Events\ApplicationEvent.h"
#include "Micro\ImGui\ImGuiLayer.h"

#include "Micro\Renderer\Shader.h"


namespace Micro
{
	class MICRO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;

		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}