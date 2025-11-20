#pragma once
#include <map>
#include <memory>
#include <string>

#include "../Render/ShaderProgram.h"

class ResourceManager {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(const ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string& shaderName);

private:
	std::string getFileString(const std::string& Path) const;

	typedef std::map<const std::string,std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap mShaderProgram;

	std::string mPath;
};
