#pragma once

#include "Core.h"

#include "Window.h"
#include "Amber/LayerStack.h"
#include "Amber/Events/Event.h"
#include "Amber/Events/ApplicationEvent.h"

namespace Amber
{
	class AMBER_API Application
	{

	public:
		Application();
		virtual ~Application();
		 
		void Run();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer);

		void PushOverlay(Layer *layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application *CreateApplication();

}
