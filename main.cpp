//Using SDL, SDL_image, SDL_ttf
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sys/time.h>
#include <ctime>
#include <unistd.h> // usleep
#include <stdlib.h>	// srand
#include "Towers/Tower.h"
#include "Towers/TowerSpace.h"
#include "Enemies/Enemy.h"
#include "Enemies/Goblin.h"
#include "Enemies/Troll.h"
#include "Enemies/Dragon.h"
#include "Enemies/Wizard.h"
#include "MapDirections.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;

const int TOWER_MAX_DIMENSION = 70;
const int ENEMY_MAX_DIMENSION = 60;
const double MAX_DISTORTION = .57;		// decimal of max percentage
const int ENEMY_TIME_DELAY = 4500;		// delay between enemies traversing the path, milliseconds

//Text palcement
const int TITLE_Y = 0;
const int COIN_X = 5;
const int COIN_Y = 620;
const int LIVES_X = 5;
const int LIVES_Y = 660;
const int WAVE_X = 5;
const int WAVE_Y = 700;

// methods
bool init();		//Starts up SDL and creates window
bool loadMedia();	//Loads media
void close();		//Frees media and shuts down SDL
void renderWin();
void renderLose();
SDL_Rect getRect(SDL_Texture* texture, int maxDimension, int x, int y);
void moveEnemies(int *);						// moves all enemies in the enemies vector
void addEnemies(MapDirections mapDirections, vector<string> *, int * nEnemiesAdded);		// add enemies until max # reached based on a vector of predefined enemies
SDL_Texture* renderText(const string &message);	// render text-labels onto the screen
string toString(int);							// converts integer to string
vector<string> split(const string &s, char delim);	// given a string, returns a vector with elements of string using delimeter
void renderText(int total_points, int lives, int wave);	// render all text textures to the screen (title, # coins, # lives)
void render(int total_points, int lives, int wave);		// render everything that needs to be rendered, in the correct order

// global vars
SDL_Texture* loadTexture( std::string path );	//Loads individual image as texture
SDL_Window* gWindow = NULL;			//The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;		//The window renderer
SDL_Texture* gBackground = NULL;		//Current displayed texture
SDL_Texture* gYouWin = NULL; //winner screen
SDL_Texture* gYouLose = NULL; //loser screen
vector<Enemy*> enemies;				// stores all enemies
vector<TowerSpace*> towerSpaces;
vector<Tower*> towers;

