#include "MyErrors.h"

#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

namespace MyGameEngine {

void FatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	system("pause");
	SDL_Quit();
	exit(1);
}

}