#include "window.h"
#include "sprite.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "Lab309_ADT_Matrix.h"
#include "random.h"
#include "fish.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define MESH_W 64
#define MESH_H 64

#define SHARK_SIZE 0.1
#define FISH_SIZE 0.1

using namespace lab309;

unsigned int gTimer;
List<Sprite*>	gFish,
				gShark;
SDL_Surface	*gSharkTexture,
			*gFishTexture;
Matrix<List<Sprite*>::Iterator> gNavmesh(MESH_W, MESH_H);

//arredonda um ponto no espaco para um ponto na malha
int mapXPoint (int point) {
	return point - point % (WIDTH/MESH_W);
}
int mapYPoint (int point) {
	return point - point % (HEIGHT/MESH_H);
}

void addAgent (SDL_Surface *texture, List<Sprite*> &list, float size, int x, int y) {
	Sprite *object = new Sprite (texture, texture->w, texture->h, size);
	object->setPos({mapXPoint(x), mapYPoint(y)});
	list.add(0, object);
}

void addFish (int x, int y) {
	Fish *fish = new Fish (gFishTexture, gFishTexture->w, gFishTexture->h, FISH_SIZE, gTimer);
	fish->setPos({mapXPoint(x), mapYPoint(y)});
	gFish.add(0, fish);
}

bool handleInput (void) {
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			return false;
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					gTimer++;
					//atualizar IA
				break;
			}
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				addAgent(gSharkTexture, gShark, SHARK_SIZE, event.button.x, event.button.y);
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				addFish(event.button.x, event.button.y);
			}
		}
	}
	
	return true;
}

void generateNavmesh (void) {
	size_t i, j;
	List<Sprite*>::Iterator it;
	Coordinate coordinate;
	
	//zerar navmesh
	for (i = 0; i < gNavmesh.getLines(); i++) {
		for (j = 0; j < gNavmesh.getLines(); j++) {
			gNavmesh[i][j] = List<Sprite*>::Iterator();
		}
	}
	
	//preencher tubaroes na navmesh
	for (it = gShark.getBeginning(); !it.end(); it++) {
		coordinate = it.getData()->getCenter();
		gNavmesh[mapXPoint(coordinate.x)][mapYPoint(coordinate.y)] = it;
	}
	//preencher peixes na navmesh
	for (it = gFish.getBeginning(); !it.end(); it++) {
		coordinate = it.getData()->getCenter();
		gNavmesh[mapXPoint(coordinate.x)][mapYPoint(coordinate.y)] = it;
	}
}

void killFish (List<Sprite*>::Iterator &fish) {
	delete(fish.getData());
	gFish.remove(fish);
}

int main (int argc, char **args) {

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	List<Sprite*>::Iterator i, j;
	
	Window *window;
	bool running = true;
	
	gTimer = 0;
	
	//inicializar janela
	window = new Window("Shark IA", WIDTH, HEIGHT);
	gSharkTexture = window->loadTexture("img/shark.png");
	gFishTexture = window->loadTexture("img/fish.png");
	
	while (running) {
		generateNavmesh();
		running = handleInput();
		
		for (i = gFish.getBeginning(); !i.end(); i++) {
			Fish *fish = (Fish*)(i.getData());
			
			j = i.next();
			while (fish->canReproduce(gTimer) && !j.end()) {
				//colisao peixe-peixe
				if (collision(*i.getData(), *j.getData())) {
					//printf("fish-fish collision\n");	//debug
					gFish.add(0, fish->reproduce(gTimer));
 				}
 				
 				j++;
			}
			
			if (fish->isOld(gTimer)) {
				killFish(i);
				i--;
			} else {
				//colisao peixe-tubarao
				for (j = gShark.getBeginning(); !j.end(); j++) {
					if (collision(*i.getData(), *j.getData())) {
						//printf("fish-shark collision\n");	//debug
						killFish(i);
						i--;
					}
				}
			}
		}
		
		//desenhar
		for (i = gShark.getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		for (i = gFish.getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		window->update();
	}
	
end_program:
	delete(window);
	for (i = gShark.getBeginning(); !i.end(); i++) {
		delete(i.getData());
	}
	for (i = gFish.getBeginning(); !i.end(); i++) {
		delete(i.getData());
	}
	SDL_FreeSurface(gSharkTexture);
	SDL_FreeSurface(gFishTexture);
	SDL_Quit();

	return 0;
}
