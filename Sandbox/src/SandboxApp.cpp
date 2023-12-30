#include <Amber.h>

#include "imgui/imgui.h"

class ExampleLayer : public Amber::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override
	{
		if (Amber::Input::IsKeyPressed(AM_KEY_TAB))
			AM_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Amber::Event& event) override
	{
		if (event.GetEventType() == Amber::EventType::KeyPressed)
		{
			Amber::KeyPressedEvent& e = (Amber::KeyPressedEvent&)event;
			if (e.GetKeyCode() == AM_KEY_TAB)
				AM_TRACE("Tab key is pressed (event)!");
			AM_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};
class Sandbox : public Amber::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer()); 
	}

	~Sandbox()
	{
	}
};
Amber::Application* Amber::CreateApplication()
{
	return new Sandbox();
}