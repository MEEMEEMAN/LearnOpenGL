#pragma once
#include "perhapsPch.h"

class Input
{
	static double MouseX, MouseY;
	static std::vector<int> m_heldKeyCache;
	static std::vector<int> m_MouseCache;
	static GLFWwindow* m_Window;
	static glm::vec2 m_MouseDelta;
	public:
	static bool GetKeyDown(int glkeycode);
	static bool GetKey(int glkeycode);
	static glm::vec2 GetMouseDelta();
	static void SetWindow(GLFWwindow* window);
	//Input update loop, includes glfwPollEvents() .
	static void Update();
	static bool GetMouseDown(int mouseKey);
	static bool GetMouse(int mouseKey);
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetWASDVector();
	static glm::vec2 GetScreenDimensions();
};
