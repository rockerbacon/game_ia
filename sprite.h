#ifndef LAB309SDL_SPRITE_H
#define LAB309SDL_SPRITE_H

#include <SDL2/SDL.h>
#include "coordinates.h"
#include "window.h"

namespace lab309 {
	class Sprite {
		friend class Window;
		private:
			/*ATTRIBUTES*/
			SDL_Surface *texture;
			SDL_Rect rect;
			SDL_Rect displayRect;
			
		public:
			/*CONSTRUCTORS*/
			Sprite (SDL_Surface *texture, int rectWidth, int rectHeight, float size);
			
			/*GETTERS*/
			Coordinate getSpritePos (void) const;
			Coordinate getPos (void) const;
			
			/*SETTERS*/
			void setSpritePos (const Coordinate &pos);
			void setPos (const Coordinate &pos);
			
			/*METHODS*/
			void moveX (int offset);
			void moveY (int offset);
			void blitTo (const Window &window);
	};
};

#endif
