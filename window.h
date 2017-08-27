#ifndef LAB309_WINDOW_H
#define LAB309_WINDOW_H

#include <SDL2/SDL.h>

namespace lab309 {
	public class Sprite;
	
	public class Window {
		friend class Sprite;
		private:
			/*ATTRIBUTES*/
			SDL_Window *window;
			SDL_Surface *surface;
			
		public:
			/*CONSTRUCTORS*/
			Window (const char *title, unsigned int width, unsigned int hight);
			~Window (void);
			
			/*METHODS*/
			SDL_Surface* loadTexture (const char *imgPath, int format);
			void blit (const lab309::Sprite &sprite);
			void update (void);
	};
};

#endif