// True Type Font
string fontFile = "img/SEASRN__.ttf";
TTF_Font *gFont = NULL;
SDL_Color textColor;
int TEXT_WIDTH = 0;		// these are updated each time renderText is called
int TEXT_HEIGHT = 0;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
		return 1;
	}
	
		//Load media
	if( !loadMedia() )
	{
		printf( "Failed to load media!\n" );
		return 2;
	}
	
	bool quit = false;	// Main loop flag
	SDL_Event e;		// Event handler
	srand(time(NULL));	// seed random generator

    // add directions for the specific map (must be hard-coded for each map)
	MapDirections mapDirections;	// stores turning instructions for the map's path
    mapDirections.setNext("right", .1675*SCREEN_WIDTH);
    mapDirections.setNext("up", .1750*SCREEN_HEIGHT);
    mapDirections.setNext("right", .3677*SCREEN_WIDTH);
    mapDirections.setNext("down", .6488*SCREEN_HEIGHT);
    mapDirections.setNext("right", .6361*SCREEN_WIDTH);
    mapDirections.setNext("up", .3850*SCREEN_HEIGHT);
    mapDirections.setNext("right", SCREEN_WIDTH);

    // create a hashmap to extract a string of enemies for each wave
    map<int, string> waveEnemies;
    waveEnemies[1] = "g,g,t,g,w,g";
    waveEnemies[2] = "g,t,w,g,w,t,w";
    waveEnemies[3] = "w,t,w,g,t,t,w";
    waveEnemies[4] = "t,w,d,t,w,d,t,w,d";

    int nWaves = waveEnemies.size();
    int nEnemiesAdded = 0;
    bool allEnemiesAdded = false;

    // add first enemy immediately
    struct timeval tp;			// allows for milliseconds of current time
    gettimeofday(&tp, NULL);
    long int clockTime;			// used to track current time
	long int lastAddTime = tp.tv_sec * 1000 + tp.tv_usec / 1000; //get current timestamp in milliseconds

	int total_points = 400;
	int lives = 3;
	int wave = 1;
	vector<string> curWaveEnemies = split(waveEnemies[wave], ',');
    addEnemies(mapDirections, &curWaveEnemies, &nEnemiesAdded);

	TowerSpace *tower1 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 80, 360);
	TowerSpace *tower2 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 220, 275);
	TowerSpace *tower3 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 400, 440);
	TowerSpace *tower4 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 670, 285);
	TowerSpace *tower5 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 750, 435);
	TowerSpace *tower6 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 500, 590);
	TowerSpace *tower7 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 400, 200);
	TowerSpace *tower8 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 160, 120);
	TowerSpace *tower9 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 220, 435);
	TowerSpace *tower10 = new TowerSpace(&gRenderer, &towerSpaces, &towers, &enemies, 500, 360);
	towerSpaces.push_back(tower1);
	towerSpaces.push_back(tower2);
	towerSpaces.push_back(tower3);
	towerSpaces.push_back(tower4);
	towerSpaces.push_back(tower5);
	towerSpaces.push_back(tower6);
	towerSpaces.push_back(tower7);
	towerSpaces.push_back(tower8);
	towerSpaces.push_back(tower9);
	towerSpaces.push_back(tower10);

	bool mouseClick = false;	// flag in case mouseclick occurs during execution in another part of main
	int x,y;	// x and y locations of mouseclick 
	
	


	//While application is running

	while( !quit )
	{
		SDL_Event e2;
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			//If mouse click occurs, place image where mouse was clicked
			if(e.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&x,&y);
				// pass x and y mouse click coordinates Towers
				for(int i = 0; i < towers.size(); i++) {
					towers[i]->handleMouseClick(x, y);
				}
				mouseClick = false; 	// reset flag
				break;
			}
			else if(mouseClick) {
				// pass x and y mouse click coordinates Towers
				for(int i = 0; i < towers.size(); i++) {
					towers[i]->handleMouseClick(x, y);
				}
				mouseClick = false; 	// reset flag
				break;
			} else if(e.type == SDL_KEYDOWN) {
				mouseClick = false;
				break;
			}
			
		}	

		// check if wave is over. If so, reset and prepare to initialize next wave
		if(allEnemiesAdded && enemies.size() == 0) {
			cout << "All enemies on wave " << wave << " have been defeated!" << endl;
			wave++;
			if(wave > nWaves) {
				cout << "You have defeated all of the waves!" << endl;
				quit = true;

				continue;	// game should be over
			}
			enemies.clear();
			curWaveEnemies = split(waveEnemies[wave], ',');
			allEnemiesAdded = false;
			nEnemiesAdded = 0;
		}
		
		// set timing to correctly space enemies
		if(!allEnemiesAdded) {
			gettimeofday(&tp, NULL);
			clockTime = tp.tv_sec * 1000 + tp.tv_usec / 1000; //get current timestamp in milliseconds
		}
		// check if it is time for another enemy to be added
		if(!allEnemiesAdded && nEnemiesAdded < curWaveEnemies.size() && (clockTime - lastAddTime) >= ENEMY_TIME_DELAY) {
    		addEnemies(mapDirections, &curWaveEnemies, &nEnemiesAdded);
    		lastAddTime = clockTime;
    		if(nEnemiesAdded == curWaveEnemies.size()) allEnemiesAdded = true;
		}

		moveEnemies(&lives);	// moves all enemies in enemies vector (updates position)

		//Clear screen
		SDL_RenderClear( gRenderer );

		// render everything: background, towers, towerspaces, enemies, on-screen text
		render(total_points, lives, wave);
		
		// if player has lost all lives, GAME OVER
		if(lives == 0){
			/*
			int extraWidth = 200;
			int extraHeight = 150;
			SDL_Texture *gameOverTexture = renderText("GAME OVER!");
			SDL_Rect gameOverRect {.5*SCREEN_WIDTH - .5*(TEXT_WIDTH +extraWidth), \
				.5*(SCREEN_HEIGHT + extraHeight), TEXT_WIDTH + extraWidth, TEXT_HEIGHT + extraHeight};
			SDL_RenderCopy(gRenderer, gameOverTexture, NULL, &gameOverRect);
			SDL_DestroyTexture(gameOverTexture);
			sleep(5);	// wait for 5 seconds, displaying "GAME OVER", before continuing
			*/
			cout << "GAME OVER!" << endl;
			quit = true;
		}

		//iterates through the towers and calls the inRange to sense if enemies are in range
		if(SDL_PollEvent(&e2) != 0) {
			// try to update coordinates of last mouseclick again
			if(e2.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&x,&y);
				mouseClick = true;
			}
		}

		for(int i=0;i<towerSpaces.size();i++){
			if(mouseClick) break;
			if (towerSpaces[i]->dispDropDown(x,y)){
				if(e2.type == SDL_KEYDOWN ){
					//cout << "e2" << endl;
					if( towerSpaces[i]->handleKeyPress(e2, &total_points)) {
						break;
					}
				} else if(e.type == SDL_KEYDOWN) {
		            // also check if other SDL_Event received a keypress
					if( towerSpaces[i]->handleKeyPress(e, &total_points)) {
						e = e2;
						break;
					}
				} 				
	        }
		}

		// find enemies that are Towers' range, and attack them
		for (int i=0;i<towers.size();i++){
			if (towers[i]->inRange()){
				towers[i]->attack(&total_points);
			}
		}

		//Update screen
		SDL_RenderPresent( gRenderer );

	}
	
	if(wave > nWaves){
		renderWin(); //display you win! on screen
		SDL_RenderPresent( gRenderer ); //update screen one last time
		sleep(6); //allow you win/lose title to display before closing window
		quit = true;
	}
	if(lives == 0){
		renderLose(); //display you lose on screen
		SDL_RenderPresent( gRenderer ); //update screen one last time
		sleep(6); //allow you win/lose title to display before closing window
		quit = true;
	}

	SDL_RenderPresent( gRenderer ); //update screen one last time

	//Free resources and close SDL
	close();


	return 0;
}

