#pragma once
#include <string>

#include "../GLinclude.h"

namespace Rendarer {
	class ShaderProgram {
	public:
		ShaderProgram(std::string& vertexShader, std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const {
			return mIsCompiled;
		}
		void use() const;

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
