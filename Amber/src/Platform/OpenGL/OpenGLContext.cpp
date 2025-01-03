#include "precHeaders.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Amber {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AM_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		AM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AM_CORE_ASSERT(status, "Failed to initialize Glad!");

		AM_CORE_INFO("OpenGL Info:");
		AM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		AM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		AM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));


		#ifdef AM_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		glGetIntegerv( GL_MAJOR_VERSION,versionMajor);

		AM_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Amber requires at least OpenGL version 4.5 !");

		#endif

	}

	void OpenGLContext::SwapBuffers()
	{
		AM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}