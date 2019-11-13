#pragma once

#include <string>
#include <GL/glew.h>

class GLSLProgram {
private:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	int m_nAttributes;

public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void LinkShaders();
	void AddAttribute(const std::string& name);

	void Use();
	void Unuse();

private:
	void CompileShader(const std::string& shaderPath, GLuint id);
};

