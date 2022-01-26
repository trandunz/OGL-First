#pragma once
#include "NumptyBehavior.h"
#include "Texture.h"
class TextureMaster : public NumptyBehavior
{
public:
	~TextureMaster()
	{
		for (auto& item : m_Textures)
		{
			if (item)
			{
				delete item;
			}
			item = nullptr;
		}
		m_Textures.erase(std::remove(m_Textures.begin(), m_Textures.end(), nullptr), m_Textures.end());
		m_TextureIDs.clear();
	}
	void LoadTexture(std::string _path)
	{
		m_TextureIDs.push_back(m_Textures.size());
		std::string extension;
		extension = _path.substr(_path.find(".") + 1);
		if (extension == "jpg")
			m_Textures.push_back(new Texture(_path.c_str(), GL_TEXTURE_2D, m_Textures.size(), GL_RGB, GL_UNSIGNED_BYTE));
		else
			m_Textures.push_back(new Texture(_path.c_str(), GL_TEXTURE_2D, m_Textures.size(), GL_RGBA, GL_UNSIGNED_BYTE));
	}
	void LoadNormal(std::string _path)
	{
		m_TextureIDs.push_back(m_Textures.size());
		m_Textures.push_back(new Texture(_path.c_str(), GL_TEXTURE_2D, m_Textures.size(), GL_RGBA, GL_UNSIGNED_BYTE));
	}
	void LoadSpecular(std::string _path)
	{
		m_TextureIDs.push_back(m_Textures.size());
		m_Textures.push_back(new Texture(_path.c_str(), GL_TEXTURE_2D, m_Textures.size(), GL_RED, GL_UNSIGNED_BYTE));
	}
	

	std::vector<Texture*> m_Textures;
	std::vector<int> m_TextureIDs;
};

