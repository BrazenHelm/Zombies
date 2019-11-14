#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>

#include <string>

namespace MyGameEngine {

enum WindowFlags {
	HIDDEN = 0x01,
	FULLSCREEN = 0x02,
	BORDERLESS = 0x04
};

class Window
{
private:
	SDL_Window* m_pWindow;
	int			m_width;
	int			m_height;

public:
	Window();
	~Window();

	int Width() { return m_width; }
	int Height() { return m_height; }

	int Create(const std::string& name, int width, int height, unsigned int flags);
	void Swap();
};

}
