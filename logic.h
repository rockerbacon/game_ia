/*
 * Tempo sempre em segundos
 * Distancia sempre em pixels
 */

#ifndef LAB309_AI_H
#define LAB309_AI_H

#include "Lab309_ADT_Matrix.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "sprite.h"
#include "animal.h"
#include <SDL2/SDL.h>

#define PREDATOR_FOV 100

namespace lab309 {
	
	class Cell {
		public:
			List<Animal*>::Iterator animal;
			Vector<float> predatorTrace;
			double lastPredatorTraceUpdate;
			Vector<float> preyTrace;
			double lastPreyTraceUpdate;
			
			Cell (List<Animal*>::Iterator animal, const Vector<float> &predatorTrace, double lastPredatorTraceUpdate, const Vector<float> &preyTrace, double lastPreyTraceUpdate);
	};
	
	class WorldModel {
		private:
			/*ATTRIBUTES*/
			const Window *window;
			Matrix<Cell*> navmesh;
			double date;
			List<Animal*> prey;
			List<Animal*> predator;
			const Vector<float> movementWheel[5] = {DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_LEFT, DIRECTION_DOWN, {0,0}};
			
			Vector<float> discretizeToNavmesh(Vector<float> coordinate);
			void mapToNavmesh (List<Animal*>::Iterator iterator);
			void removeFromNavmesh(List<Animal*>::Iterator iterator);
			
		public:
			/*CONSTRUCTORS*/
			WorldModel (const Window &window, size_t navmeshHeight, size_t navmeshWidth);
			~WorldModel (void);
			
			/*GETTERS*/
			double getDate (void) const;
			const List<Animal*>& referencePreyList (void) const;
			const List<Animal*>& referencePredatorList (void) const;
			
			/*METHODS*/
			void addPrey (Animal *prey, const Vector<float> &pos);
			void addPredator (Animal *predator, const Vector<float> &pos);
			
			void timePasses (void);
			void elderDie (void);
			void preyReproduce (void);
			void predatorEat (void);
			void preyMove (void);
			void leaderPredatorMoves (void);
			void predatorMove (void);
			
	};
	
	bool see (const Animal *a, const Animal *b);
	List<Animal*>::Iterator findClosest (const Vector<float> &start, const List<Animal*> &list);
};

#endif
