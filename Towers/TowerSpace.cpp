/* Jack Ryan
 * CSE 20212
 * FC Project
 * TowerSpace.cpp
 * implementation for TowerSpace base class
*/
#include "TowerSpace.h"

TowerSpace::TowerSpace(SDL_Renderer** gRendererPtr, vector<TowerSpace*> *towerSpacesTemp, \
	vector<Tower*> *towersTemp, vector<Enemy*> *enemiesTemp, double xpos, double ypos) : Object(gRendererPtr)
{
	towerX = xpos;
	towerY = ypos;
	TOWER_MAX_DIMENSION = 70;
	gRenderer = gRendererPtr;
	towerSpaces = towerSpacesTemp;
	towers = towersTemp;
	enemies = enemiesTemp;

	towerTexture = loadTexture("img/TowerSymbol.png");
	towerRect = getRect(towerTexture, TOWER_MAX_DIMENSION, towerX, towerY);
	SDL_RenderCopy(*gRenderer, towerTexture, NULL, &towerRect);
	
	// initialize timing to prevent being spammed with the same error message
	errorWait = 1500; // wait 1/4 of a second
	gettimeofday(&timeStruct, NULL);	// get current time of day
	lastErrorTime = (timeStruct.tv_sec * 1000 + timeStruct.tv_usec / 1000) - errorWait;   // will make errorMessage available immediately

	// set cost for each type of tower
    WizardCost = 80;
    ArcherCost = 100;
    CannonCost = 120;
    FreezeCost = 150;	

	// create textures for each tower type
	gWizardTower = loadTexture("img/wizardTowerDetails.png");
	gArcherTower = loadTexture("img/archerTowerDetails.png");
	gCannonTower = loadTexture("img/cannonTowerDetails.png");
	gFreezeTower = loadTexture("img/freezeTowerDetails.png");
	
	//create rects for each image
	createRects();
}

// delete allocated memory
TowerSpace::~TowerSpace() {
	
	SDL_DestroyTexture(towerTexture);
	SDL_DestroyTexture(gArcherTower);
	SDL_DestroyTexture(gCannonTower);
	SDL_DestroyTexture(gFreezeTower);
	SDL_DestroyTexture(gWizardTower);	
}

// redisplays/renders the TowerSpace object on the screen
void TowerSpace::render() {
	SDL_RenderCopy(*gRenderer, towerTexture, NULL, &towerRect);
}

void TowerSpace::createRects()
{
	if(towerY < 500){
		gArcherTowerRect = getSDL_Rect(gArcherTower, TOWER_MAX_DIMENSION,towerX,towerY+2*TOWER_MAX_DIMENSION );
		gWizardTowerRect = getSDL_Rect(gWizardTower, TOWER_MAX_DIMENSION,towerX,towerY+TOWER_MAX_DIMENSION );
		gCannonTowerRect = getSDL_Rect(gCannonTower, TOWER_MAX_DIMENSION,towerX,towerY+3*TOWER_MAX_DIMENSION );
		gFreezeTowerRect = getSDL_Rect(gFreezeTower, TOWER_MAX_DIMENSION,towerX,towerY+4*TOWER_MAX_DIMENSION );
	} else {
		gArcherTowerRect = getSDL_Rect(gArcherTower, TOWER_MAX_DIMENSION,towerX,towerY-2*TOWER_MAX_DIMENSION);
		gWizardTowerRect = getSDL_Rect(gWizardTower, TOWER_MAX_DIMENSION,towerX,towerY-TOWER_MAX_DIMENSION );
		gCannonTowerRect = getSDL_Rect(gCannonTower, TOWER_MAX_DIMENSION,towerX,towerY-3*TOWER_MAX_DIMENSION );
		gFreezeTowerRect = getSDL_Rect(gFreezeTower, TOWER_MAX_DIMENSION,towerX,towerY-4*TOWER_MAX_DIMENSION );
	}
}

bool TowerSpace::dispDropDown(double xclick, double yclick)
{
	if( (xclick >= towerX-35 && xclick <= towerX-35+TOWER_MAX_DIMENSION) && (yclick >= towerY-35 && yclick <= towerY-35+TOWER_MAX_DIMENSION) ){

		//open texutre on screen without rendering
		SDL_RenderCopy( *gRenderer, gWizardTower, NULL, &gWizardTowerRect);
		SDL_RenderCopy( *gRenderer, gArcherTower, NULL, &gArcherTowerRect);
		SDL_RenderCopy( *gRenderer, gCannonTower, NULL, &gCannonTowerRect);
		SDL_RenderCopy( *gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);	
		return true;	
	} else return false;
}

