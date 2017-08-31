#ifndef LAB309SDL_SPRITE_H
#define LAB309SDL_SPRITE_H

#include <SDL2/SDL.h>
#include "coordinates.h"
#include "window.h"

#define COLLISION_LEFT 0xd	//1101
#define COLLISION_RIGHT 0xe	//1110
#define COLLISION_UP 0x7	//0111
#define COLLISION_DOWN 0xb	//1011

namespace lab309 {
	class Sprite {
		friend class Window;
		friend int collision (const Sprite &a, const Sprite &b);
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
			Coordinate getCenter (void) const;
			
			/*SETTERS*/
			void setSpritePos (const Coordinate &pos);
			void setPos (const Coordinate &pos);
			
			/*METHODS*/
			void moveX (int offset);
			void moveY (int offset);
			void blitTo (const Window &window);
	};
	
	int collision (const Sprite &a, const Sprite &b);
};

#endif
