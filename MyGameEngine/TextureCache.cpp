#include "TextureCache.h"

#include "ImageLoader.h"

//#include <iostream>

namespace MyGameEngine {

TextureCache::TextureCache() {
}


TextureCache::~TextureCache() {
}


GLTexture TextureCache::GetTexture(const std::string& path) {

	auto it = m_textureMap.find(path);

	if (it == m_textureMap.end()) {
		GLTexture newTexture = ImageLoader::LoadPNG(path);
		m_textureMap.emplace(path, newTexture);
		//std::cout << "Loaded new texture, ID is " << newTexture.id << std::endl;
		return newTexture;
	}
	else {
		//std::cout << "Loaded texture from cache, ID is " << it->second.id << std::endl;
		return it->second;
	}

}

}
