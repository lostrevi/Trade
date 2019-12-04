#ifndef NOISE_MAP_H
#define NOISE_MAP_H

#include "Input.h"


struct Noise_map
{
    std::vector<double> data;
    int width, height;
    std::string resource;
    //resource will add later after perlinNoise is working for map gen.
};

class Noise_Handler
{
    public:
        void make_map(int sizeX, int sizeY, std::string resource, double cut_off);//add resource id later //set cut_off to zero to have no cut off

        void draw_map(SDL_Renderer *RenA);
        void change_map_draw(std::string target); //make_better_later like you put resource name or id later
        std::string get_currentmap_target();

    private:
        std::vector<Noise_map> maps;

        std::string type_target;

        double Cut_Off = 0;

        int map_target = -1; //this will just point to nothing

};


#endif // NOISE_MAP_H
