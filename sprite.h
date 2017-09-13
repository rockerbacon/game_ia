#ifndef LAB309SDL_SPRITE_H
#define LAB309SDL_SPRITE_H

#include <SDL2/SDL.h>
#include "vertex.h"
#include "window.h"

#define COLLISION_LEFT 0xd	//1101
#define COLLISION_RIGHT 0xe	//1110
#define COLLISION_UP 0x7	//0111
#define COLLISION_DOWN 0xb	//1011

namespace lab309 {
	class Sprite {
		friend class Window;
		friend int collision (const Sprite &a, const Sprite &b);
		protected:
			/*ATTRIBUTES*/
			Vector_2d pos;
			SDL_Surface *texture;
			SDL_Rect rect;
			SDL_Rect displayRect;
			
		public:
			/*CONSTRUCTORS*/
			Sprite (SDL_Surface *texture, int rectWidth, int rectHeight, float size);
			
			/*GETTERS*/
			Vector_2d getSpritePos (void) const;
			Vector_2d getPos (void) const;
			int getXPos (void) const;
			int getYPos (void) const;
			Vector_2d getCenter (void) const;
			int getDisplayWidth (void) const;
			int getDisplayHeight (void) const;
			
			/*SETTERS*/
			void setSpritePos (const Vector_2d &pos);
			void setPos (const Vector_2d &pos);
			
			/*METHODS*/
			void translate (const Vector_2d &offset);
			void blitTo (const Window &window);
	};
	
	int collision (const Sprite &a, const Sprite &b);
};

#endif
