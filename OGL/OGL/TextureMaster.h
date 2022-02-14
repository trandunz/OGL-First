#pragma once

#ifndef TEXTURE_MASTER_H
#define TEXTURE_MASTER_H
#include "Includes.h"
#include "Texture.h"

namespace Harmony
{
	class TextureMaster
	{
	public:
		~TextureMaster()
		{
			for (auto& item : m_Textures)
			{
				delete item;
				item = nullptr;
			}
			m_Textures.erase(std::remove(m_Textures.begin(), m_Textures.end(), nullptr), m_Textures.end());
			m_TextureIDs.clear();
		}
		void LoadTexture(std::string _path)
		{
			m_TextureIDs.push_back(m_Textures.size());
			m_Textures.push_back(new Texture(_path.c_str(), m_Textures.size(), GL_RGB));
		}
		void LoadNormal(std::string _path)
		{
			m_TextureIDs.push_back(m_Textures.size());
			m_Textures.push_back(new Texture(_path.c_str(), m_Textures.size(), GL_RGB));
		}
		void LoadSpecular(std::string _path)
		{
			m_TextureIDs.push_back(m_Textures.size());
			m_Textures.push_back(new Texture(_path.c_str(), m_Textures.size(), GL_RED));
		}


		std::vector<Texture*> m_Textures;
		std::vector<int> m_TextureIDs;
	};
}
#endif


