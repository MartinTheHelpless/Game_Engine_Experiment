#pragma once

#include "Event.h"

namespace Amber {

	class AMBER_API MouseMovementEvent : public Event
	{
	public:
		MouseMovementEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovementEvent: " << m_MouseX << " ," << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMovement)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class AMBER_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const {
			return m_XOffset;
		}
		inline float GetYOffset() const {
			return m_YOffset;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << GetXOffset() << " ," << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class AMBER_API MouseButtonEvent : public Event
	{
	public: 
		inline int GetMouseButton() const { return m_Button; }
		 
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_Button(button) {};

		int m_Button;
	};

	class AMBER_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)  
	};

	class AMBER_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
