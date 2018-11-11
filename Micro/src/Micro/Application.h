#pragma once
#include "Core.h"

namespace Micro
{
	class MICRO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();
}