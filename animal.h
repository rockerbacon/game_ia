#ifndef LAB309_ANIMAL_H
#define LAB309_ANIMAL_H

#include <SDL2/SDL.h>
#include "sprite.h"
#include <string>

#define NAME_PREY "fish"
#define NAME_PREDATOR "shark"

#define REPRODUCTIONTIME_PREY 4
#define REPRODUCTIONTIME_PREDATOR 4

#define LIFETIME_PREY 10
#define LIFETIME_PREDATOR 10

namespace lab309 {

	/*DEFAULTS*/
	extern SDL_Surface *defaultPreyTexture;
	extern float defaultPreySize;
	extern SDL_Surface *defaultPredatorTexture;
	extern float defaultPredatorSize;

	class Animal : public Sprite {
		private:
			std::string species;
			unsigned int birthDate;
			unsigned int lastReproduction;
			unsigned int lifetime;
			unsigned int reproductionTime;
			
		public:
			
			/*CONSTRUCTORS*/
			Animal (std::string species, SDL_Surface *texture, int rectWidth, int rectHeight, float size, unsigned int birthDate, unsigned int lifetime, unsigned int reproductionTime);
			
			/*METHODS*/
			void setBirthDate (unsigned int birthDate);
			bool canReproduce (unsigned int time) const;
			bool isOld (unsigned int time) const;
			void reproduce (unsigned int time);
	};
	
	Animal* newPrey (void);
	Animal* newPredator (void);
	
};


#endif
