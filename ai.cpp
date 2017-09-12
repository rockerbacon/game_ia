#include "ai.h"
#include "random.h"

/*WORLDMODEL*/
/*CONSTRUCTORS*/
lab309::WorldModel::WorldModel (const Window &window, size_t navmeshHeight, size_t navmeshWidth) {
	this->date = 0;
	this->window = &window;
	this->navmesh = Matrix<struct Cell>(navmeshHeight, navmeshWidth);
}

lab309::WorldModel::~WorldModel (void) {
	lab309::List<Animal*>::Iterator i;
	
	for (i = this->prey.getBeginning(); !i.end(); i++) {
		delete(i.getData());
	}
	for (i = this->predator.getBeginning(); !i.end(); i++) {
		delete(i.getData());
	}
}

/*GETTERS*/
unsigned int lab309::WorldModel::getDate (void) const {
	return this->date;
}

const lab309::List<lab309::Animal*>& lab309::WorldModel::referencePreyList (void) const {
	return this->prey;
}

const lab309::List<lab309::Animal*>& lab309::WorldModel::referencePredatorList (void) const {
	return this->predator;
}

/*METHODS*/
void lab309::WorldModel::mapToNavmesh (List<Animal*>::Iterator iterator) {
	Coordinate c = iterator.getData()->getCenter();
	c.x = c.x / (this->window->getWidth()/this->navmesh.getColums());
	c.y = c.y / (this->window->getHeight()/this->navmesh.getLines());
	
	this->navmesh[c.y][c.x].animal = iterator;
}

void lab309::WorldModel::addPrey (Animal *prey, const Coordinate &pos) {
	prey->setPos(pos);
	prey->setBirthDate(this->date);
	this->prey.add(this->prey.getLength(), prey);
	this->mapToNavmesh(this->prey.getEnd());
}

void lab309::WorldModel::addPredator (Animal *predator, const Coordinate &pos) {
	predator->setPos(pos);
	predator->setBirthDate(this->date);
	this->predator.add(this->predator.getLength(), predator);
	this->mapToNavmesh(this->predator.getEnd());
}

void lab309::WorldModel::timePasses (void) {
	this->date++;
}

void lab309::WorldModel::elderDie (void) {
	lab309::List<Animal*>::Iterator i;
	Animal *prey;
	Animal *predator;
	
	i = this->prey.getBeginning();
	while (!i.end()) {
		prey = i.getData();
		if (prey->isOld(this->date)) {
			delete(prey);
			this->prey.remove(i);
		} else {
			i++;
		}
	}
	
	i = this->predator.getBeginning();
	while (!i.end()) {
		predator = i.getData();
		if (predator->isOld(this->date)) {
			delete(predator);
			this->predator.remove(i);
		} else {
			i++;
		}
	}
}

void lab309::WorldModel::preyReproduce (void) {
	lab309::List<Animal*>::Iterator i, j;
	Animal *a, *b;
	
	for (i = this->prey.getBeginning(); !i.end(); i++) {
		j = i.next();
		a = i.getData();
		while (a->canReproduce(this->date) && !j.end()) {
			b = j.getData();
			//colisao peixe-peixe
			if (collision(*a, *b)) {
				//printf("prey-prey collision\n");	//debug
				Coordinate c;
				c.x = randomBetween(a->getXPos()-a->getDisplayWidth(), a->getXPos()+a->getDisplayWidth()),
				c.y = randomBetween(a->getYPos()-a->getDisplayHeight(), a->getYPos()+a->getDisplayHeight());
				this->addPrey(newPrey(), c);
				a->reproduce(this->date);
				b->reproduce(this->date);
 			}
 				
 			j++;
		}
	}

}

void lab309::WorldModel::predatorEat (void) {
	lab309::List<Animal*>::Iterator i, j;
	
	for (i = this->predator.getBeginning(); !i.end(); i++) {
		j = this->prey.getBeginning();
		while (!j.end()) {
			//colisao tubarao peixe
			if (collision(*i.getData(), *j.getData())) {
				delete(j.getData());
				this->prey.remove(j);
			} else {
				j++;
			}
		}
	}
}
