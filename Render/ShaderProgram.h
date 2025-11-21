#pragma once
#include <string>

#include "../source/GLinclude.h"
#include "glm/ext/matrix_float4x4.hpp"

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(std::string& vertexShader, std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const {
			return mIsCompiled;
		}
		void use() const;
		void setInt(const std::string& name,const GLint value);
		void setMatrix4(const std::string& name,const glm::mat4 matrix);

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
	private:
		bool CreateShader(std::string& source,GLenum shaderType,GLuint& shaderID);
		bool mIsCompiled = false;
		GLuint mID;
	};
}
