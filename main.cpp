#include "window.h"
#include "sprite.h"
#include "Lab309_ADT_LinkedList.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define MESH 64

using namespace lab309;

bool handleInput (LList<Sprite*> &shark, LList<Sprite*> &fish, SDL_Surface *sharkTexture, SDL_Surface *fishTexture) {
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			return false;
		} else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					//atualizar IA
				break;
			}
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			Sprite *object;
			int x = event.button.x - event.button.x % (WIDTH/MESH),
				y = event.button.y - event.button.y % (HEIGHT/MESH);
			if (event.button.button == SDL_BUTTON_LEFT) {
				object = new Sprite(sharkTexture, sharkTexture->w, sharkTexture->h, 0.1);
				object->setPos({x, y});
				shark.add(shark.getLength(), object);
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				object = new Sprite(fishTexture, fishTexture->w, fishTexture->h, 0.1);
				object->setPos({x, y});
				fish.add(fish.getLength(), object);
			}
		}
	}
	
	return true;
}

int main (int argc, char **args) {

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	LList<Sprite*>	shark, fish;
	LList<Sprite*>::Iterator i;
	
	SDL_Surface *sharkTexture, *fishTexture;
	SDL_Event event;
	
	Window *window;
	bool running = true;
	
	//inicializar janela
	window = new Window("Shark IA", WIDTH, HEIGHT);
	sharkTexture = window->loadTexture("img/shark.png");
	fishTexture = window->loadTexture("img/fish.png");
	
	while (running) {
		running = handleInput(shark, fish, sharkTexture, fishTexture);
		
		for (i = shark.beginning(); !i.end(); i.next()) {
			i.getData()->blitTo(*window);
		}
		for (i = fish.beginning(); !i.end(); i.next()) {
			i.getData()->blitTo(*window);
		}
		window->update();
	}
	
end_program:
	delete(window);
	for (i = shark.beginning(); !i.end(); i.next()) {
		delete(i.getData());
	}
	for (i = fish.beginning(); !i.end(); i.next()) {
		delete(i.getData());
	}
	SDL_FreeSurface(sharkTexture);
	SDL_FreeSurface(fishTexture);
	SDL_Quit();

	return 0;
}
