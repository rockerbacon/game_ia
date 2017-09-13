/*
 * Data armazenada em segundos
 */

#ifndef LAB309_AI_H
#define LAB309_AI_H

#include "Lab309_ADT_Matrix.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "sprite.h"
#include "animal.h"
#include "vertex.h"
#include <SDL2/SDL.h>

namespace lab309 {
	
	class WorldModel {
		private:
			struct Cell {
				List<Animal*>::Iterator animal;
			};
			
			/*ATTRIBUTES*/
			const Window *window;
			Matrix<struct Cell> navmesh;
			double date;
			List<Animal*> prey;
			List<Animal*> predator;
			const Vector_2d movementWheel[5] = {DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_LEFT, DIRECTION_DOWN, {0,0}};
			
			Vector_2d discretizeToNavmesh(Vector_2d coordinate);
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
			void addPrey (Animal *prey, const Vector_2d &pos);
			void addPredator (Animal *predator, const Vector_2d &pos);
			
			void timePasses (void);
			void elderDie (void);
			void preyReproduce (void);
			void predatorEat (void);
			void preyMove (void);
			
	};
};

#endif
