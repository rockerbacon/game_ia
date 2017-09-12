#include "window.h"
#include "sprite.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "random.h"
#include "animal.h"
#include "ai.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define MESH_W 64
#define MESH_H 64

using namespace lab309;

WorldModel *worldModel;

bool handleInput (void) {
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			return false;
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					worldModel->timePasses();
					//atualizar IA
				break;
			}
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				worldModel->addPredator(newPredator(), {event.button.x, event.button.y});
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				worldModel->addPrey(newPrey(), {event.button.x, event.button.y});
			}
		}
	}
	
	return true;
}

int main (int argc, char **args) {

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	List<Animal*>::Iterator i;
	
	Window *window;
	bool running = true;
	
	//inicializar janela e modelo do mundo
	window = new Window("Shark IA", WIDTH, HEIGHT);
	worldModel = new WorldModel(*window, MESH_H, MESH_W);
	
	//carregar texturas
	defaultPredatorTexture = window->loadTexture("img/shark.png");
	defaultPredatorSize = 0.15;
	defaultPreyTexture = window->loadTexture("img/fish.png");
	defaultPreySize = 0.08;
	
	while (running) {
		//gerar malha de navegacao
		running = handleInput();
		
		//processar interacao de agentes com o mundo
		worldModel->elderDie();
		worldModel->preyReproduce();
		worldModel->predatorEat();
		
		//desenhar mundo
		for (i = worldModel->referencePreyList().getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		for (i = worldModel->referencePredatorList().getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		window->update();
	}
	
end_program:
	delete(window);
	delete(worldModel);
	SDL_FreeSurface(defaultPredatorTexture);
	SDL_FreeSurface(defaultPreyTexture);
	SDL_Quit();

	return 0;
}
