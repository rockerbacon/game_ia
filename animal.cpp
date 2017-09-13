#include "animal.h"
#include <iostream>

/*DEFAULTS*/
SDL_Surface *lab309::defaultPreyTexture = NULL;
float lab309::defaultPreySize = 1.0f;
SDL_Surface *lab309::defaultPredatorTexture = NULL;
float lab309::defaultPredatorSize = 1.0f;

/*ANIMAL*/
/*CONSTRUCTORS*/
lab309::Animal::Animal (std::string species, SDL_Surface *texture, int rectWidth, int rectHeight, float size, double birthDate, double lifetime, double reproductionTime, float speed) : Sprite(texture, rectWidth, rectHeight, size) {
	this->species = species;
	this->birthDate = birthDate;
	this->lastReproduction = birthDate;
	this->lifetime = lifetime;
	this->reproductionTime = reproductionTime;
	this->speed = speed;
}

/*METHODS*/
void lab309::Animal::setBirthDate (double birthDate) {
	this->birthDate = birthDate;
	this->lastReproduction = birthDate;
}

bool lab309::Animal::canReproduce (double time) const {
	return time - this->lastReproduction > this->reproductionTime;
}

bool lab309::Animal::isOld (double time) const {
	return time - this->birthDate > this->lifetime;
}

void lab309::Animal::reproduce (double time) {
	this->lastReproduction = time;
}

void lab309::Animal::move (const Vector_2d &direction, double timeDelta) {
	this->translate(this->speed*timeDelta*direction);
	//std::cout << direction << std::endl;	//debug
	//std::cout << this->speed*timeDelta << std::endl;	//debug
}

lab309::Animal* lab309::newPrey (void) {
	return new Animal (NAME_PREY, defaultPreyTexture, defaultPreyTexture->w, defaultPreyTexture->h, defaultPreySize, 0, LIFETIME_PREY, REPRODUCTIONTIME_PREY, SPEED_PREY);
}

lab309::Animal* lab309::newPredator (void) {
	return new Animal (NAME_PREDATOR, defaultPredatorTexture, defaultPredatorTexture->w, defaultPredatorTexture->h, defaultPredatorSize, 0, LIFETIME_PREDATOR, REPRODUCTIONTIME_PREDATOR, SPEED_PREDATOR);
}
