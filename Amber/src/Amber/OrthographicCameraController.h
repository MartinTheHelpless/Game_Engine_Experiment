#pragma once

#include "Amber/Renderer/OrthographicCamera.h"
#include "Amber/Core/Timestep.h"
#include "Amber/Events/ApplicationEvent.h"
#include "Amber/Events/MouseEvent.h" 

namespace Amber
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);

		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		float GetZoomLevel() const { return m_ZoomLevel; }

	private:
		bool OnMouseScroll(MouseScrollEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; 

		float m_CameraTranslationSpeed = 2.0f, m_CameraRotationSpeed = 100.0f;

	};

}