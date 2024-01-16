#pragma once

#include "Amber/Core/Layer.h" 

#include "Amber/Events/KeyEvent.h"
#include "Amber/Events/MouseEvent.h"
#include "Amber/Events/ApplicationEvent.h"


namespace Amber {

	class AMBER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override; 

		void Begin();
		void End();
	private:
		 
		float m_Time = 0.0f;
	};


}