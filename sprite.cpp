#include "sprite.h"

/*CONSTRUCTORS*/
lab309::Sprite::Sprite (SDL_Surface *texture, int rectWidth, int rectHeight, float size) {
	this->texture = texture;
	this->rect = {0, 0, rectWidth, rectHeight};
	this->displayRect = {0, 0, (int)(rectWidth*size), (int)(rectHeight*size)};
}

/*GETTERS*/
lab309::Coordinate lab309::Sprite::getSpritePos (void) const {
	return { this->rect.x/this->rect.w, this->rect.y/this->rect.h };
}

lab309::Coordinate lab309::Sprite::getPos (void) const {
	return { this->displayRect.x, this->displayRect.y };
}

int lab309::Sprite::getXPos (void) const {
	return this->displayRect.x;
}

int lab309::Sprite::getYPos (void) const {
	return this->displayRect.y;
}

lab309::Coordinate lab309::Sprite::getCenter (void) const {
	return { this->displayRect.x+this->displayRect.w/2, this->displayRect.y+this->displayRect.h/2 };
}

int lab309::Sprite::getDisplayWidth (void) const {
	return this->displayRect.w;
}

int lab309::Sprite::getDisplayHeight (void) const {
	return this->displayRect.h;
}

/*SETTERS*/
void lab309::Sprite::setSpritePos (const lab309::Coordinate &pos) {
	this->rect.x = pos.x*this->rect.w;
	this->rect.y = pos.y*this->rect.h;
}

void lab309::Sprite::setPos (const lab309::Coordinate &pos) {
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

void lab309::Sprite::blitTo (const lab309::Window &window) {
	SDL_BlitScaled(this->texture, &this->rect, window.surface, &this->displayRect);
}

int lab309::collision (const lab309::Sprite &a, const lab309::Sprite &b) {
	int colx, coly;
	int	bxmax = b.displayRect.x+b.displayRect.w,
		bymax = b.displayRect.y+b.displayRect.h,
		axmax = a.displayRect.x+a.displayRect.w,
		aymax = a.displayRect.y+a.displayRect.h;
		
	colx = bxmax > a.displayRect.x && b.displayRect.x < axmax;
	coly = bymax > a.displayRect.y && b.displayRect.y < aymax;
	return colx && coly;
}
