#include "shark.h"

/*CONSTRUCTORS*/
lab309::Shark::Shark (SDL_Surface *texture, int rectWidth, int rectHeight, float size, unsigned int birthDate) : Sprite(texture, rectWidth, rectHeight, size) {
	this->birthDate = birthDate;
}

/*METHODS*/
void lab309::Shark::setBirthDate (unsigned int birthDate) {
	this->birthDate = birthDate;
}

bool lab309::Shark::isOld (unsigned int time) const {
	return time-this->birthDate > SHARK_LIFETIME;
}
