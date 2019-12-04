#ifndef TEXT_H
#define TEXT_H

#include "Noise_map.h"


class Text
{
    public:
        void init(TTF_Font* font, SDL_Renderer *renA, Uint32 Width_table_size);
        void init(TTF_Font* font, SDL_Renderer *renA) {Font = font; RenA = renA;}
        void update(std::string message, SDL_Rect Location);
        void update(std::string message);
        void draw();


    private:
        TTF_Font* Font; //this should be loaded from a parent object not each time Text is inited
        SDL_Renderer *RenA;
        SDL_Surface *surfaceMessage;
        SDL_Texture* Message_T;
        SDL_Rect Message_rect;

        std::string Message_mem = "";

        Uint32 width_tabe_size = 300;

        //Text_colors
        SDL_Color White = {255, 255, 255};
        SDL_Color Black = {0, 0, 0};
        SDL_Color Red = {255, 0, 0};

        bool Text_is_shit_debug_mode = true;

        bool Change_text = false;

};

//This always updates where the Text class will only update if the text changes.
/*
static void render_text(
    SDL_Renderer *renderer,
    int x,
    int y,
    const char *text,
    TTF_Font *font,
    SDL_Rect *rect,
    SDL_Color color
) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Blended(font, text, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;
    // This is wasteful for textures that stay the same.
    // But makes things less stateful and easier to use.
    // Not going to code an atlas solution here... are we?
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);

}
*/

#endif // TEXT_H
