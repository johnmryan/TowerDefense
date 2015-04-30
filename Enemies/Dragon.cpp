#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Dragon.h"
using namespace std;

Dragon::Dragon(SDL_Renderer** gRendererPtr, MapDirections pathInfo) : Enemy(gRendererPtr, pathInfo)
{
	// load enemy img
	gEnemy = NULL;
	gEnemy = loadTexture("img/dragon.png");	// utilizes Enemy class method
	health = 1800;	// sets protected variable in Enemy class
    maxHealth = health; 


    enemyRect = getRect(gEnemy, ENEMY_MAX_DIMENSION, mPosX, mPosY);
}