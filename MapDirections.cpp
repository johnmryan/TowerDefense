#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "MapDirections.h"
using namespace std;

/* Constructor */
MapDirections::MapDirections() {
	index = 0;	// set index to 0
}

/* Add the next direction and stop values to their respective vectors
*/
void MapDirections::setNext(string direction, int stop) {
	directions.push_back(direction);
	stops.push_back(stop);
}

/* Incremenets the index 
 * returns true if there is a next set of directions, otherwise false
 */
bool MapDirections::next() {
	if((index + 1) > directions.size()) {	// +1 because size is 1 ahead of the last index
		cout << "Unable to move to next index in MapDirections vector. Currently at last occupied index." << endl;
		return false;
	} else {
		index++;
		return true;
	}
}

/* Returns the direction that the Enemy should be moving in 
*/
string MapDirections::getDir() {
	return directions[index];
}	

/* Returns the x or y coordinate to stop moving at, prompting the next instruction set
*/
int MapDirections::getStop() {
	return stops[index];
}

/* Returns true if at the end of the path, false otherwise
*/
bool MapDirections::isEnd() {
	if(index + 1 > directions.size()) return true;
	else return false;
}