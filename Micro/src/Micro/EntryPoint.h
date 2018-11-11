#pragma once
#ifdef MC_PLATFORM_WINDOWS

extern Micro::Application* Micro::CreateApplication();

int main(int argc, char** argv)
{

	auto app = Micro::CreateApplication();
	app->Run();
	delete app;
}
#endif