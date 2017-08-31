#ifndef LAB309_FISH_H
#define LAB309_FISH_H

#define FISH_LIFETIME 10
#define FISH_REPRODUCTIONTIME 4

#include "sprite.h"

namespace lab309 {
	class Fish : public Sprite {
		private:
			unsigned int birthDate;
			unsigned int lastReproduction;
			
		public:
			/*DEFAULTS*/
			static SDL_Surface *defaultTexture;
			static float defaultSize;
			
			/*CONSTRUCTORS*/
			Fish (SDL_Surface *texture, int rectWidth, int rectHeight, float size, unsigned int birthDate);
			inline Fish (void) : Fish (defaultTexture, defaultTexture->w, defaultTexture->h, defaultSize, 0) {}
			
			/*METHODS*/
			void setBirthDate (unsigned int birthDate);
			bool canReproduce (unsigned int time) const;
			bool isOld (unsigned int time) const;
			void reproduce (unsigned int time);
	};
};

#endif
