/* Jack Ryan
 * CSE 20212
 * Final Project
 * Tower.h
 * Tower interface for abstract base class
 */
#ifndef TOWER_H
#define TOWER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <cmath>
#include "../Enemies/Enemy.h"
using namespace std;

class Tower : public Object {
	public:
		Tower(SDL_Renderer **gRendererPtr, vector<Enemy*> *, vector<Tower*> *);
        ~Tower();                      // deconstructor frees allocated memory
    	void attack(int*);             // function to begin attacking (decreasing health) of target
    	void render();     // makes Tower class abstract
		bool inRange();                // senses if any enemy is in the specific tower's range
        void resetTarget(Enemy *);
        void handleMouseClick(int x, int y);

	private:
		double MAX_DISTORTION;        
        struct timeval timeStruct;   // allows for milliseconds of current time, for attack frequency
        long long lastAttackTime;    // last time that an Enemy was attacked

    protected:
		int pts_per_kill;
        int MAX_DIMENSION;      // share this value with derived towers
		int towerX;
        int towerY;
		int range;
        int damage;
        int attackDelay;        // number of seconds tower will wait before attacking another enemy
        bool renderRange;       // bool flag to display range or not

        SDL_Renderer** gRenderer;    // double pointer to renderer
        SDL_Texture* gTower;   // texture containing tower's image
        SDL_Rect gTowerRect;    // container for gTower texture
        SDL_Texture* gRange;    // texture for Range radius
        SDL_Rect gRangeRect;    // container for Range radius
        Enemy* target;          // target is a pointer to the enemy that is the target
        vector<Enemy*> *enemies;  // ref to vector of addresses of enemies from main.cpp
        vector<Tower*> *towers;   // ref to vector of address of towers from main.cpp
};

#endif
