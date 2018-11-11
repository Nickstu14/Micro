#include <Micro.h>

class Sandbox : public Micro::Application
{
public :
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Micro::Application* Micro::CreateApplication()
{
	return new Sandbox();
}