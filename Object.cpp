#include "Object.h"
#include <iostream>
using namespace std;

Object::Object(SDL_Renderer** gRendererPtr)
{
    MAX_DIMENSION = 60;
    MAX_DISTORTION = .57;       // decimal of max percentage
    gRenderer = gRendererPtr;

}
 

/* Return an SDL_Rect with an SDL_Surface as the background
 * Method assumes a square image is most ideal, as long as it is not too distorted
 * Returns an SDL_Rect that has no more than the maximum threshold of distortion
 * x and y are the coordinates of the position of the top of the SDL_Rect
*/
SDL_Rect Object::getRect(SDL_Texture* texture, int maxDimension, int x, int y) {
    SDL_Rect container;

    // get height and width of original image
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    double textureWidth = width;
    double textureHeight = height;

    if(textureHeight > textureWidth) {                  // height = maxDimesion. Distort up to MAX_DISTORTION
        double factor = textureHeight / maxDimension;   // scaling factor to reduce height by
        textureHeight = maxDimension;                   // height cannot exceed max dimension
        // check if factor will cause width to exceed MAX_DISTORTION            
        if(1 - (textureWidth / factor / maxDimension) > MAX_DISTORTION) { 
            textureWidth = textureWidth / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
        } else {
            textureWidth = maxDimension;    // safe because width won't exceed MAX_DISTORTION threshold
        }
        container.x = (int)(x - (.5 * maxDimension) + (.5*(maxDimension - textureWidth)));
        container.y = (int)(y - (.5 * textureHeight));          
        
        
    } else {                                            // width = maxDimension. Distort height as necessary
        double factor = textureWidth / maxDimension;    // scaling factor to reduce height by
        textureWidth = maxDimension;                    // height cannot exceed max dimension
        // check if factor will cause width to exceed MAX_DISTORTION            
        if(1 - (textureHeight / factor / maxDimension) > MAX_DISTORTION) { 
            textureHeight = textureHeight / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
        } else {
            textureHeight = maxDimension;   // safe because width won't exceed MAX_DISTORTION threshold
        }
        container.x = (int)(x - (.5 * textureWidth));
        container.y = (int)(y - (.5 * maxDimension) + (.5*(maxDimension - textureHeight)));
    }
    container.w = (int)textureWidth;
    container.h = (int)textureHeight;

    return container;
}

/* Return an SDL_Texture for the specified image, print errors appropriately
*/
SDL_Texture* Object::loadTexture( std::string path )
{
    SDL_Texture* newTexture = NULL; //The final texture

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( *gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}