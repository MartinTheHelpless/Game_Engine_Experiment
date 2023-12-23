#pragma once

#ifdef AM_PLATFORM_WINDOWS

extern Amber::Application* Amber::CreateApplication();

int main(int argc, char** argv) {

	auto app = Amber::CreateApplication();
	app->Run();
	delete app;
}

#endif  

