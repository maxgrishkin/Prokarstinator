#include "ResourceManager.h"
#include <fstream>
#include "../Render/ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
   #include "stb_image.h"

ResourceManager::ResourceManager(const std::string &executablePath) {
	#ifdef _WIN32
		#define found_symbol "\\"
	#elif __linux__
		#define found_symbol "/"
	#else
		#define found_symbol "/\\"
	#endif
	size_t found = executablePath.find_last_of(found_symbol);
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

	std::shared_ptr<Renderer::ShaderProgram>& newShader = mShaderPrograms.emplace(shaderName,std::make_shared<Renderer::ShaderProgram>(vertexString,fragmentString)).first->second;
	if (!newShader->isCompiled()) {
		throw std::runtime_error(std::string("Can't load shader program:\nVertex:") + vertexPath + "\nFragment:" + fragmentPath + "\n");
	}
	return newShader;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string &shaderName) {
	ShaderProgramsMap::const_iterator it = mShaderPrograms.find(shaderName);
	if (it == mShaderPrograms.end()) {
		throw std::runtime_error("Can't find the shader program: " + shaderName + "\n");
	}
	return it->second;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const std::string &textureName, const std::string &texturePath) {
	int channels = 0;
	int width = 0;
	int height = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels =  stbi_load(std::string(mPath + "/" + texturePath).c_str(),&width,&height,&channels, 0);

	if (!pixels) {
		throw std::runtime_error("Can't load image: " + texturePath + "\n");
	}

	std::shared_ptr<Renderer::Texture2D> newTexture = mTextures.emplace(textureName,std::make_shared<Renderer::Texture2D>(width,height,pixels,channels,GL_NEAREST,GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newTexture;
}
std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string &textureName, const std::string &texturePath) {
	TexturesMap::const_iterator it = mTextures.find(textureName);
	if (it == mTextures.end()) {
		throw std::runtime_error("Can't find the texture: " + textureName + "\n");
	}
	return it->second;
}