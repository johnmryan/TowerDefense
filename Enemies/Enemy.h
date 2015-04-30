/* Enemy.h
 * Fund Comp II, Tower Defense
 * This class serves as an abstract base class for all enemeies that will move across the path
 * */

#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/time.h>
#include "../MapDirections.h"
#include "../Object.h"
#include "HealthBar.h"

class Enemy : public Object
{
    public:	

		//Maximum velocity of the Enemy
		static const double ENEMY_VEL = 3;		// different computers seem to require a different velocity

		Enemy(SDL_Renderer **gRenderer, MapDirections pathInfo);  // constructor
		~Enemy();	// deconstructor
		void render();		// Repositions the the enemy on the screen after gRenderer is updated
		bool move();		// move the enemy on the screen according to map positions
		double getPosX();	// return current x coordinate of enemy
		double getPosY();	// return current y coordinate
		void takeDamage(int);	// take x amount of damage from an Enemy tower
		bool isDead();		// return T if health has run out, false otherwise
	
	protected:
		int ENEMY_MAX_DIMENSION;
		double MAX_DISTORTION;		// decimal of max percentage
		MapDirections mapDirections;// object to hold information to know when the Enemy should turn on the path
		SDL_Texture* gEnemy;		// image of enemy
		SDL_Renderer** gRenderer;	// double pointer to renderer
		SDL_Rect enemyRect;			// container for enemy image. Has positioning properties (x and y location)
		double mPosX, mPosY;  		// The X and Y positions of the enemy
		struct timeval tp;			// allows for milliseconds of current time, for animation
		long long lastMoveTime;		// store time of last movement
		int moveInterval;			// move every __ milliseconds

		long health;				// should be different for each Enemy and set in the derived classes
		double maxHealth;				// hold initial health value
		HealthBar* healthBar;		// health bar to display above the Enemy

    private:
		
};

#endif
