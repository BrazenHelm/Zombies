#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace MyGameEngine {

GLSLProgram::GLSLProgram() :
	m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_nAttributes(0) {
}


GLSLProgram::~GLSLProgram() {
}


void GLSLProgram::CompileShaders(const std::string& vertexShaderPath, const std::string&fragmentShaderPath) {

	m_programID = glCreateProgram();

	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0) {
		FatalError("Vertex Shader could not be created.");
	}
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0) {
		FatalError("Fragment Shader could not be created.");
	}

	CompileShader(vertexShaderPath, m_vertexShaderID);
	CompileShader(fragmentShaderPath, m_fragmentShaderID);
}


void GLSLProgram::CompileShader(const std::string& path, GLuint id) {

	std::ifstream file;
	file.open(path);
	if (file.fail()) {
		FatalError("Failed to open " + path);
	}

	std::string fileContents{ "" };
	std::string line;
	while (std::getline(file, line)) {
		fileContents += (line + "\n");
	}

	file.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {

		GLint logLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> errorLog(logLength);
		glGetShaderInfoLog(id, logLength, &logLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shader " + path + " failed to compile.");

		return;
	}
}


void GLSLProgram::LinkShaders() {

	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);
	glLinkProgram(m_programID);

	GLint success = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

	if (success == GL_FALSE) {

		GLint logLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> errorLog(logLength);
		glGetProgramInfoLog(m_programID, logLength, &logLength, &errorLog[0]);

		glDeleteProgram(m_programID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shaders failed to link.");
	}

	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}


void GLSLProgram::AddAttribute(const std::string& name) {
	glBindAttribLocation(m_programID, m_nAttributes++, name.c_str());
}


GLint GLSLProgram::GetUniformLocation(const std::string& name) {
	GLint location = glGetUniformLocation(m_programID, name.c_str());
	if (location == GL_INVALID_INDEX) {
		FatalError("Uniform " + name + " not found in shader.");
	}
	return location;
}


void GLSLProgram::Use() {
	glUseProgram(m_programID);
	for (int i = 0; i < m_nAttributes; ++i) {
		glEnableVertexAttribArray(i);
	}
}


void GLSLProgram::Unuse() {
	glUseProgram(0);
	for (int i = 0; i < m_nAttributes; ++i) {
		glDisableVertexAttribArray(i);
	}
}

}
