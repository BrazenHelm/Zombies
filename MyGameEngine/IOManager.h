#pragma once

#include <string>
#include <vector>

namespace MyGameEngine {

class IOManager
{
public:
	static bool ReadFile(const std::string& path, std::vector<unsigned char>& buffer);
};

}
