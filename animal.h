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

#define REPRODUCTIONTIME_PREY 4
#define REPRODUCTIONTIME_PREDATOR 1

#define LIFETIME_PREY 10
#define LIFETIME_PREDATOR 15

#define SPEED_PREY 22
#define SPEED_PREDATOR 28

#define FOV_PREY 300
#define FOV_PREDATOR 300

#define STATE_IDLE 0
#define STATE_CHASING 1
#define STATE_FLEEING 2

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
			int state;
			float fieldOfView;
			
		public:
			
			/*CONSTRUCTORS*/
			Animal (std::string species, SDL_Surface *texture, int rectWidth, int rectHeight, float size, double birthDate, double lifetime, double reproductionTime, float speed, float fieldOfView);
			
			/*METHODS*/
			int getState (void) const;
			void setState (int state);
			float getFieldOfView (void) const;
			void setBirthDate (double birthDate);
			bool canReproduce (double time) const;
			bool isOld (double time) const;
			void reproduce (double time);
			void move (const Vector<float> &direction, double timeDelta);
			bool sees (const Vector<float> &point) const;
	};
	
	Animal* newPrey (void);
	Animal* newPredator (void);
	
};


#endif
