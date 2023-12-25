#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Amber
{
	class AMBER_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application *CreateApplication();

}