#include "ShaderProgram.h"
#include <iostream>

namespace Renderer {
	ShaderProgram::ShaderProgram(std::string& vertexShader, std::string& fragmentShader) {
		GLuint vertexShaderID;
		if (!CreateShader(vertexShader,GL_VERTEX_SHADER,vertexShaderID)) {
			std::cerr << "VERTEX::SHADER::Compile-time:error" << std::endl;
			return;
		}
		GLuint fragmentShaderID;
		if (!CreateShader(fragmentShader,GL_FRAGMENT_SHADER,fragmentShaderID)) {
			std::cerr << "FRAGMENT::SHADER::Compile-time:error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}
		mID = glCreateProgram();
		glAttachShader(mID,vertexShaderID);
		glAttachShader(mID,fragmentShaderID);
		glLinkProgram(mID);

		GLint success;
		glGetProgramiv(mID,GL_LINK_STATUS,&success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(mID,1024,nullptr,infoLog);
			std::cerr << "ERROR::SHADER::Link-time error:\n" << infoLog << std::endl;
		}
		else {
			mIsCompiled = true;
		}
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	bool ShaderProgram::CreateShader(std::string& source,const GLenum shaderType,GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* sourceCh = source.c_str();
		glShaderSource(shaderID,1,&sourceCh,nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID,GL_COMPILE_STATUS,&success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID,1024,nullptr,infoLog);
			std::cerr << "ERROR::SHADER::Compile-time error:\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}
	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(mID);
	}
	void ShaderProgram::use() const {
		glUseProgram(mID);
	}
	ShaderProgram& ShaderProgram::operator=(ShaderProgram &&shaderProgram) noexcept {
		glDeleteProgram(mID);
		mID = shaderProgram.mID;
		mIsCompiled = shaderProgram.mIsCompiled;

		shaderProgram.mID = 0;
		shaderProgram.mIsCompiled = false;

		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) noexcept {
		mID = shaderProgram.mID;
		mIsCompiled = shaderProgram.mIsCompiled;

		shaderProgram.mID = 0;
		shaderProgram.mIsCompiled = false;
	}
}
