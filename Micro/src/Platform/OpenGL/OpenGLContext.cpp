#include "Mipch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad\glad.h>

namespace Micro
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MC_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MC_CORE_ASSERT(status, "Failed to initialize Glad!");

		OpenGLInfo();
	}

	void OpenGLContext::SwapBuffers()
	{

		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::OpenGLInfo()
	{
		MC_CORE_INFO("OpenGL Info:");
		MC_CORE_INFO("  Vendor:	{0}", glGetString(GL_RENDERER));
		MC_CORE_INFO("  Renderer:	{0}", glGetString(GL_VENDOR));
		MC_CORE_INFO("  Version:	{0}", glGetString(GL_VERSION));
	}
}