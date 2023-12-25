#include "Application.h"

#include "Amber/Events/ApplicationEvent.h"
#include "Amber/Events/MouseEvent.h"
#include "Amber/Events/KeyEvent.h"
#include "Amber/Log.h"

namespace Amber
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{

		WindowResizeEvent e (1200, 100);
		AM_TRACE(e);

		while (true) ;
	}

}