/* takes in an SDL_Event and utilizes a pointer to the towerSpaces vector and a pointer to the towers vector from main.cpp
 * If a valid key is pressed to create a new tower, the TowerSpace is removed, and a new Tower is created
 * and a  pointer to it is added pushed onto the towers vector
 */
bool TowerSpace::handleKeyPress(SDL_Event e, int* points)
{
	bool displayError = false;
	// adds a specific type of tower to the towers vector
	// objects are instantiated using operator new, adding the object to the HEAP
	// this means the Towers will need to be explicitely deleted later to prevent a memory leak.
	switch (e.key.keysym.sym){
		case SDLK_a:
		{
			// create a new WizardTower on the HEAP
			// this means delete MUST be called on the object later, or else there will be a memory leak
			if (*points >= ArcherCost)
			{
				ArcherTower* archer = new ArcherTower(gRenderer, enemies, towers, towerX, towerY);
            	towers->push_back(archer);
				*points -= ArcherCost;
            }
			else {
				gettimeofday(&timeStruct, NULL);	// get current time of day
				long currentTime = timeStruct.tv_sec * 1000 + timeStruct.tv_usec / 1000;
				if(currentTime - lastErrorTime >= errorWait) {
					lastErrorTime = currentTime;
					cout << "You do not have enough points to buy this tower!" << endl;
				}
				return false;
			}	
			break;
        }
		case SDLK_c:
		{
			if (*points >= CannonCost)
			{
				CannonTower* cannon = new CannonTower(gRenderer, enemies, towers, towerX, towerY);
            	towers->push_back(cannon);
				*points -= CannonCost;
			}
			else {
				gettimeofday(&timeStruct, NULL);	// get current time of day
				long currentTime = timeStruct.tv_sec * 1000 + timeStruct.tv_usec / 1000;
				if(currentTime - lastErrorTime >= errorWait) {
					lastErrorTime = currentTime;
					cout << "You do not have enough points to buy this tower!" << endl;
				}
				return false;
			}
            break;
        }
		case SDLK_f:
		{
			if (*points >= FreezeCost)
			{
				FreezeTower* freeze = new FreezeTower(gRenderer, enemies, towers, towerX, towerY);
            	towers->push_back(freeze);
				*points -= FreezeCost;
			}
			else {
				gettimeofday(&timeStruct, NULL);	// get current time of day
				long currentTime = timeStruct.tv_sec * 1000 + timeStruct.tv_usec / 1000;
				if(currentTime - lastErrorTime >= errorWait) {
					lastErrorTime = currentTime;
					cout << "You do not have enough points to buy this tower!" << endl;
				}
				return false;
			}
            break;
        }
        case SDLK_w:
		{
			if (*points >= WizardCost)
			{
				WizardTower* wiz = new WizardTower(gRenderer, enemies, towers, towerX, towerY);
				towers->push_back(wiz);
				*points -= WizardCost;
			}
			else {
				gettimeofday(&timeStruct, NULL);	// get current time of day
				long currentTime = timeStruct.tv_sec * 1000 + timeStruct.tv_usec / 1000;
				if(currentTime - lastErrorTime >= errorWait) {
					lastErrorTime = currentTime;
					cout << "You do not have enough points to buy this tower!" << endl;
				}
				return false;
			}
			break;
		}
		default:
			return false;
	}

	// if valid key was selected (a new tower was created), remove the TowerSpace
	if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_c || e.key.keysym.sym == SDLK_f) {
		//removes the specific towerSpace that was selected
		for (int i = 0; i < towerSpaces->size(); i++) {
			if ((*towerSpaces)[i] == this) {
				delete this;
				towerSpaces->erase(towerSpaces->begin() + i);
			}
		}
	}
	return true;
}

SDL_Rect TowerSpace::getSDL_Rect(SDL_Texture* texture, int height, int x, int y) {
	SDL_Rect container;
	int originalWidth, originalHeight;
	SDL_QueryTexture(texture, NULL, NULL, &originalWidth, &originalHeight);
	double scalingFactor = originalHeight / height;

  	container.x = x - .5*TOWER_MAX_DIMENSION;	// will be updated before rendered. doesn't matter what value is given
  	container.y = y - .5*TOWER_MAX_DIMENSION;
  	container.w = originalWidth / scalingFactor;
  	container.h = height;
  	return container;
}