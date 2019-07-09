#include "Input.h"

std::vector<int> Input::m_heldKeyCache;
std::vector<int> Input::m_MouseCache;
GLFWwindow* Input::m_Window;
double Input::MouseX = 0.0f, Input::MouseY = 0.0f;
glm::vec2 Input::m_MouseDelta;

bool Input::GetKeyDown(int glkeycode)
{
	if (glfwGetKey(m_Window, glkeycode) == GLFW_PRESS)
	{
		auto iterator = std::find(m_heldKeyCache.begin(), m_heldKeyCache.end(), glkeycode);

		if (iterator == m_heldKeyCache.end())
		{
			m_heldKeyCache.push_back(glkeycode);
			return true;
		}
	}

	return false;
}

bool Input::GetKey(int glkeycode)
{
	int pressed = glfwGetKey(m_Window, glkeycode);

	if (pressed == GLFW_PRESS)
		return true;

	return false;
}

glm::vec2 Input::GetMouseDelta()
{
	return m_MouseDelta;
}

void Input::SetWindow(GLFWwindow* window)
{
	m_Window = window;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::Update()
{
	GLCall(glfwPollEvents());

	if (m_heldKeyCache.size() > 0)
	{	
		for (unsigned int i = 0; i < m_heldKeyCache.size(); i++)
		{
			int keycode = m_heldKeyCache.at(i);
			if (glfwGetKey(m_Window, keycode) == GLFW_RELEASE)
			{
				m_heldKeyCache.erase(m_heldKeyCache.begin() + i);
			}
		}
	}

	if (m_MouseCache.size() > 0)
	{
		for (unsigned int i = 0; i < m_MouseCache.size(); i++)
		{
			int button = m_MouseCache.at(i);
			if (glfwGetMouseButton(m_Window, button) == GLFW_RELEASE)
			{
				m_MouseCache.erase(m_MouseCache.begin() + i);
			}
		}
	}


	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);
#pragma warning(push)
#pragma warning(disable: 4244)
	float xdelta = xpos - MouseX;
	float ydelta = ypos - MouseY;
#pragma warning(pop)

	m_MouseDelta.x = xdelta;
	m_MouseDelta.y = ydelta;
	MouseX = xpos;
	MouseY = ypos;
}

bool Input::GetMouseDown(int mouseButton)
{
	if (glfwGetMouseButton(m_Window, mouseButton) == GLFW_PRESS)
	{
		auto iterator = std::find(m_MouseCache.begin(), m_MouseCache.end(), mouseButton);

		if (iterator == m_MouseCache.end())
		{
			m_MouseCache.push_back(mouseButton);
			return true;
		}
	}

	return false;
}

bool Input::GetMouse(int mouseButton)
{
	if (glfwGetMouseButton(m_Window, mouseButton) == GLFW_PRESS)
		return true;

	return false;
}

glm::vec2 Input::GetMousePosition()
{
	return glm::vec2(MouseX, MouseY);
}

glm::vec2 Input::GetWASDVector()
{
	float forward = 0, side = 0;
	if (GetKey(GLFW_KEY_W))
	{
		forward += 1;
	}
	if (GetKey(GLFW_KEY_S))
	{
		forward -= 1;
	}
	if (GetKey(GLFW_KEY_D))
	{
		side += 1;
	}
	if (GetKey(GLFW_KEY_A))
	{
		side -= 1;
	}

	if (forward == 0 && side == 0)
	{
		return glm::vec2(0,0);
	}

	glm::vec2 wasdvec = glm::vec2(forward, side);
	wasdvec = glm::normalize(wasdvec);
	
	return wasdvec;
}

glm::vec2 Input::GetScreenDimensions()
{
	return glm::vec2(800,600);
}
