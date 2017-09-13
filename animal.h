/*
 * Unidade de espaco sempre em pixels
 * Unidade de tempo sempre em segundos
*/

#ifndef LAB309_ANIMAL_H
#define LAB309_ANIMAL_H

#include <SDL2/SDL.h>
#include "sprite.h"
#include <string>

#define DIRECTION_UP {0, 1}
#define DIRECTION_LEFT {-1, 0}
#define DIRECTION_RIGHT {1, 0}
#define DIRECTION_DOWN {0, -1}

#define NAME_PREY "fish"
#define NAME_PREDATOR "shark"

#define REPRODUCTIONTIME_PREY 1
#define REPRODUCTIONTIME_PREDATOR 1

#define LIFETIME_PREY 4
#define LIFETIME_PREDATOR 3

#define SPEED_PREY 10
#define SPEED_PREDATOR 10

namespace lab309 {

	/*DEFAULTS*/
	extern SDL_Surface *defaultPreyTexture;
	extern float defaultPreySize;
	extern SDL_Surface *defaultPredatorTexture;
	extern float defaultPredatorSize;

	class Animal : public Sprite {
		private:
			/*GENERAL ATTRIBUTES*/
			std::string species;
			double birthDate;
			double lastReproduction;
			double lifetime;
			double reproductionTime;
			float speed;
			
		public:
			
			/*CONSTRUCTORS*/
			Animal (std::string species, SDL_Surface *texture, int rectWidth, int rectHeight, float size, double birthDate, double lifetime, double reproductionTime, float speed);
			
			/*METHODS*/
			void setBirthDate (double birthDate);
			bool canReproduce (double time) const;
			bool isOld (double time) const;
			void reproduce (double time);
			void move (const Vector_2d &direction, double timeDelta);
	};
	
	Animal* newPrey (void);
	Animal* newPredator (void);
	
};


#endif
