#ifndef HEADER_FILE_H
#define HEADER_FILE_H


#define _WIN32_WINNT 0x0A00

//This is a stop to dump the headers and includes all in one place. bla bla bla bla bla
#include "SDL.h"
#include "SDL_image.h";
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include "Mingw/mingw.thread.h"
#include <functional>
#include "SDL_thread.h"

extern "C"
{
    #include "../LUA535/include/lua.h"
    #include "../LUA535/include/lauxlib.h"
    #include "../LUA535/include/lualib.h"
}



static std::string To_string(int value)
{
    std::stringstream ss;
    ss << value;
    std::string output = ss.str();
    return output;
}


struct Net_Info //might need updating
{
    int port = 0;
    std::string ipAddress;
    bool primed = false;
    bool server = false;
    bool client = false;
};




static SDL_Texture* loadTexture(SDL_Renderer* RenA,std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );


    if( loadedSurface == NULL )
    {
        std::cout <<  "[ SDL_ERROR ]Unable to load image" << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( RenA, loadedSurface );
        if( newTexture == NULL )
        {
            std::cout << "[ SDL_ERROR ] Unable to create texture from" <<  path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

static bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}





#endif // HEADER_FILE_H
