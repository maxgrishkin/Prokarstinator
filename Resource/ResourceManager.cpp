#include "ResourceManager.h"

#include <fstream>

#include "../Render/ShaderProgram.h"

ResourceManager::ResourceManager(const std::string &executablePath) {
	size_t found = executablePath.find_last_of("/\\");
	mPath = executablePath.substr(0,found);
}

std::string ResourceManager::getFileString(const std::string &Path) const {
	std::ifstream fis(Path, std::ios::binary);
	if (!fis.good()) {
		throw std::runtime_error("Failed to open file: " + Path);
	}
	std::string code((std::istreambuf_iterator<char>(fis)), std::istreambuf_iterator<char>());
	return code;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShader(const std::string &shaderName, const std::string &vertexPath, const std::string &fragmentPath) {
	std::string vertexString = getFileString(vertexPath);
	std::string fragmentString = getFileString(fragmentPath);

	std::shared_ptr<Renderer::ShaderProgram>& newShader = mShaderProgram.emplace(shaderName,std::make_shared<Renderer::ShaderProgram>(vertexString,fragmentString)).first->second;
	if (!newShader->isCompiled()) {
		throw std::runtime_error(std::string("Can't load shader program:\nVertex:") + vertexPath + "\nFragment:" + fragmentPath + "\n");
	}
	return newShader;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string &shaderName) {
	ShaderProgramsMap::const_iterator it = mShaderProgram.find(shaderName);
	if (it == mShaderProgram.end()) {
		throw std::runtime_error("Can't find the shader program: " + shaderName + "\n");
	}
	return it->second;
}