#pragma once
#ifdef MC_PLATFORM_WINDOWS

extern Micro::Application* Micro::CreateApplication();

int main(int argc, char** argv)
{
	int a = 5;
	Micro::Log::Init();
	MC_CORE_WARN("Initialized Log!");
	MC_INFO("Hello! "); // var = { 0 }", a);

	auto app = Micro::CreateApplication();
	app->Run();
	delete app;
}
#endif