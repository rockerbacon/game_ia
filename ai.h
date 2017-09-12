#ifndef LAB309_AI_H
#define LAB309_AI_H

#include "Lab309_ADT_Matrix.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "sprite.h"
#include "animal.h"
#include "coordinates.h"

namespace lab309 {
	
	class WorldModel {
		private:
			struct Cell {
				List<Animal*>::Iterator animal;
			};
			
			/*ATTRIBUTES*/
			const Window *window;
			Matrix<struct Cell> navmesh;
			unsigned int date;
			List<Animal*> prey;
			List<Animal*> predator;
			
			void mapToNavmesh (List<Animal*>::Iterator iterator);
			
		public:
			/*CONSTRUCTORS*/
			WorldModel (const Window &window, size_t navmeshHeight, size_t navmeshWidth);
			~WorldModel (void);
			
			/*GETTERS*/
			unsigned int getDate (void) const;
			const List<Animal*>& referencePreyList (void) const;
			const List<Animal*>& referencePredatorList (void) const;
			
			/*METHODS*/
			void addPrey (Animal *prey, const Coordinate &pos);
			void addPredator (Animal *predator, const Coordinate &pos);
			
			void timePasses (void);
			void elderDie (void);
			void preyReproduce (void);
			void predatorEat (void);
			
	};
};

#endif