void renderWin()
{
	SDL_RenderCopy( gRenderer, gYouWin, NULL, NULL); //render you win texture
}
void renderLose()
{
	SDL_RenderCopy( gRenderer, gYouLose, NULL, NULL); //render you lose texture
}
/* Render background, Towers, TowerSpaces, Enemies, and text labels
 * Order of rendering matters. Most recently rendered will be on top
 */
void render(int total_points, int lives, int wave) {
	//Render background to screen
	SDL_RenderCopy( gRenderer, gBackground, NULL, NULL );	// MUST BE FIRST: render background, automatically fills the window
		
	// render each TowerSpace
	for (int i=0;i<towerSpaces.size();i++){
		towerSpaces[i]->render();
	}
	//renders the Towers
	for (int i=0;i<towers.size();i++){
		towers[i]->render();
	}
	// call SDL_RenderCopy() on all enemies in the enemies vector
	for(int i = 0; i < enemies.size(); i++) {
		enemies[i]->render();
	}

	renderText(total_points, lives, wave);
}

// adds enemies every ____seconds, based on a predefined vector of enemies
void addEnemies(MapDirections mapDirections, vector<string> * curWaveEnemies, int *nEnemiesAdded) {
	string enemyCode = (*curWaveEnemies)[*nEnemiesAdded]; // save code for next enemy to be added

	if(enemyCode == "g") {
		Goblin* goblin = new Goblin(&gRenderer, mapDirections);
		enemies.push_back(goblin);
	} else if(enemyCode == "t") {
		Troll* troll = new Troll(&gRenderer, mapDirections);
		enemies.push_back(troll);
	} else if(enemyCode == "w") {
		Wizard* wizard = new Wizard(&gRenderer, mapDirections);
		enemies.push_back(wizard);
	} else if(enemyCode == "d") {
		Dragon* dragon = new Dragon(&gRenderer, mapDirections);
		enemies.push_back(dragon);
	} else {
		cout << "Attempted to add invalid enemy" << endl;
	}
	(*nEnemiesAdded)++;	// incremement nEnemiesAdded counter
}

/* Move all enemies in the enemies vector
 * Check return status of enemy.move(). If false, then the enemy has
 * reached the end of the path, and should be removed from the enemies vector
 */
void moveEnemies(int* life) {
	for(int i = 0; i < enemies.size(); i++) {
		if(enemies[i]->move() == false) {			// if enemy has reached end of path
			*life -= 1;
			enemies.erase(enemies.begin() + i);
		}
	}
}

/* Render the title, number of coins, and number of lives as text to the screen
 * Destroys the SDL_Textures after they are rendered
 */
void renderText(int total_points, int lives, int wave) {
	int extraTitleWidth = 150;
	int extraTitleHeight = 70;
	SDL_Texture *titleTexture = renderText("Tower Defense");
	SDL_Rect titleRect {.5*SCREEN_WIDTH - .5 * (TEXT_WIDTH + extraTitleWidth), TITLE_Y, TEXT_WIDTH \
		+ extraTitleWidth, TEXT_HEIGHT + extraTitleHeight}; // make title larger, centered
	SDL_RenderCopy(gRenderer, titleTexture, NULL, &titleRect);
	SDL_DestroyTexture(titleTexture);

	SDL_Texture *coinTexture = renderText("Coins: " + toString(total_points));
	SDL_Rect coinsRect {COIN_X, COIN_Y, TEXT_WIDTH, TEXT_HEIGHT};
	SDL_RenderCopy(gRenderer, coinTexture, NULL, &coinsRect);
	SDL_DestroyTexture(coinTexture);

	SDL_Texture *livesTexture = renderText("Lives: " + toString(lives));
	SDL_Rect livesRect {LIVES_X, LIVES_Y, TEXT_WIDTH, TEXT_HEIGHT};
	SDL_RenderCopy(gRenderer, livesTexture, NULL, &livesRect);
	SDL_DestroyTexture(livesTexture);

	SDL_Texture *waveTexture = renderText("Wave: " + toString(wave));
	SDL_Rect waveRect {WAVE_X, WAVE_Y, TEXT_WIDTH, TEXT_HEIGHT};
	SDL_RenderCopy(gRenderer, waveTexture, NULL, &waveRect);
	SDL_DestroyTexture(waveTexture);
}

