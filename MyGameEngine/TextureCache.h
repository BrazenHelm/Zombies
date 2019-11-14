#pragma once

#include "GLTexture.h"

#include <map>
#include <string>

namespace MyGameEngine {

class TextureCache
{
private:
	std::map<std::string, GLTexture> m_textureMap;

public:
	TextureCache();
	~TextureCache();

	GLTexture GetTexture(const std::string& path);
};

}
