/* HealthBar.h
 * Health bar to visualize the remaining health of an Enemy
 */

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "../Object.h"

class HealthBar : public Object {
	public:
		HealthBar(SDL_Renderer **gRenderer, int maxEnemyDimension);
		~HealthBar();									// deallocate resources
		void update(int x, int y, double proportion);	// update key properties of health bar (before rendered)
		void render();									// render health bar to screen
		SDL_Rect getRect(int width, int height);		// get rectangle container for health bar

	private:
		SDL_Renderer** gRenderer;	// double pointer to renderer
		int barWidth;				// width of health bar
		int barHeight;				// height of health bar
		int maxEnemyDimension;		// store max dimension of enemy

		SDL_Texture* gGreenBar;
		SDL_Texture* gRedBar;

		SDL_Rect greenBarRect;
		SDL_Rect redBarRect;

};

#endif