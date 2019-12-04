
#include "include/Game.h"






int main(int argc, char* argv[])
{
    //argc check
    Net_Info net_info;

    if (argc == 2 && strcmp(argv[1], "server") == 0)
    {
        if(MULTIPLAYER_TCP)
        {
            //do server stuff
            net_info.server = true;

            //std::string input = "";
            //std::cout << "\nenter ip of host (127.0.0.1) : ";
            //std::cin >> input;
            //net_info.ipAddress = input.c_str();

            std::cout << "\nenter port (12312) : ";
            int value = 0;
            std::cin >> value;
            net_info.port = value;

            net_info.primed = true;
        }
        else
        {
            std::cout << "This feature is disabled. Check game.h and change that MULTIPLAYER_TCP to true. This might change with updates.\n";
        }
    }
    else if (argc == 2 && strcmp(argv[1], "client") == 0)
    {
        if(MULTIPLAYER_TCP)
        {
            //do server stuff
            net_info.client = true;
            std::string input = "";

            std::cout << "\nenter ip of host (127.0.0.1) : ";
            std::cin >> input;
            net_info.ipAddress = input.c_str();

            std::cout << "\nenter port (12312) : ";
            int value = 0;
            std::cin >> value;
            net_info.port = value;

            net_info.primed = true;
        }
        else
        {
            std::cout << "This feature is disabled. Check game.h and change that MULTIPLAYER_TCP to true. This might change with updates.\n";
        }
    }
    else if (argc == 2)
    {
        std::cout << "No a valid argc. Try\n";
        std::cout << "server - run as server (MULTIPLAYER_TCP must be enabled)\n";
        std::cout << "client - run as client (MULTIPLAYER_TCP must be enabled)\n";
    }



    std::cout << "Starting the main object\n";

    Game Game_master;

    if(MULTIPLAYER_TCP)
        Game_master.send_connection_Info(net_info);

    Game_master.init();

    return 0;
}

