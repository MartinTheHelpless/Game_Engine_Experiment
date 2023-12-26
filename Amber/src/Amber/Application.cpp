#include "precHeaders.h"
#include "Application.h"

#include "Amber/Events/ApplicationEvent.h"
#include "Amber/Events/MouseEvent.h"
#include "Amber/Events/KeyEvent.h"
#include "Amber/Log.h"

namespace Amber
{

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{

		WindowResizeEvent e (1200, 100);
		AM_TRACE(e);

		while (m_Running) {

			m_Window->OnUpdate();

		}
	}

}