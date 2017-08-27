#include "sprite.h"

/*CONSTRUCTORS*/
lab309::Sprite::Sprite (SDL_Surface *texture, int rectWidth, int rectHeight, float size) {
	this->texture = texture;
	this->rect = {0, 0, rectWidth, rectHeight};
	this->displayRect = {0, 0, (int)(rectWidth*size), (int)(rectHeight*size)};
}

lab309::Sprite::~Sprite (void) {
	SDL_FreeSurface(this->texture);
}

/*GETTERS*/
Coordinate lab309::Sprite::getSpritePos (void) const {
	return { this->rect.x/this->rect.w, this->rect.y/this->rect.h };
}

Coordinate lab309::Sprite::getPos (void) const {
	return { this->displayRect.x, this->displayRect.y };
}

/*SETTERS*/
void lab309::Sprite::setSpritePos (const Coordinate &pos) {
	this->rect.x = pos.x*this->rect.w;
	this->rect.y = pos.y*this->rect.h;
}

void lab309::Sprite::setPos (const Coordinate &pos) {
	this->displayRect.x = pos.x;
	this->displayRect.y = pos.y;
}

/*METHODS*/
void lab309::Sprite::moveX (int offset) {
	this->displayRect.x += offset;
}

void lab309::Sprite::moveY (int offset) {
	this->displayRect.y += offset;
}
