#include "ai.h"
#include "random.h"

/*NAVMESH*/
/*CONSTRUCTORS*/
lab309::Navmesh::Navmesh (int windowWidth, int windowHeight, size_t width, size_t height) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->matrix = Matrix<List<Sprite*>::Iterator>(height, width);
}

/*GETTERS*/
size_t lab309::Navmesh::getWidth (void) const {
	return this->matrix.getColums();
}

size_t lab309::Navmesh::getHeight (void) const {
	return this->matrix.getLines();
}

/*METHODS*/
lab309::Coordinate lab309::Navmesh::roundToWindow (Coordinate coordinate) {
	return {	coordinate.x - coordinate.x % (this->windowWidth/(int)this->matrix.getColums()),
				coordinate.y - coordinate.y % (this->windowHeight/(int)this->matrix.getLines()) };
}

void lab309::Navmesh::clear (void) {
	size_t i, j;
	for (i = 0; i < this->matrix.getLines(); i++) {
		for (j = 0; j < this->matrix.getLines(); j++) {
			this->matrix[i][j] = List<Sprite*>::Iterator();
		}
	}
}

void lab309::Navmesh::add (const lab309::List<Sprite*> &list) {
	List<Sprite*>::Iterator i;
	Coordinate c;
	
	for (i = list.getBeginning(); !i.end(); i++) {
		//determinar posicao x, y do sprite na matriz da malha
		c = i.getData()->getCenter();
		c.x = c.x / (this->windowWidth/this->matrix.getColums());
		c.y = c.y / (this->windowHeight/this->matrix.getLines());
		
		this->matrix[c.x][c.y] = i;
	}
}

/*WORLDMODEL*/
/*CONSTRUCTORS*/
lab309::WorldModel::WorldModel (void) {
	this->date = 0;
}

lab309::WorldModel::~WorldModel (void) {
	lab309::List<Sprite*>::Iterator i;
	
	for (i = this->fish.getBeginning(); !i.end(); i++) {
		delete(i.getData());
	}
	for (i = this->shark.getBeginning(); !i.end(); i++) {
		delete(i.getData());
	}
}

/*GETTERS*/
unsigned int lab309::WorldModel::getDate (void) const {
	return this->date;
}

const lab309::List<lab309::Sprite*>& lab309::WorldModel::referenceFishList (void) const {
	return this->fish;
}

const lab309::List<lab309::Sprite*>& lab309::WorldModel::referenceSharkList (void) const {
	return this->shark;
}

/*METHODS*/
void lab309::WorldModel::addFish (Fish *fish, const Coordinate &pos) {
	fish->setPos(pos);
	fish->setBirthDate(this->date);
	this->fish.add(0, fish);
}

void lab309::WorldModel::addShark (Shark *shark, const Coordinate &pos) {
	shark->setPos(pos);
	shark->setBirthDate(this->date);
	this->shark.add(0, shark);
}

void lab309::WorldModel::timePasses (void) {
	this->date++;
}

void lab309::WorldModel::elderDie (void) {
	lab309::List<Sprite*>::Iterator i;
	Fish *fish;
	Shark *shark;
	
	i = this->fish.getBeginning();
	while (!i.end()) {
		fish = (Fish*)i.getData();
		if (fish->isOld(this->date)) {
			delete(fish);
			this->fish.remove(i);
		} else {
			i++;
		}
	}
	
	i = this->shark.getBeginning();
	while (!i.end()) {
		shark = (Shark*)i.getData();
		if (shark->isOld(this->date)) {
			delete(shark);
			this->shark.remove(i);
		} else {
			i++;
		}
	}
}

void lab309::WorldModel::fishReproduce (void) {
	lab309::List<Sprite*>::Iterator i, j;
	Fish *a, *b;
	
	for (i = this->fish.getBeginning(); !i.end(); i++) {
		j = i.next();
		a = (Fish*)i.getData();
		while (a->canReproduce(this->date) && !j.end()) {
			b = (Fish*)j.getData();
			//colisao peixe-peixe
			if (collision(*a, *b)) {
				//printf("fish-fish collision\n");	//debug
				Coordinate c;
				c.x = randomBetween(a->getXPos()-a->getDisplayWidth(), a->getXPos()+a->getDisplayWidth()),
				c.y = randomBetween(a->getYPos()-a->getDisplayHeight(), a->getYPos()+a->getDisplayHeight());
				this->addFish(new Fish(), c);
				a->reproduce(this->date);
				b->reproduce(this->date);
 			}
 				
 			j++;
		}
	}

}

void lab309::WorldModel::sharkEat (void) {
	lab309::List<Sprite*>::Iterator i, j;
	
	for (i = this->shark.getBeginning(); !i.end(); i++) {
		j = this->fish.getBeginning();
		while (!j.end()) {
			//colisao tubarao peixe
			if (collision(*i.getData(), *j.getData())) {
				delete(j.getData());
				this->fish.remove(j);
			} else {
				j++;
			}
		}
	}
}
