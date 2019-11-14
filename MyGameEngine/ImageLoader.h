#pragma once

#include "GLTexture.h"

#include <string>

namespace MyGameEngine {

class ImageLoader
{
public:
	static GLTexture LoadPNG(const std::string& path);
};

}
