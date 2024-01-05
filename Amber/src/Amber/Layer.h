#pragma once
 
#include "Amber/Core.h"
#include "Amber/Events/Event.h" 

#include "Amber/Core/Timestep.h"

namespace Amber {

	class AMBER_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnImGuiRender() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}