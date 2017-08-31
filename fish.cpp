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

lab309::Fish* lab309::Fish::reproduce (unsigned int time) {
	int bornX = randomBetween(this->displayRect.x-this->displayRect.w, this->displayRect.x+this->displayRect.w);
	int bornY = randomBetween(this->displayRect.y-this->displayRect.h, this->displayRect.y+this->displayRect.h);
	Fish *fish = new Fish(this->texture, this->rect.w, this->rect.h, (float)this->displayRect.w/this->rect.w, time);
	fish->setPos({bornX, bornY});
	this->lastReproduction = time;
	return fish;
}
