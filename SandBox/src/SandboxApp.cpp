#include <Micro.h>

class ExampleLayer : public Micro::Layer 
{
public :
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//MC_INFO("ExampleLayer::Update");

		if (Micro::Input::IsKeyPressed(MC_KEY_TAB))
			MC_TRACE("Tab key is pressed!");
	}

	void OnEvent(Micro::Event& event) override
	{
		//MC_TRACE("{0}", event);
	}
};


class Sandbox : public Micro::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Micro::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Micro::Application* Micro::CreateApplication()
{
	return new Sandbox();
}