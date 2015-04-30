/* Wizard.h
 * Fund Comp II, Tower Defense
 * This Enemy class is derived from the abstract Enemy class
 * */

#ifndef WIZARD_H
#define WIZARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Enemy.h"
#include "../MapDirections.h"

class Wizard : public Enemy {
	public:
		Wizard(SDL_Renderer **gRenderer, MapDirections pathInfo);  // constructor

	private:
	
};

#endif
