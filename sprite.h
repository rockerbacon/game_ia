#ifndef LAB309SDL_SPRITE_H
#define LAB309SDL_SPRITE_H

#include <SDL2/SDL.h>
#include "coordinates.h"
#include "window.h"

#define	FORMAT_BMP 1

namespace lab309 {
	public class Sprite {
		friend class Window;
		private:
			/*ATTRIBUTES*/
			SDL_Surface *texture;
			SDL_Rect rect;
			SDL_Rect displayRect;
			
		public:
			/*CONSTRUCTORS*/
			Sprite (SDL_Surface *texture, int rectWidth, int rectHeight, float size);
			~Sprite (void);
			
			/*GETTERS*/
			Coordinate getSpritePos (void) const;
			Coordinate getPos (void) const;
			
			/*SETTERS*/
			void setSpritePos (const Coordinate &pos);
			void setPos (const Coordinate &pos);
			
			/*METHODS*/
			void moveX (int offset);
			void moveY (int offset);
	};
};

#endif
