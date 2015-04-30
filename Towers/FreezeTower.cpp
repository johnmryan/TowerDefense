/* CSE 20212
 * Final Project
 * FreezeTower.cpp
 * constructors and member functions
*/

#include "FreezeTower.h"

//constructor that initializes an FreezeTower (arguments = position)
FreezeTower::FreezeTower(SDL_Renderer** gRendererPtr, vector<Enemy*> * enemiesTemp, \
    vector<Tower*> * towersTemp, int xpos, int ypos) : Tower(gRendererPtr, enemiesTemp, towersTemp)
{
    //initialize fields
    towerX = xpos;
    towerY = ypos;
    attackDelay = 2;    //number of times it attacks per minute
    range = 120;
    damage = 90;

    gTower = loadTexture("img/freezeTower.png");
	gTowerRect = getRect(gTower, MAX_DIMENSION, towerX, towerY);
    gRange = loadTexture("img/range.png");                          // load in range radius image
    gRangeRect = getRect(gRange, 2*range, towerX, towerY);          // container for range radius with correct sizing

}