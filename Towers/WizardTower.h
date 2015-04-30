/* Jack Ryan
 * CSE 20212
 * Final Project
 * WizardTower.h
 * Tower interface for Archer Tower derived class
 */
#ifndef WIZARDTOWER_H
#define WIZARDTOWER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Tower.h"
using namespace std;

class WizardTower : public Tower {
public:
        WizardTower( SDL_Renderer** gRenderer, vector<Enemy*> *, vector<Tower*> *, int xpos, int ypos); //constructor with the position as argument

private:

};

#endif
