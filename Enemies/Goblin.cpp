#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Goblin.h"
using namespace std;

Goblin::Goblin(SDL_Renderer** gRendererPtr, MapDirections pathInfo) : Enemy(gRendererPtr, pathInfo)
{
	// load enemy img
	gEnemy = NULL;
	gEnemy = loadTexture("img/goblin.png");	// utilizes Enemy class method
	health = 500;	// sets protected variable in Enemy class
    maxHealth = health; 


    enemyRect = getRect(gEnemy, ENEMY_MAX_DIMENSION, mPosX, mPosY);
}