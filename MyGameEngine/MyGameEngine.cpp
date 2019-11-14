#include "MyGameEngine.h"

#include <GL/glew.h>
#include <SDL/SDL.h>

namespace MyGameEngine {

int Init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return 0;
}

}