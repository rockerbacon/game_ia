#ifndef LAB309_AI_H
#define LAB309_AI_H

#include "Lab309_ADT_Matrix.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "sprite.h"
#include "fish.h"
#include "shark.h"
#include "coordinates.h"

namespace lab309 {
	class Navmesh {
		private:
			/*ATTRIBUTES*/
			int windowWidth;
			int windowHeight;
			lab309::Matrix<List<Sprite*>::Iterator> matrix;
			
		public:
			/*CONSTRUCTORS*/
			Navmesh (int windowWidth, int windowHeight, size_t width, size_t height);
			
			/*GETTERS*/
			size_t getWidth (void) const;
			size_t getHeight (void) const;
			
			/*METHODS*/
			//arredonda uma posicao na janela para uma posicao que esteja na malha
			Coordinate roundToWindow (Coordinate coordinate);
			void clear (void);
			void add (const List<Sprite*> &list);
	};
	
	class WorldModel {
		private:
			/*ATTRIBUTES*/
			unsigned int date;
			List<Sprite*> fish;
			List<Sprite*> shark;
			
		public:
			/*CONSTRUCTORS*/
			WorldModel (void);
			~WorldModel (void);
			
			/*GETTERS*/
			unsigned int getDate (void) const;
			const List<Sprite*>& referenceFishList (void) const;
			const List<Sprite*>& referenceSharkList (void) const;
			
			/*METHODS*/
			void addFish (Fish *fish, const Coordinate &pos);
			void addShark (Shark *shark, const Coordinate &pos);
			
			void timePasses (void);
			void elderDie (void);
			void fishReproduce (void);
			void sharkEat (void);
			
	};
};

#endif
