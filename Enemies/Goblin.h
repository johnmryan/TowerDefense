/* Goblin.h
 * Fund Comp II, Tower Defense
 * This Enemy class is derived from the abstract Enemy class
 * */

#ifndef GOBLIN_H
#define GOBLIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Enemy.h"
#include "../MapDirections.h"

class Goblin : public Enemy {
	public:
		Goblin(SDL_Renderer **gRenderer, MapDirections pathInfo);  // constructor

	private:
	
};

#endif
