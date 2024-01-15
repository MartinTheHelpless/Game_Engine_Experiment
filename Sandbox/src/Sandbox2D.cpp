#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
 

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController((float)(1280.0f / 720.0f))
{

}

void Sandbox2D::OnAttach()
{ 
	m_Texture = Amber::Texture2D::Create("assets/Textures/Checkerboard.png"); 
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Amber::Timestep ts)
{

	m_CameraController.OnUpdate(ts);

	Amber::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1});
	Amber::RenderCommand::Clear();

	Amber::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Amber::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
	Amber::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.8f, 0.2f, 0.3f, 1.0f});
	Amber::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
	Amber::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Color Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Amber::Event& e)
{
	m_CameraController.OnEvent(e);
}
