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

	/*��ȡ����*/
	sf::Font& GetFont(string const& filename);

	/*��ȡ����*/
	sf::Texture& GetTexture(string const& filename);

	/*��������⻬����*/
	void SetTextureSmooth(string const& filename, bool BeSmooth);

	/*��ȡʵ��*/
	static AssetManager* getInstance();

private:

	AssetManager();

	static AssetManager* sInstance;

	std::map<std::string, sf::Texture> m_Textures;

	std::map<string, sf::Font>m_Fonts;
};

//font filenames
#define FONT_MSYH "source/msyh_boot.ttf" // ΢���ź�
