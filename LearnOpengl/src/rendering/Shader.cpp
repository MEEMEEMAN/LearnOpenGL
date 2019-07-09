#include "Shader.h"

void Shader::CompileShader(GLenum type, std::string shaderSrc)
{
	const char* src = shaderSrc.c_str();
	GLCall(glShaderSource(m_ID, 1, &src, nullptr));
	GLCall(glCompileShader(m_ID));

	int result;
	glGetShaderiv(m_ID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		GLCall(glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(m_ID, length, &length, message));
		std::cout << "*** FAILED TO COMPILE SHADER***\n";
		std::cout << "Shader id: " << m_ID << "\n";
		std::cout << message;
		std::cout << "*******************************\n";
		GLCall(glDeleteShader(m_ID));
	}
}

unsigned int& Shader::GetID()
{
	return m_ID;
}

Shader::Shader(GLenum shaderType ,const std::string& shaderSrcCode) : m_ID(0)
{
	if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER)
	{
		conlog("Are you even making a shader, bro?");
		return;
	}
	
	m_ID = glCreateShader(shaderType);
	CompileShader(shaderType, shaderSrcCode);
}

std::string Shader::ParseShader(const std::string& filePath)
{
	std::stringstream ss;
	std::ifstream stream(filePath);
	std::string line;

	while (std::getline(stream, line))
	{
		ss << line << "\n";
	}
	stream.close();
	
	return ss.str();
}

void ShaderProgram::SetUniform3f(const std::string& name, glm::vec3 vec3)
{
	GLCall(glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z));
}

void ShaderProgram::SetMat4f(const std::string& name, const glm::mat4 Matrix4x4)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &Matrix4x4[0][0]););
}

void ShaderProgram::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void ShaderProgram::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void ShaderProgram::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

ShaderProgram::ShaderProgram() : m_ID(0)
{
	m_ID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteProgram(m_ID));
}

void ShaderProgram::UseProgram()
{
	GLCall(glUseProgram(m_ID));
}

void ShaderProgram::AttachShader(Shader& shader)
{
	GLCall(glAttachShader(m_ID, shader.GetID()));
}

void ShaderProgram::DetachShader(Shader& shader)
{
	GLCall(glDetachShader(m_ID, shader.GetID()));
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (m_UniformCache.find(name) != m_UniformCache.end())
	{
		return m_UniformCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_ID, name.c_str()))
		if (location == -1)
		{
			std::cout << "'" << name << "' Uniform doesnt exist\n";
		}
		else
		{
			m_UniformCache[name] = location;
		}

	return location;
}

void ShaderProgram::LinkProgram()
{
	GLCall(glLinkProgram(m_ID));
	GLCall(glValidateProgram(m_ID))
}
