#ifndef WINDOW_INSTANCE_H
#define WINDOW_INSTANCE_H

#include "Text.h"

class Window_instance
{
    public:
        void init(int window_x, int window_y, std::string Name);
        void update(Input *inputs);
        void draw();

        void destory();

        bool is_window_init();

    private:
        //basic stuff
        SDL_Window* _window = NULL;
        SDL_Surface* _main_surface = NULL;
        SDL_Renderer* Ren0 = NULL;
        SDL_Texture* Tex0 = NULL;

        bool I_keyLock = true;

        bool window_inited = false;

        std::string Window_name = "TESTING WINDOW";
        int Window_Height = 660;
        int Window_Width = 320;

        int Window_XPOS = 720;
        int Window_YPOS = 200;




};

#endif // WINDOW_INSTANCE_H
