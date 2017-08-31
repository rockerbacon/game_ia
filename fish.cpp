#include "fish.h"
#include "random.h"

/*CONSTRUCTORS*/
lab309::Fish::Fish (SDL_Surface *texture, int rectWidth, int rectHeight, float size, unsigned int birthDate) : Sprite(texture, rectWidth, rectHeight, size) {
	this->birthDate = birthDate;
	this->lastReproduction = birthDate;
}

/*METHODS*/
bool lab309::Fish::canReproduce (unsigned int time) const {
	return time - this->lastReproduction > FISH_REPRODUCTIONTIME;
}

bool lab309::Fish::isOld (unsigned int time) const {
	return time - this->birthDate > FISH_LIFETIME;
}

void lab309::Fish::reproduce (unsigned int time) {
	this->lastReproduction = time;
}
