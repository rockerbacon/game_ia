#include "window.h"

lab309::Window::Window (const char *title, unsigned int width, unsigned int hight) {
	this->window = SDL_CreateWindow (title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, hight, SDL_WINDOW_SHOWN);
	this->surface = SDLGetWindowSurface (this->window);
}

lab309::Window::~Window (void) {
	SDL_DestroyWindow(this->window);
}

SDL_Surface* lab309::Window::loadTexture (const char *imgPath, int format) {
	SDL_Surface *loaded;
	SDL_Surface *optimized;
	
	switch (format) {
		case FORMAT_BMP:
			loaded = SDL_LoadBMP(impPath);
		break;
	}
	
	optimized = SDL_ConvertSurface (loaded, this->suface->format, NULL);
	SDL_FreeSurface(loaded);
	
	return optimized;
}

void lab309::Window::blit (const lab309::Sprite &sprite) {
	SDL_BlitScaled(sprite.texture, sprite.rect, this->surface, sprite.displayRect);
}

void lab309::Window::update (void) {
	SDL_UpdateWindowSurface(this->window);
}
