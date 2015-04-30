/* MapDirections.h
 * class to store and retrieve directions of when and how to turn on
 * the Tower Defense path
 */
#ifndef MAPDIRECTIONS_H
#define MAPDIRECTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class MapDirections
{
    public:	
		MapDirections();
		void setNext(string, int);	// set constraints for next turn
		bool next();				// increment index to next set of directions. Returns false if on last direction
		string getDir();			// get string for direction (ie "up", "right", ect)
		int getStop();				// get stop value
		bool isEnd();				// returns true if at end of path, false otherwise

    private:
    	int index;					// tracks position on map, which set of instructions to get next
		vector<string> directions; 	// vector of directions
		vector<int> stops;			// vector of stop values
};

#endif