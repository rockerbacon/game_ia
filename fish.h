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
			/*CONSTRUCTORS*/
			Fish (SDL_Surface *texture, int rectWidth, int rectHeight, float size, unsigned int birthDate);
			
			/*METHODS*/
			bool canReproduce (unsigned int time) const;
			bool isOld (unsigned int time) const;
			void reproduce (unsigned int time);
	};
};

#endif
