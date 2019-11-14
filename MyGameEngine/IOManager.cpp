#include "IOManager.h"
#include "Errors.h"

#include <fstream>

bool IOManager::ReadFile(const std::string& path, std::vector<unsigned char>& buffer) {

	std::ifstream file;
	file.open(path, std::ios::binary);
	if (file.fail()) {
		FatalError("Failed to open " + path);
		return false;
	}

	file.seekg(0, std::ios::end);
	int filesize = file.tellg();
	file.seekg(0, std::ios::beg);
	filesize -= file.tellg();
	buffer.resize(filesize);

	file.read((char*)&(buffer[0]), filesize);

	file.close();
	return true;
}

