#pragma once
#include "perhapsPch.h"

void frameBufferCallback(GLFWwindow* window, int width, int height);
class OpenGLContext
{
	GLFWwindow* m_Window = nullptr;
	void EndPG();
public:
	OpenGLContext(const int& Width, const int& Height, const char* windowName);
	~OpenGLContext();
	GLFWwindow *GetWindow();
};