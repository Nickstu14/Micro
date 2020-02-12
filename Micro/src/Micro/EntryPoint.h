#pragma once
#ifdef MC_PLATFORM_WINDOWS

extern Micro::Application* Micro::CreateApplication();

int main(int argc, char** argv)
{
	
	Micro::Log::Init();
	MC_CORE_WARN("Initialized Log!");
	int a = 5;
	MC_INFO("Hello! Var = {0}", a);
	
	auto app = Micro::CreateApplication();
	app->Run();
	delete app;
}
#endif