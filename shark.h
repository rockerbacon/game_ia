#ifndef LAB309_SHARK_H
#define LAB309_SHARK_H

#include "sprite.h"

#define SHARK_LIFETIME 10

namespace lab309 {
	class Shark : public Sprite {
		private:
			unsigned int birthDate;
			
		public:
			/*DEFAULTS*/
			static SDL_Surface *defaultTexture;
			static float defaultSize;
		
			/*CONSTRUCTORS*/
			Shark (SDL_Surface *texture, int rectWidth, int rectHeight, float size, unsigned int birthDate);
			inline Shark (void) : Shark (defaultTexture, defaultTexture->w, defaultTexture->h, defaultSize, 0) {}
			
			/*METHODS*/
			void setBirthDate (unsigned int birthDate);
			bool isOld (unsigned int time) const;
	};
};

#endif
