#include "window.h"
#include "sprite.h"
#include "Lab309_ADT_DoublyLinkedList.h"
#include "random.h"
#include "animal.h"
#include "logic.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

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
					//worldModel->timePasses();
					//atualizar IA
				break;
			}
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				worldModel->addPredator(newPredator(), {(float)event.button.x, (float)event.button.y});
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				worldModel->addPrey(newPrey(), {(float)event.button.x, (float)event.button.y});
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
	window = new Window("Shark IA", WIDTH, HEIGHT, LIMIT_30FPS);
	worldModel = new WorldModel(*window, MESH_H, MESH_W);
	
	//carregar texturas
	defaultPredatorTexture = window->loadTexture("img/shark.png");
	defaultPredatorSize = 0.1;
	defaultPreyTexture = window->loadTexture("img/fish.png");
	defaultPreySize = 0.12;
	
	while (running) {
		//gerar malha de navegacao
		running = handleInput();
		
		timeSeed();
		
		//processar interacao de agentes com o mundo
		worldModel->timePasses();
		//std::cout << "time passes" << std::endl;	//debug
		worldModel->elderDie();
		//std::cout << "the elder die" << std::endl;	//debug
		worldModel->preyReproduce();
		//std::cout << "prey reproduce" << std::endl;	//debug
		worldModel->predatorEat();
		//std::cout << "predators eat" << std::endl;	//debug
		worldModel->preyMove();
		worldModel->leaderPredatorMoves();
		worldModel->predatorMove();
		//std::cout << "prey move" << std::endl;	//debug
		
		//desenhar mundo
		for (i = worldModel->referencePreyList().getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		for (i = worldModel->referencePredatorList().getBeginning(); !i.end(); i++) {
			i.getData()->blitTo(*window);
		}
		//std::cout << "animals are blitted" << std::endl;	//debug
		window->update();
		//std::cout << "window updates" << std::endl;	//debug
	}
	
end_program:
	delete(window);
	delete(worldModel);
	SDL_FreeSurface(defaultPredatorTexture);
	SDL_FreeSurface(defaultPreyTexture);
	SDL_Quit();

	return 0;
}
