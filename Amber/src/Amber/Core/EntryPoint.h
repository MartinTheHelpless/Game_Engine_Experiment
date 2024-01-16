#pragma once

#ifdef AM_PLATFORM_WINDOWS

extern Amber::Application* Amber::CreateApplication();

int main(int argc, char** argv) {

	Amber::Log::Init(); 

	AM_PROFILE_BEGIN_SESSION("Amber", "AmberProfile-Startup.json");

	auto app = Amber::CreateApplication(); 
	
	AM_PROFILE_END_SESSION(); 
	AM_PROFILE_BEGIN_SESSION("Amber", "AmberProfile-Runtime.json");
	 
	app->Run();

	AM_PROFILE_END_SESSION(); 
	AM_PROFILE_BEGIN_SESSION("Amber", "AmberProfile-Shutdown.json");

	delete app;

	AM_PROFILE_END_SESSION();

}

#endif  

