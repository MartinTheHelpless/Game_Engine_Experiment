#pragma once

#include "Core.h"

namespace Amber{
	class AMBER_API Application
	{

	public:
		Application(); 
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();

}
