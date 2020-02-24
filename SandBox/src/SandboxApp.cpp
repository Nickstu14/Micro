#include <Micro.h>


class ExampleLayer : public Micro::Layer 
{
public :
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//MC_INFO("ExampleLayer::Update");
		
		
	}
	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Micro::Event& event) override
	{
		//MC_TRACE("{0}", event);
		if (event.GetEventType() == Micro::EventType::KeyPressed)
		{
			Micro::KeyPressedEvent& e = (Micro::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MC_KEY_TAB)
				MC_TRACE("Tab key is pressed (event)!");
			MC_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
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