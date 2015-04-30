/* Jack Ryan
 * CSE 20212
 * Final Project
 * ArcherTower.h
 * Tower interface for Archer Tower derived class
 */
#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class ArcherTower : public Tower {
public:
    ArcherTower(SDL_Renderer** gRenderer, vector<Enemy*> *, vector<Tower*> *, int xpos, int ypos);  //constructor with the position as argument

private:
          
};

#endif
