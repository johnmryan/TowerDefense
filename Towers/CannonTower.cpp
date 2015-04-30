/* CSE 20212
 * Final Project
 * CannonTower.cpp
 * constructors and member functions
*/

#include "CannonTower.h"

//constructor that initializes an CannonTower (arguments = position)
CannonTower::CannonTower(SDL_Renderer** gRendererPtr, vector<Enemy*> * enemiesTemp, \
    vector<Tower*> * towersTemp, int xpos, int ypos) : Tower(gRendererPtr, enemiesTemp, towersTemp)
{
        //initialize fields
    towerX = xpos;
    towerY = ypos;
    damage = 100;
    attackDelay = 3;    //number of times it attacks per minute
    range = 180;

    gTower = loadTexture("img/cannonTower.png");
    gTowerRect = getRect(gTower, MAX_DIMENSION, towerX, towerY);
    gRange = loadTexture("img/range.png");                          // load in range radius image
    gRangeRect = getRect(gRange, 2*range, towerX, towerY);          // container for range radius with correct sizing

   
}