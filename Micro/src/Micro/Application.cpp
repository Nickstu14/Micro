#include "Mipch.h"

#include "Application.h"

#include "Micro\Events\ApplicationEvent.h"
#include "Micro\Log.h"

namespace Micro
{

	Application::Application()
	{
	}


	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		MC_TRACE(e);

		while (true);

	}
}