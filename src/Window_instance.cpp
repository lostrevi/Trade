#include "Window_instance.h"

void Window_instance::init(int window_x, int window_y, std::string Name)
{
    Window_Width = window_x;
    Window_Height = window_y;
    Window_name = Name;

    window_inited = true;
    //create window
    _window = SDL_CreateWindow( Window_name.c_str(), Window_XPOS, Window_YPOS, Window_Width, Window_Height, SDL_WINDOW_SHOWN );
    if( _window == NULL )
    {
        std::cout << "[SDL ERROR] Could not create window : " << SDL_GetError() << "\n";
        window_inited = false;
    }
    else
    {
        //Get window surface
        _main_surface = SDL_GetWindowSurface( _window );
    }

    //create renderer
    Ren0 = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Ren0 == NULL){
        SDL_DestroyWindow(_window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        //SDL_Quit();
        window_inited = false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( Ren0, 0xFF, 0xFF, 0xFF, 0xFF );
    I_keyLock = true;




}

void Window_instance::update(Input *inputs )
{
    if(inputs->Iispressed() && !I_keyLock)
       destory();

    if(!inputs->Iispressed() && I_keyLock)
        I_keyLock = false;

}

void Window_instance::draw()
{
    SDL_SetRenderDrawColor( Ren0, 29, 30, 34, 0xFF );
    SDL_RenderClear( Ren0 );
    //DRAW//


    //DRAW//
    SDL_RenderPresent( Ren0 );
}


bool Window_instance::is_window_init()
{
    return window_inited;
}








void Window_instance::destory()
{
    SDL_GetWindowPosition(_window, &Window_XPOS, &Window_YPOS);

    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(Ren0);
    SDL_FreeSurface(_main_surface);
    window_inited = false;

}
















