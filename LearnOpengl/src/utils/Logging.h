#pragma once 
#include <iostream>
#include "glfw3.h"

#define conlog(x) std::cout << x << "\n"
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void  GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		conlog("*** ERROR ***");
		conlog("Code: " << error);
		conlog("On Line: "<< line);
		conlog("On Function: "<<function);
		conlog("On file: "<< file);
		return false;
	}
	return true;
}