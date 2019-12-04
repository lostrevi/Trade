#include "../include/Game.h"


static void TestThread(Input inputs)
{

}

void Game::init()
{
    srand( time(NULL));

    if(!startup())
    {
        std::cout << "[C++] Error : startup() has failed\n";
        running = false;
    }


    //The frame per second timer
    GTimer fpsTimer;

    //The frames per second cap timer
    GTimer capTimer;

    //Start counting frames
    int countedFrames = 0;
    fpsTimer.start();

    //2nd init
    init2();


    //start net
    if(MULTIPLAYER_TCP)
        net_init();


    //start other treads if needed
    if(THREAD_BASED_DRAWING)
    {
        std::cout << "Using Drawing_thread to draw frame rate should be : " << DRAW_FPS << "fps\n";
        Drawing_thread = std::thread(&Game::MT_init_draw, this);
    }
    if(THREAD_BASED_INPUTS)
    {
        std::cout << "Using Input_thread to check changes in inputs.\n";
        //Input_thread = std::thread(&Game::MT_init_input, this);
        //Input_thread = SDL_CreateThread( MT_init_input, NULL ,NULL); //not working
        //Input_thread = SDL_CreateThread( TestThread, "Input_thread", &inputs);//(void *)NULL);

        int threadReturnValue;

        if (NULL == Input_thread) {
            printf("SDL_CreateThread failed: %s\n", SDL_GetError());
        } else {
            SDL_WaitThread(Input_thread, &threadReturnValue);
            printf("Thread returned value: %d\n", threadReturnValue);
        }
    }



    while(running) //game loop
    {
        //start cap timer
        capTimer.start();

        //calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }
        //FRAME BASED UPDATES START



        if(!THREAD_BASED_DRAWING)
            draw();
        if(!THREAD_BASED_INPUTS)
        {
            inputs.update();
            running = inputs.Quit();
        }



        update();

        //FRAME BASED UPDATES END

        //if frame finished early
        int frameTicks = capTimer.getTicks();
        if ( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            //wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }

    }

    //clean up
    close();

}

void Game::init2()
{
    //testing
    noise_master.make_map(SCREEN_WIDTH - (SCREEN_WIDTH/6) ,SCREEN_HEIGHT,"Stone", 0.6);
    noise_master.make_map(SCREEN_WIDTH - (SCREEN_WIDTH/6) ,SCREEN_HEIGHT,"Wood", 0);
    noise_master.make_map(SCREEN_WIDTH - (SCREEN_WIDTH/6) ,SCREEN_HEIGHT,"Soil", 0);
    //noise_master.change_map_draw("Stone");

    Info_bar = { (SCREEN_WIDTH/6) * 5, 0, SCREEN_WIDTH/6, SCREEN_HEIGHT};

    Large_font = TTF_OpenFont("Data/Font.ttf", 18); //this opens a font style and sets a size
    Small_font = TTF_OpenFont("Data/Font.ttf", 12); //this opens a font style and sets a size

    if(Large_font == NULL)
        std::cout << "[c++] error: the TTF Font Large_font did not load. Data\\Front.ttf\n";
    if(Small_font == NULL)
        std::cout << "[c++] error: the TTF Font Small_font did not load. Data\\Front.ttf\n";

    test_text.init(Large_font,Ren0);


}

void Game::update()
{
    //debug keys (most of these will find there way in but for now this how they are)
    if(D_timer == D_time_max)
    {
        if(inputs.NUM1ispressed() && noise_master.get_currentmap_target() != "Stone")
        {
            std::cout << "View Stone map\n";
            noise_master.change_map_draw("Stone");
            D_timer = 0;
        }
        else if(inputs.NUM2ispressed() && noise_master.get_currentmap_target() != "Wood")
        {
            std::cout << "View Wood map\n";
            noise_master.change_map_draw("Wood");
            D_timer = 0;
        }
        else if(inputs.NUM3ispressed() && noise_master.get_currentmap_target() != "Soil")
        {
            std::cout << "View Soil map\n";
            noise_master.change_map_draw("Soil");
            D_timer = 0;
        }

        else if(inputs.Iispressed() && !Info_window.is_window_init() && !lockinfowindowkey)
        {
            std::cout << "Loading test window\n";
            Info_window.init(330,660,"Info Window ( Hot Key: I )");
            lockinfowindowkey = true;
        }
        else if(!inputs.Iispressed() && Info_window.is_window_init() && lockinfowindowkey)
        {
            lockinfowindowkey = false;
        }

        else if(inputs.Tispressed())
        {
            //use for other debug or something else
            std::cout << "Key does nothing at the moment.\n";
            D_timer = 0;
        }

    }
    else
        D_timer++;


            //text testing

        SDL_Rect TEMP2;
        TEMP2.x = 0;
        TEMP2.y = 0;
        TEMP2.w = 10;
        TEMP2.h = 10;

        std::string str2 = "info : " + To_string(D_timer);

        test_text.update(str2,TEMP2); // since drawing hapens on it's own thread this must be done in the drawing thread to have text work.



        //Other Windows
        if(Info_window.is_window_init())
            Info_window.update(&inputs);

}

void Game::draw()
{
    //Clear screen
    SDL_SetRenderDrawColor( Ren0, 29, 30, 34, 0xFF );
    SDL_RenderClear( Ren0 );




    //DRAW//
        noise_master.draw_map(Ren0);




        //UI DRAW
        SDL_SetRenderDrawColor(Ren0, 100,100,100,0xff);
        SDL_RenderFillRect(Ren0,&Info_bar);
        SDL_SetRenderDrawColor( Ren0, 29, 30, 34, 0xFF );


        //testing text
        test_text.draw();


        //Other Windows
        if(Info_window.is_window_init())
            Info_window.draw();


    //DRAW//

    SDL_RenderPresent( Ren0 );

}


bool Game::get_running()
{
    return running;
}









//Multithreading junk

void Game::MT_init_input() //SDL funtion must be int
{

    //The frame per second timer
    GTimer fpsTimer;

    //The frames per second cap timer
    GTimer capTimer;

    //Start counting frames
    int countedFrames = 0;
    fpsTimer.start();

    while(running) //game loop
    {
        //start cap timer
        capTimer.start();

        //calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }
        //FRAME BASED UPDATES START

        inputs.update();
        running = inputs.Quit();

        //TEST.update();
        //running = TEST.Quit();

        //FRAME BASED UPDATES END

        //if frame finished early
        int frameTicks = capTimer.getTicks();
        if ( frameTicks < INPUT_TICKS_PER_FARME )
        {
            //wait remaining time
            SDL_Delay( INPUT_TICKS_PER_FARME - frameTicks );
        }

    }
}

void Game::MT_init_draw()
{
    //The frame per second timer
    GTimer fpsTimer;

    //The frames per second cap timer
    GTimer capTimer;

    //Start counting frames
    int countedFrames = 0;
    fpsTimer.start();

    while(running) //game loop
    {
        //start cap timer
        capTimer.start();

        //calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }
        //FRAME BASED UPDATES START

        draw();

        //FRAME BASED UPDATES END

        //if frame finished early
        int frameTicks = capTimer.getTicks();
        if ( frameTicks < DRAW_TICKS_PER_FRAME )
        {
            //wait remaining time
            SDL_Delay( DRAW_TICKS_PER_FRAME - frameTicks );
        }

    }
}






















//Net stuff (Might set up to run an another tread one it works)
void Game::send_connection_Info(Net_Info n_info)
{
    net_info = n_info;
}

void Game::net_init()
{
    if(net_info.primed)
    {
        std::cout << "Net data is primed running net data\n";

        //yeah i could have used done this a bit cleaner but this is ok for now.
        if(net_info.server)
            server_init();
        else if(net_info.client)
            client_init();
    }
}
void Game::server_init()
{
    //IPaddress ipAddress;
    // This sets the IPaddress up with the correct values.
    // Since we want to listen for connection, we set the IP parameter to null
    // This will set the ip in ipAddress to INADDR_NONE
    int success = SDLNet_ResolveHost( &ipAddress, nullptr, net_info.port );

    if ( success == -1 )
    {
        std::cout << "Failed to open port : " << net_info.port << std::endl;
        //return false;
    }

    // Remember : ipAddress has the IP set to INADDR_NONE,
    // so now we'll listen for new connections on 'port'
    server = SDLNet_TCP_Open( &ipAddress );

    if ( server == nullptr )
    {
        std::cout << "Failed to open port for listening : " << net_info.port
            <<" \n\tError : " << SDLNet_GetError()
            << std::endl;
        //return false;
    }

    //Create connection
    bool done = false;



    while(!done)
    {
      /* try to accept a connection */
      client = SDLNet_TCP_Accept(server);
      if (!client) { /* no connection accepted */
        /*printf("SDLNet_TCP_Accept: %s\n",SDLNet_GetError()); */
        SDL_Delay(100); /*sleep 1/10th of a second */
        continue;
      }

      /* get the clients IP and port number */
      IPaddress *remoteip;
      remoteip = SDLNet_TCP_GetPeerAddress(client);
      if (!remoteip) {
        printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
        continue;
      }

      /* print out the clients IP and port number */
      Uint32 ipaddr;
      ipaddr = SDL_SwapBE32(remoteip->host);
      printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
             (ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
             remoteip->port);


         //////////////////////////////////////TESTING////////////////////////////////////////////////
                bool Message_Grab = false;
               while (!Message_Grab)
                {
                    /* read the buffer from client */
                    char message[1024];
                    int len = SDLNet_TCP_Recv(client, message, 1024);
                    if (!len) {
                      printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
                      break;
                    }
                    /* print out the message */
                    printf("Received: %.*s\n", len, message);


                    if(client == nullptr)
                    {
                        std::cout << "Client has disconnected!\n";
                    }
                }
         //////////////////////////////////////TESTING////////////////////////////////////////////////

 }







}
void Game::client_init()
{
    // Since this is the client connection, we supply the ip of the server
    // In this case, 127.0.0.1 which basically means "this computer"
    //IPaddress ipAddress;

    // This sets the IPaddress so we can try to connect to the server in the next step
    int success = SDLNet_ResolveHost( &ipAddress, net_info.ipAddress.c_str(), net_info.port );

    if ( success == -1 )
    {
        std::cout << "Failed to open port : " << net_info.port << std::endl;
        //return false;
    }



    // Try to open a connection to the server
    tcpSocket = SDLNet_TCP_Open( &ipAddress );

    if ( tcpSocket == nullptr )
    {
        std::cout << "Failed to connect to port : " << net_info.port
            <<" \n\tError : " << SDLNet_GetError()
            << std::endl;
        //return false;
    }
    else
    {
        std::cout << "Connected to server! \n";


        //S////////////////////////////////////TESTING/////////////////////////////////////////////S//

        //send data just for the sake of it



          char message[1024];

            //fgets(message, 1024, stdin);

          std::string str_message = "[Client saying Hello to Server] ";
          for(int i = 0; i < 1024; i++ )
          {
              message[i] = str_message[i];
          }

            std::cout << "Delaying 3000 ...";
            SDL_Delay(3000);
            std::cout << " done\n";


          int len = strlen(message);

          /* strip the newline */
          //message[len - 1] = '\0';

          if (len) {
            int result;

            /* print out the message */
            printf("Sending: %.*s\n", len, message);

            result = SDLNet_TCP_Send(tcpSocket, message, len); /* add 1 for the NULL */
            if (result < len)
              printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
          }



        //E////////////////////////////////////TESTING/////////////////////////////////////////////E//


    }
}



///////////////////MORE NET STUFF//////////////////////////////////////

void Game::send_message(std::string Message) //sends to server if client or sends to all if server (only one connection can be used at the moment)
{
    if(net_info.server)//for server send to all clients. ONLY ONE CLIENT IS SUPPORTED AT THE MOMMENT (i'll try to add more after this is setup)
    {

    }
    else //for client send to server
    {
        char message[1024];
        Message = Message + "X"; //if i get rid of the strip the newline then it will be all set.
        for(int i = 0; i < Message.length(); i++ )
        {
            message[i] = Message[i];
        }
        int len = strlen(message);

        /* strip the newline */
        message[len - 1] = '\0'; // don't know what this is but i'll leave it in for now

        if (len)
        {
            int result;

            /* print out the message */
            printf("Sending: %.*s\n", len, message);

            result = SDLNet_TCP_Send(tcpSocket, message, len); /* add 1 for the NULL */
            if (result < len)
              printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        }
    }
}
void Game::server_receive_data() //will just cout for now (thread later)
{

}
void Game::client_receive_data() //will just cout for now (thread later)
{

}







