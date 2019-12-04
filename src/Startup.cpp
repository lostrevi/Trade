#include "../include/Game.h"

bool Game::startup() //returns true if it worked
{

    //starts all the SDL Stuff and makes a window.

    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "[SDL ERROR] Could not init : " << SDL_GetError() << "\n";
        success = false;
    }
    else
    {
        //create window
        _main_window = SDL_CreateWindow( NAME_OF_APP.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( _main_window == NULL )
        {
            std::cout << "[SDL ERROR] Could not create window : " << SDL_GetError() << "\n";
            success = false;
        }
        else
        {
            //Get window surface
            _main_surface = SDL_GetWindowSurface( _main_window );
        }
    }

    //create renderer
    Ren0 = SDL_CreateRenderer(_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Ren0 == NULL){
        SDL_DestroyWindow(_main_window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

        //Initialize renderer color
        SDL_SetRenderDrawColor( Ren0, 0xFF, 0xFF, 0xFF, 0xFF );


    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        std::cout <<  "[SDL ERROR] SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }


    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        std::cout << "[SDL ERROR] SDL_image could not initialize! SDL_image Error: " <<  IMG_GetError() << std::endl;
    }



    if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "ER: SDL_Init: %s\n", SDL_GetError());
        return false;
    }

    if(SDLNet_Init() == -1) {
        fprintf(stderr, "ER: SDLNet_Init: %s\n", SDLNet_GetError());
        return false;
    }



    return success;

}












///close stuff is here
void Game::close()
{
    //Deallocate surface
    //SDL_FreeSurface( _main_surface );
    //then set null

    //Rejoin thread. this might be the wrong spot to do this.
    if(THREAD_BASED_DRAWING)
    {
        std::cout << "Trying to get the Drawing_thread to rejoin ....";
        Drawing_thread.join();
        std::cout << "... Done\n";
    }
    if(THREAD_BASED_INPUTS)
    {
        std::cout << "Trying to get the Input_thread to rejoin .....";
        //Input_thread.join();
        SDL_DetachThread( Input_thread );
        std::cout << "... Done\n";
    }


    //Destroy window
    _main_window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
