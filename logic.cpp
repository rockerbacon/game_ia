#include "logic.h"
#include "random.h"
#include <iostream>
#include <math.h>

/*WORLDMODEL*/
/*CONSTRUCTORS*/
lab309::WorldModel::WorldModel (const Window &window, size_t navmeshHeight, size_t navmeshWidth) {
	this->date = SDL_GetTicks()/1000.0;
	this->window = &window;
	this->navmesh = Matrix<struct Cell>(navmeshHeight, navmeshWidth);
	for (size_t i = 0; i < this->navmesh.getLines(); i++) {
		for (size_t j = 0; j < this->navmesh.getColums(); j++) {
			this->navmesh[i][j] = {List<Animal*>::Iterator(), {0.0f,0.0f}, 0.0f, {0.0f, 0.0f}, 0.0f};
		}
	}
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
double lab309::WorldModel::getDate (void) const {
	return this->date;
}

const lab309::List<lab309::Animal*>& lab309::WorldModel::referencePreyList (void) const {
	return this->prey;
}

const lab309::List<lab309::Animal*>& lab309::WorldModel::referencePredatorList (void) const {
	return this->predator;
}

/*METHODS*/
lab309::Vector_2d lab309::WorldModel::discretizeToNavmesh (Vector_2d coordinate) {
	coordinate[COORDINATE_X] = (int)coordinate[COORDINATE_X] / (this->window->getWidth()/this->navmesh.getColums());
	coordinate[COORDINATE_Y] = (int)coordinate[COORDINATE_Y] / (this->window->getHeight()/this->navmesh.getLines());
	
	return coordinate;
}

void lab309::WorldModel::mapToNavmesh (List<Animal*>::Iterator iterator) {
	Vector_2d c = this->discretizeToNavmesh(iterator.getData()->getCenter());
	
	this->navmesh[c].animal = iterator;
}

void lab309::WorldModel::removeFromNavmesh (List<Animal*>::Iterator iterator) {
	Vector_2d c = this->discretizeToNavmesh(iterator.getData()->getCenter());
	
	this->navmesh[c].animal = List<Animal*>::Iterator();
}

void lab309::WorldModel::addPrey (Animal *prey, const Vector_2d &pos) {
	prey->setPos(pos);
	prey->setBirthDate(this->date);
	this->prey.add(this->prey.getLength(), prey);
	this->mapToNavmesh(this->prey.getEnd());
}

void lab309::WorldModel::addPredator (Animal *predator, const Vector_2d &pos) {
	predator->setPos(pos);
	predator->setBirthDate(this->date);
	this->predator.add(this->predator.getLength(), predator);
	this->mapToNavmesh(this->predator.getEnd());
}

void lab309::WorldModel::timePasses (void) {
	this->date = SDL_GetTicks()/1000.0;
}

void lab309::WorldModel::elderDie (void) {
	lab309::List<Animal*>::Iterator i;
	Animal *prey;
	Animal *predator;
	
	i = this->prey.getBeginning();
	while (!i.end()) {
		prey = i.getData();
		if (prey->isOld(this->date)) {
			this->removeFromNavmesh(i);
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
			this->removeFromNavmesh(i);
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
				Vector_2d c;
				c[COORDINATE_X] = (float)randomBetween(a->getXPos() - a->getDisplayWidth(), a->getXPos()+a->getDisplayWidth()),
				c[COORDINATE_Y] = (float)randomBetween(a->getYPos() - a->getDisplayHeight(), a->getYPos()+a->getDisplayHeight());
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

void lab309::WorldModel::preyMove (void) {
	lab309::List<Animal*>::Iterator i;
	Vector_2d direction;
	for (i = this->prey.getBeginning(); !i.end(); i++) {
		this->removeFromNavmesh(i);
		direction = this->movementWheel[randomBetween(0, 5)];
		//std::cout << direction << std::endl;	//debug
		//std::cout << this->window->getTimeDelta() << std::endl;	//debug
		i.getData()->move(direction, this->window->getTimeDelta());
		this->mapToNavmesh(i);
	}
}

void lab309::WorldModel::leaderPredatorMoves (void) {
	if (this->predator.getLength() == 0) {
		return;
	}
	
	List<Animal*>::Iterator leaderIndex = this->predator.getBeginning();	//tubarao mais velho eh sempre o primeiro da lista
	Animal* leader = leaderIndex.getData();
	
	if (this->prey.getLength() > 0) {
		List<Animal*>::Iterator closestPreyIndex = findClosest(leader->getCenter(), this->prey);
		Animal *closestPrey = closestPreyIndex.getData();
		if (leader->sees(closestPrey->getCenter())) {
			leader->setState(STATE_CHASING);
			Vector_2d direction = normalize(closestPrey->getCenter() - leader->getCenter());
			//std::cout << direction << std::endl;	//debug
			Vector_2d pos = discretizeToNavmesh(leader->getCenter());
			
			//predador deixa bilhete avisando a direcao que andou
			this->navmesh[pos].predatorTrace = 0.5f*(this->navmesh[pos].predatorTrace + direction);
			this->navmesh[pos].lastPredatorTraceUpdate = this->date;
			
			//predador move
			this->removeFromNavmesh(leaderIndex);
			leader->move(direction, this->window->getTimeDelta());
			this->mapToNavmesh(leaderIndex);
		} else {
			leader->setState(STATE_IDLE);
		}
		
	} else {
		leader->setState(STATE_IDLE);
	}
	
}

void lab309::WorldModel::predatorMove (void) {
	if (this->predator.getLength() < 1) {
		return;
	}
	lab309::List<Animal*>::Iterator i;
	Vector_2d direction;
	for (i = this->predator.getBeginning(); !i.end(); i++) {
		switch (i.getData()->getState()) {
			case STATE_IDLE:
				this->removeFromNavmesh(i);
				direction = this->movementWheel[randomBetween(0, 5)];
				//std::cout << direction << std::endl;	//debug
				//std::cout << this->window->getTimeDelta() << std::endl;	//debug
				i.getData()->move(direction, this->window->getTimeDelta());
				this->mapToNavmesh(i);
			break;
		}
	}
}

/*NAMESPACE*/
lab309::List<lab309::Animal*>::Iterator lab309::findClosest (const Vector_2d &start, const List<Animal*> &list) {
	List<Animal*>::Iterator i, min;
	float minDistance;
	
	min = list.getBeginning();
	minDistance = manhattanDistance(start, min.getData()->getCenter());
	for (i = min.next(); !i.end(); i++) {
		if (manhattanDistance(start, i.getData()->getCenter()) < minDistance) {
			min = i;
			minDistance = manhattanDistance(start, i.getData()->getCenter());
		}
	}
	
	return min;
}
