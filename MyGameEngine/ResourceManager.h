#pragma once

#include "TextureCache.h"

class ResourceManager {
private:
	static TextureCache m_textureCache;

public:

	static GLTexture GetTexture(const std::string& path);

};

