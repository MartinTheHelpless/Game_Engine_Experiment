#include "precHeaders.h"
#include "WindowsInput.h"

#include "Amber/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Amber
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;

	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;

		return false;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x,y ;
		glfwGetCursorPos(window, &x, &y); 

		return {(float)x, (float)y};
	}

	float WindowsInput::GetMouseXImpl()
	{ 
		return GetMousePositionImpl().first;
	}

	float WindowsInput::GetMouseYImpl()
	{
		return GetMousePositionImpl().second;
	}


}
