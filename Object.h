/* Object.h
 * Fund Comp II, Tower Defense
 * This abstract Object class is desiged to be used by both Enemy and Tower classes in order to return
 * an SDL Texture given an image path, and an SDL_Rect container for the texture
 * */

#ifndef Object_H
#define Object_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
 using namespace std;

class Object {

public:
	Object(SDL_Renderer **gRenderer);		
	SDL_Rect getRect(SDL_Texture* texture, int maxDimension, int x, int y);
	SDL_Texture* loadTexture( std::string path );
	virtual void render() = 0;

private:
	SDL_Renderer** gRenderer;	// double pointer to renderer
	
protected:
	int MAX_DIMENSION;
	double MAX_DISTORTION;		// decimal of max percentage
};

#endif