#include "ResourceManager.h"

TextureCache ResourceManager::m_textureCache;

GLTexture ResourceManager::GetTexture(const std::string& path) {
	return m_textureCache.GetTexture(path);
}
