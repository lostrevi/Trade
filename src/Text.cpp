#include "Text.h"

void Text::init(TTF_Font* font, SDL_Renderer *renA, Uint32 Width_table_size)
{
    RenA = renA;
    Font = font;
    width_tabe_size = Width_table_size;
}



void Text::update(std::string message, SDL_Rect Location)
{
    if(Message_mem != message)
    {
        Message_mem = message;
        Message_rect = Location; //make w based on string

        Change_text = true;
    }
}

void Text::update(std::string message)
{
    if(Message_mem != message)
    {
        Message_mem = message;
        Change_text = true;
    }
}



void Text::draw()
{
    //draw has to update since draw is it's own thread
    if(Change_text)
    {

        surfaceMessage = TTF_RenderText_Blended_Wrapped(Font, Message_mem.c_str(), White, width_tabe_size); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
        if(surfaceMessage != NULL)
        Message_T = SDL_CreateTextureFromSurface(RenA, surfaceMessage); //now you can convert it into a texture

        if(surfaceMessage != NULL)
        {
            Message_rect.w = surfaceMessage->w;
            Message_rect.h = surfaceMessage->h;
        }

        if(Message_T != NULL)
            SDL_RenderCopy(RenA, Message_T, NULL, &Message_rect);

        Change_text = false;
    }
    else
    {
        if(Message_T != NULL)
            SDL_RenderCopy(RenA, Message_T, NULL, &Message_rect);
    }






}



















/*

TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

SDL_Rect Message_rect; //create a rect
Message_rect.x = 0;  //controls the rect's x coordinate
Message_rect.y = 0; // controls the rect's y coordinte
Message_rect.w = 100; // controls the width of the rect
Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

//Don't forget too free your surface and texture

*/
