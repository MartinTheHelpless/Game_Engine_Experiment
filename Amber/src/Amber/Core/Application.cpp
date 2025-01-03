#include "precHeaders.h"
#include "Amber/Core/Application.h"

#include "Amber/Core/Log.h"
#include "Amber/Core/Input.h"
#include "Amber/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Amber
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AM_PROFILE_FUNCTION();

		AM_CORE_ASSERT(!s_Instance, "Application already exists! ");

		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		AM_PROFILE_FUNCTION();


		while (m_Running)
		{
			AM_PROFILE_SCOPE("Run Loop"); 

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

				if (!m_Minimized) {
					{
						AM_PROFILE_SCOPE("LayerStack OnUpdate");

						for (Layer* layer : m_LayerStack)
							layer->OnUpdate(timestep);

					}
					
					
							m_ImGuiLayer->Begin();
					{
						AM_PROFILE_SCOPE("OnImGuiRender");
						for (Layer* layer : m_LayerStack)
							layer->OnImGuiRender();
					}
						m_ImGuiLayer->End();
				}
			{  
				m_Window->OnUpdate();
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		AM_PROFILE_FUNCTION();


		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		m_Minimized = false;

		return false;
	}

}