// given a string with delimiter delim, returns a vector of the chars in the string
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    vector<string> elems;
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// converts an int to a string and returns it
string toString(int num) {
	ostringstream numAsString ;
	numAsString << num ;
    return numAsString.str() ;
}

/* Return an SDL_Rect with an SDL_Surface as the background
 * Method assumes a square image is most ideal, as long as it is not too distorted
 * Returns an SDL_Rect that has no more than the maximum threshold of distortion
 * x and y are the coordinates of the position of the top of the SDL_Rect
*/
SDL_Rect getRect(SDL_Texture* texture, int maxDimension, int x, int y) {
	SDL_Rect container;

	// get height and width of original image
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	double textureWidth = width;
	double textureHeight = height;

	if(textureHeight > textureWidth) {					// height = maxDimesion. Distort up to MAX_DISTORTION
		double factor = textureHeight / maxDimension;	// scaling factor to reduce height by
		textureHeight = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (textureWidth / factor / maxDimension) > MAX_DISTORTION) { 
			textureWidth = textureWidth / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			textureWidth = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
		
	} else {											// width = maxDimension. Distort height as necessary
		double factor = textureWidth / maxDimension;	// scaling factor to reduce height by
		textureWidth = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (textureHeight / factor / maxDimension) > MAX_DISTORTION) { 
			textureHeight = textureHeight / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			textureHeight = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
	}
	container.x = (int)(x - (.5 * textureWidth));
	container.y = (int)(y - (.5 * textureHeight));			
	container.w = (int)textureWidth;
	container.h = (int)textureHeight;

	return container;
}

/* Load call loadTexture for each image
*/
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gBackground = loadTexture("img/towerDefenseBackground.bmp");
	gYouWin = loadTexture("img/YouWin.bmp");
	gYouLose = loadTexture("img/YouLose.bmp");

	if(gBackground==NULL || gYouWin==NULL || gYouLose==NULL)
	{
		printf( "Failed to a load background texture image!\n" );
		success = false;
	}

	return success;
}

/* Return an SDL_Texture for the specified image, print errors appropriately
*/
SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

/* Deallocate memory
*/
void close()
{
	//Free loaded image
	SDL_DestroyTexture( gBackground );
	SDL_DestroyTexture( gYouWin );
	SDL_DestroyTexture( gYouLose );
	gBackground = NULL;
	gYouWin = NULL;
	gYouLose = NULL;
	for(int i = 0; i < towers.size(); i++) {	// delete all Towers (living in the heap)
		delete towers[i];
	}
	for(int i = 0; i < towerSpaces.size(); i++) {	// delete all TowerSpaces in the heap
		delete towerSpaces[i];
	}
	for(int i = 0; i < enemies.size(); i++) {	// delete all enemies in the heap
		delete enemies[i];
	}

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	TTF_CloseFont( gFont );
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

/* Initialize SDL and SDL_image
*/
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Tower Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 //Initialize SDL_ttf
				if( TTF_Init() != 0 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				//Open the font
				gFont = TTF_OpenFont(fontFile.c_str(), 28 );
				if( gFont == NULL )
				{
					printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				textColor = { 0, 0, 0 };	// set font color
			}
		}
	}

	return success;
}

/**
* Render the message we want to display to a texture for drawing
* message is the text that should be displayed in the texture that is returned
* @return An SDL_Texture containing the rendered message, or NULL if something went wrong
*/
SDL_Texture* renderText(const std::string &message)
{	
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Solid( gFont, message.c_str(), textColor );
	//SDL_Surface *surf = TTF_RenderText_Blended(gFont, message.c_str(), color);
	if (surf == NULL){
		cout << "Error creating TTF surface" << endl;
		return NULL;
	}
	//Get image dimensions
	TEXT_WIDTH = surf->w;
	TEXT_HEIGHT = surf->h;
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surf);
	if (texture == NULL){
		cout << "Error converting TTF surface to texture" << endl;
	}
	//Clean up the surface
	SDL_FreeSurface(surf);
	return texture;
}