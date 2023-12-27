#include <Amber.h>


class ExampleLayer : public Amber::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		// AM_INFO("Example Layer :: Update");
	}

	void OnEvent(Amber::Event& event) override
	{
		AM_TRACE("{0}", event);
	}

};

class Sandbox : public Amber::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Amber::ImGuiLayer());
		AM_INFO("Overlay has been created");
	}
	
	~Sandbox() {

	}
};
 
Amber::Application* Amber::CreateApplication() {

	return new Sandbox();

}