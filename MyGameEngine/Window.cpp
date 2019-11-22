#include "Window.h"

#include "Errors.h"

namespace MyGameEngine {

Window::Window() {
}


Window::~Window() {
}


int Window::Create(const std::string& name, int width, int height, unsigned int flags) {

	Uint32 sdlWindowFlags = SDL_WINDOW_OPENGL;

	if (flags & HIDDEN)		{ sdlWindowFlags |= SDL_WINDOW_HIDDEN; }
	if (flags & FULLSCREEN) { sdlWindowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP; }
	if (flags & BORDERLESS) { sdlWindowFlags |= SDL_WINDOW_BORDERLESS; }

	m_pWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdlWindowFlags);
	if (m_pWindow == nullptr) { FatalError("SDL Window could not be created."); }

	SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);
	if (glContext == nullptr) { FatalError("SDL_GL Context could not be created."); }

	GLenum error = glewInit();
	if (error != GLEW_OK) { FatalError("GLEW could not be initialised."); }

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::printf("**  OpenGL Version : %s  **\n", glGetString(GL_VERSION));

	//	SDL_GL_SetSwapInterval(1);		// VSYNC

	return 0;
}


void Window::Swap() {
	SDL_GL_SwapWindow(m_pWindow);
}

}
