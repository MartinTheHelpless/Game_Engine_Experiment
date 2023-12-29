#include <Amber.h>

#include "imgui/imgui.h"

class ExampleLayer : public Amber::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		// AM_INFO("Example Layer::Update");

		if (Amber::Input::IsKeyPressed(AM_KEY_TAB))
			AM_INFO("TAB has been pressed");

	}

	virtual void OnImGuiRender() override
	{
	
		ImGui::Begin("Test");
		ImGui::Text("Hello");
		ImGui::End();
	
	}

	void OnEvent(Amber::Event& event) override
	{
		//AM_TRACE("{0}", event);
	}

};

class Sandbox : public Amber::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}
};
 
Amber::Application* Amber::CreateApplication() {

	return new Sandbox();

}