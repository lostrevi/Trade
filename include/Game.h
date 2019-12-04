#ifndef GAME_H
#define GAME_H

#include "Window_instance.h"

//features
const static bool MULTIPLAYER_TCP = false; //turn this on to enable multiplayer via TCP


const static int SCREEN_HEIGHT = 480;
const static int SCREEN_WIDTH = 720;
const static std::string NAME_OF_APP = "Trade 0.0.0a";
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int DRAW_FPS = 60; //this is only for muti draw// also there not much point of having a thread
const int DRAW_TICKS_PER_FRAME = 1000 / DRAW_FPS;    // since if its set to 60 but the game updates 30 it just draws the same thing twice.
const int INPUT_FPS = 60;
const int INPUT_TICKS_PER_FARME = 1000 / INPUT_FPS;

const static bool THREAD_BASED_DRAWING = true; //this will have use multi_T_draw() and not run draw.
const static bool THREAD_BASED_INPUTS = false; //this will use Thread based inputs. //need to fix


class Game
{
    public:
        bool startup(); //This is for SDL modulates and such

        void init(); //this gets every thing up and running
        void init2(); //for other objects
        void update();
        void draw();


        void net_init();
        void server_init();
        void client_init();
        void send_connection_Info(Net_Info n_info);

        void send_message(std::string Message); //sends to server if client or sends to all if server (only one connection can be used at the moment)

        void server_receive_data(); //will just cout for now
        void client_receive_data(); //will just cout for now


        //Multithreading junk
        void MT_init_draw(); //this just uses draw
        void MT_init_input(); //this just uses input.update to keep it of the logic thread.
        //for what ever reason input thread will stop updating

        void testing(); // is is for testing and should be removed one done

        void close();

        bool get_running();

        Input* get_Input()
        {
            return &inputs;
        }

    private:
        SDL_Window* _main_window = NULL;
        SDL_Renderer* Ren0 = NULL;
        SDL_Texture* Tex0 = NULL;
        SDL_Surface* _main_surface = NULL;

        Input inputs;

        bool running = true;

        bool lockinfowindowkey = false;

        SDL_Surface* _test1_surface = NULL;


        Net_Info net_info;


        //Noise Map stuff used for resources
        Noise_Handler noise_master;


        //UI stuff
        SDL_Rect Info_bar;


        //Other Window Instance
        Window_instance Info_window;



        //testing

        Text test_text;

        //Fonts
        TTF_Font* Large_font;
        TTF_Font* Small_font;



        //temp most likely
        int D_timer = 0;
        int D_time_max = 8;


        //Threads
            //This thread is olny used if this is true TREAD_BASED_DRAWING
         std::thread Drawing_thread;
         //std::thread* Input_thread = NULL;
         SDL_Thread *Input_thread = NULL;


         //net Objects (Yeah i'm thinking to make it just part of game cuz i seem to have better luck with mutily threading)
         IPaddress ipAddress;
         TCPsocket tcpSocket;
         TCPsocket client; //will need more of these if i want the server to handle more connections
         TCPsocket server;


};

#endif // GAME_H
