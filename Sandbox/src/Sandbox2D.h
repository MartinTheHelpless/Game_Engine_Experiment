#pragma once
#include "Amber.h" 

#include <imgui/imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class Sandbox2D : public Amber::Layer
{
public:

	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Amber::Timestep ts) override;

	virtual void OnImGuiRender() override;

	void OnEvent(Amber::Event& e) override;

private:
	Amber::OrthographicCameraController m_CameraController;

	Amber::Ref<Amber::VertexArray> m_SquareVA;
	Amber::Ref<Amber::Shader> m_Shader; 
	Amber::Ref<Amber::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
	glm::vec4 m_BackgroundColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	  
	struct ProfileResult
	{
		const char* Name;
		float time; 
	};

	std::vector<ProfileResult> m_ProfileResults;

};