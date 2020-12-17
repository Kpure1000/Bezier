#include"AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	/*assert(sInstance == nullptr);
	sInstance = this;*/
}

AssetManager* AssetManager::getInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AssetManager();
	}
	return sInstance;
}

sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
	auto& texMap = sInstance->m_Textures;

	auto pairFound = texMap.find(filename);

	if (pairFound != texMap.end())
	{
		return pairFound->second; 
	}
	else
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

void AssetManager::SetTextureSmooth(string const& filename, bool BeSmooth)
{
	for (auto it = sInstance->m_Textures.begin(); 
		it != sInstance->m_Textures.end(); it++)
	{
		if (it->first == filename) 
		{
			it->second.setSmooth(BeSmooth); 
			break;
		}
	}
}

sf::Font& AssetManager::GetFont(string const& filename)
{
	auto& fontMap = sInstance->m_Fonts;

	auto pairFound = fontMap.find(filename);

	if (pairFound != fontMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& font = fontMap[filename];
		font.loadFromFile(filename);
		return font;
	}
}