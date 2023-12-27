#pragma once

#include "Amber/Layer.h" 

#include "Amber/Events/KeyEvent.h"
#include "Amber/Events/MouseEvent.h"
#include "Amber/Events/ApplicationEvent.h"


namespace Amber {

	class AMBER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrollEvent(MouseScrollEvent& e);
		bool OnMouseMoveEvent(MouseMovementEvent& e);

		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);

		float m_Time = 0.0f;
	};


}