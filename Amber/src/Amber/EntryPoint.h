#pragma once

#ifdef AM_PLATFORM_WINDOWS

extern Amber::Application* Amber::CreateApplication();

int main(int argc, char** argv) {

	Amber::Log::Init();
	AM_CORE_WARN("Core Logger Initilized");
	AM_INFO("Client Logger Initilized");

	auto app = Amber::CreateApplication();
	app->Run();
	delete app;
}

#endif  

