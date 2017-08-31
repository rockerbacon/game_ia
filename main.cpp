#include "window.h"
#include "sprite.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "random.h"
#include "fish.h"
#include "shark.h"
#include "ai.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define MESH_W 64
#define MESH_H 64

using namespace lab309;

SDL_Surface* Shark::defaultTexture = NULL;
float Shark::defaultSize = 0.08;
SDL_Surface* Fish::defaultTexture = NULL;
float Fish::defaultSize = 0.15;

Navmesh gNavmesh(WIDTH, HEIGHT, MESH_W, MESH_H);
WorldModel worldModel;

bool handleInput (void) {
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			return false;
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					worldModel.timePasses();
					//atualizar IA
				break;
			}
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				worldModel.addShark(new Shark(), {event.button.x, event.button.y});
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				worldModel.addFish(new Fish(), {event.button.x, event.button.y});
			}
		}
	}
	
	return true;
}

int main (int argc, char **args) {

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	List<Sprite*>::Iterator i;
	
	Window *window;
	bool running = true;
	
	//inicializar janela
	window = new Window("Shark IA", WIDTH, HEIGHT);
	
	//carregar texturas
	Shark::defaultTexture = window->loadTexture("img/shark.png");
	Fish::defaultTexture = window->loadTexture("img/fish.png");
	
	while (running) {
		//gerar malha de navegacao
		gNavmesh.clear();
		gNavmesh.add(worldModel.referenceFishList());
		gNavmesh.add(worldModel.referenceSharkList());
		
		running = handleInput();
		
		//processar interacao de agentes com o mundo
		worldModel.elderDie();
		worldModel.fishReproduce();
		worldModel.sharkEat();
		
		//desenhar mundo
		for (i = worldModel.referenceFishList().getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		for (i = worldModel.referenceSharkList().getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		window->update();
	}
	
end_program:
	delete(window);
	SDL_FreeSurface(Shark::defaultTexture);
	SDL_FreeSurface(Fish::defaultTexture);
	SDL_Quit();

	return 0;
}
