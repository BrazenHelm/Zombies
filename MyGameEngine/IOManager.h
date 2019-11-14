#pragma once

#include <string>
#include <vector>

class IOManager {
public:
	static bool ReadFile(const std::string& path, std::vector<unsigned char>& buffer);
};

