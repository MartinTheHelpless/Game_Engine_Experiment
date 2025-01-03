#include "precHeaders.h"
#include "OrthographicCameraController.h"

#include "Amber/Core/Input.h"
#include "Amber/Core/KeyCodes.h"

namespace Amber
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
		: m_AspectRatio(aspectRatio), m_Rotation(rotation),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{

		if (Input::IsKeyPressed(AM_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

		else if (Input::IsKeyPressed(AM_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(AM_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		else if (Input::IsKeyPressed(AM_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		if(m_Rotation)
		{
			if (Input::IsKeyPressed(AM_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			else if (Input::IsKeyPressed(AM_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel * 2.5f;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(AM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(AM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e)
	{

		m_ZoomLevel -= e.GetYOffset() * 0.25f;

		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f); 

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}