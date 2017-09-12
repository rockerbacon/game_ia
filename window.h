#ifndef LAB309_WINDOW_H
#define LAB309_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace lab309 {
	class Sprite;
	
	class Window {
		friend class Sprite;
		private:
			/*ATTRIBUTES*/
			SDL_Window *window;
			SDL_Surface *surface;
			
		public:
			/*CONSTRUCTORS*/
			Window (const char *title, unsigned int width, unsigned int hight);
			~Window (void);
			
			/*GETTERS*/
			int getWidth (void) const;
			int getHeight (void) const;
			
			/*METHODS*/
			SDL_Surface* loadTexture (const char *imgPath);
			void update (void);
			
	};
};

#endif
