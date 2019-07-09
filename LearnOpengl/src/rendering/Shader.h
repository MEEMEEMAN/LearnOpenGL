#pragma once
#include "perhapsPch.h"

class Shader
{
	unsigned int m_ID;
	public:
	Shader(GLenum shaderType, const std::string &shaderSrcCode);
	static std::string ParseShader(const std::string &filePath);
	void CompileShader(GLenum type, std::string shaderSrc);
	unsigned int& GetID();
};

class ShaderProgram
{
	std::unordered_map<std::string, int> m_UniformCache;
	unsigned int m_ID;
public:

	ShaderProgram();
	~ShaderProgram();
	void UseProgram();
	void AttachShader(Shader& shader);
	void DetachShader(Shader& shader);
	int GetUniformLocation(const std::string& name);
	void LinkProgram();

	void SetUniform3f(const std::string& name, glm::vec3 vec3);
	void SetMat4f(const std::string& name, const glm::mat4 Matrix4x4);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
};