#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<map>
#include<cassert>
using namespace std;
/*
Asset Manager
[Singleton pattern] Use AssetManager::getInstance()->GetAsset(filename)
to get asset.
 */
class AssetManager
{
public:

	~AssetManager() {}

	/*获取字体*/
	sf::Font& GetFont(string const& filename);

	/*获取纹理*/
	sf::Texture& GetTexture(string const& filename);

	/*设置纹理光滑属性*/
	void SetTextureSmooth(string const& filename, bool BeSmooth);

	/*获取实例*/
	static AssetManager* getInstance();

private:

	AssetManager();

	static AssetManager* sInstance;

	std::map<std::string, sf::Texture> m_Textures;

	std::map<string, sf::Font>m_Fonts;
};

//font filenames
#define FONT_MSYH "source/msyh_boot.ttf" // 微软雅黑
