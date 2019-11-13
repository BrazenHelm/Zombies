#pragma once

#include "GLTexture.h"

#include <string>

class ImageLoader {

public:
	static GLTexture LoadPNG(const std::string& path);
};

