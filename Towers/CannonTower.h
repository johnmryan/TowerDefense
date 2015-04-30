/* Jack Ryan
 * CSE 20212
 * Final Project
 * CannonTower.h
 * Tower interface for Cannon Tower derived class
 */
#ifndef CANNONTOWER_H
#define CANNONTOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class CannonTower : public Tower {
public:
    CannonTower(SDL_Renderer** gRenderer, vector<Enemy*> *, vector<Tower*> *, int xpos, int ypos);  //default constructor

private:

};

#endif
