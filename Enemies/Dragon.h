/* Dragon.h
 * Fund Comp II, Tower Defense
 * This Enemy class is derived from the abstract Enemy class
 * */

#ifndef DRAGON_H
#define DRAGON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Enemy.h"
#include "../MapDirections.h"

class Dragon : public Enemy {
	public:
		Dragon(SDL_Renderer **gRenderer, MapDirections pathInfo);  // constructor

	private:
	
};

#endif
