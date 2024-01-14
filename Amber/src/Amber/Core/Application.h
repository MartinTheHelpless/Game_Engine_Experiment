#pragma once

#include "Core.h"

#include "Window.h"
#include "Amber/Core/LayerStack.h"
#include "Amber/Events/Event.h"
#include "Amber/Events/ApplicationEvent.h"
#include "Amber/Renderer/OrthographicCamera.h" 

#include "Amber/ImGui/ImGuiLayer.h"

#include "Amber/Core/Timestep.h"

namespace Amber
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() {
			return *m_Window;
		}
		inline static Application& Get() {
			return *s_Instance;
		}
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime;

	private:
		static Application* s_Instance;
	
	};
	// To be defined in CLIENT
	Application* CreateApplication();
}