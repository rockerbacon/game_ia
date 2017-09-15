#include "animal.h"
#include <iostream>

/*DEFAULTS*/
SDL_Surface *lab309::defaultPreyTexture = NULL;
float lab309::defaultPreySize = 1.0f;
SDL_Surface *lab309::defaultPredatorTexture = NULL;
float lab309::defaultPredatorSize = 1.0f;

/*ANIMAL*/
/*CONSTRUCTORS*/
lab309::Animal::Animal (std::string species, SDL_Surface *texture, int rectWidth, int rectHeight, float size, double birthDate, double lifetime, double reproductionTime, float speed, float fieldOfView) : Sprite(texture, rectWidth, rectHeight, size) {
	this->species = species;
	this->birthDate = birthDate;
	this->lastReproduction = birthDate;
	this->lifetime = lifetime;
	this->reproductionTime = reproductionTime;
	this->speed = speed;
	this->state = STATE_IDLE;
	this->fieldOfView = fieldOfView;
}

/*METHODS*/
int lab309::Animal::getState (void) const {
	return this->state;
}

void lab309::Animal::setState (int state) {
	this->state = state;
}

float lab309::Animal::getFieldOfView (void) const {
	return this->fieldOfView;
}

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

void lab309::Animal::move (const Vector<float> &direction, double timeDelta) {
	this->translate(this->speed*timeDelta*direction);
	//std::cout << direction << std::endl;	//debug
	//std::cout << this->speed*timeDelta << std::endl;	//debug
}

bool lab309::Animal::sees (const Vector<float> &point) const {
	return manhattanDistance(this->getCenter(), point) < this->fieldOfView;
}

lab309::Animal* lab309::newPrey (void) {
	return new Animal (NAME_PREY, defaultPreyTexture, defaultPreyTexture->w, defaultPreyTexture->h, defaultPreySize, 0, LIFETIME_PREY, REPRODUCTIONTIME_PREY, SPEED_PREY, FOV_PREY);
}

lab309::Animal* lab309::newPredator (void) {
	return new Animal (NAME_PREDATOR, defaultPredatorTexture, defaultPredatorTexture->w, defaultPredatorTexture->h, defaultPredatorSize, 0, LIFETIME_PREDATOR, REPRODUCTIONTIME_PREDATOR, SPEED_PREDATOR, FOV_PREDATOR);
}
