//David Lewis
//cse20212
//Final Project
//FreezeTower.h

#ifndef FREEZETOWER_H
#define FREEZETOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class FreezeTower : public Tower {
public:
    FreezeTower(SDL_Renderer** gRenderer, vector<Enemy*> *, vector<Tower*> *, int xpos, int ypos);  //default constructor

private:

};

#endif
