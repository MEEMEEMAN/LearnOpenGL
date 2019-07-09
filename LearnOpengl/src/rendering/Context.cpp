#include "Context.h"

OpenGLContext::OpenGLContext(const int& Width, const int& Height, const char* windowName) : m_Window(nullptr)
{
	GLFWwindow* window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
	{
		EndPG();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Width, Height, windowName, NULL, NULL);

	if (!window)
	{
		conlog("Unable to create a GLFW window context.");
		glfwTerminate();
		EndPG();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		conlog("Unable to load glad.");
		glfwTerminate();
		EndPG();
		return;
	}
	GLCall(glViewport(0, 0, Width, Height));
	glfwSetFramebufferSizeCallback(window, frameBufferCallback);

	conlog("Using OpenGL Version: " << glGetString(GL_VERSION));
	m_Window = window;
}

OpenGLContext::~OpenGLContext()
{
	glfwTerminate();
}

GLFWwindow* OpenGLContext::GetWindow()
{
	return m_Window;
}

void frameBufferCallback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}

void OpenGLContext::EndPG()
{
	conlog("Press enter to continue");
	std::cin.get();
}
