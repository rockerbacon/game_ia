#include "animal.h"

/*DEFAULTS*/
SDL_Surface *lab309::defaultPreyTexture = NULL;
float lab309::defaultPreySize = 1.0f;
SDL_Surface *lab309::defaultPredatorTexture = NULL;
float lab309::defaultPredatorSize = 1.0f;

/*ANIMAL*/
/*CONSTRUCTORS*/
lab309::Animal::Animal (std::string species, SDL_Surface *texture, int rectWidth, int rectHeight, float size, unsigned int birthDate, unsigned int lifetime, unsigned int reproductionTime) : Sprite(texture, rectWidth, rectHeight, size) {
	this->species = species;
	this->birthDate = birthDate;
	this->lastReproduction = birthDate;
	this->lifetime = lifetime;
	this->reproductionTime = reproductionTime;
}

/*METHODS*/
void lab309::Animal::setBirthDate (unsigned int birthDate) {
	this->birthDate = birthDate;
	this->lastReproduction = birthDate;
}

bool lab309::Animal::canReproduce (unsigned int time) const {
	return time - this->lastReproduction > this->reproductionTime;
}

bool lab309::Animal::isOld (unsigned int time) const {
	return time - this->birthDate > this->lifetime;
}

void lab309::Animal::reproduce (unsigned int time) {
	this->lastReproduction = time;
}

lab309::Animal* lab309::newPrey (void) {
	return new Animal (NAME_PREY, defaultPreyTexture, defaultPreyTexture->w, defaultPreyTexture->h, defaultPreySize, 0, LIFETIME_PREY, REPRODUCTIONTIME_PREY);
}

lab309::Animal* lab309::newPredator (void) {
	return new Animal (NAME_PREDATOR, defaultPredatorTexture, defaultPredatorTexture->w, defaultPredatorTexture->h, defaultPredatorSize, 0, LIFETIME_PREDATOR, REPRODUCTIONTIME_PREDATOR);
}
