#pragma once
#include <map>
#include <memory>
#include <string>

#include "../Render/ShaderProgram.h"
#include "../Render/Sprite.h"
#include "../Render/Texture2D.h"

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
	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName,const std::string& texturePath);
	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);
	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight);
	std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

private:
	std::string getFileString(const std::string& Path) const;

	typedef std::map<const std::string,std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap mShaderPrograms;

	typedef std::map<const std::string,std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap mTextures;

	typedef std::map<const std::string,std::shared_ptr<Renderer::Sprite>> SpritesMap;
	SpritesMap mSprites;

	std::string mPath;
};
