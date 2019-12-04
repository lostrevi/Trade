#include "Noise_map.h"

#include "ppm.h"
#include "PerlinNoise.h"

void Noise_Handler::make_map(int sizeX, int sizeY, std::string resource, double cut_off)//add resource id later
{
    // Define the size of the image
	unsigned int width = sizeX, height = sizeY;

	PerlinNoise pn(rand() % 50000000);

	Cut_Off = cut_off;

	Noise_map new_map;

	new_map.height = height;
	new_map.width = width;
	new_map.resource = resource;

	// GEN Perlin noise
	for(unsigned int i = 0; i < height; ++i) {     // y
		for(unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j/((double)width);
			double y = (double)i/((double)height);

			// Typical Perlin noise
			double n = pn.noise(5 * x, 5 * y, .8);

			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);



			if(n < Cut_Off) //setting cutt off
                n = 0;

            //std::cout << "n : " << n << "\n";


            new_map.data.push_back(n);

		}
	}

    maps.push_back(new_map);


}

void Noise_Handler::draw_map(SDL_Renderer *RenA)
{

    int offsetX = 0, offsetY = 0;

    if(map_target != -1)
    {

        for( int i = 0; i < maps[map_target].height; i++ )
        {
            for( int j = 0; j < maps[map_target].width; j++ )
            {

                int valueZ = floor(255 * maps[map_target].data[j + (maps[map_target].width *i) ] );

                //valueZ = (valueZ - 255) * -1;

                    if(maps[map_target].resource == "Stone")
                        SDL_SetRenderDrawColor( RenA, valueZ, 0, 0, 0xFF );
                    if(maps[map_target].resource == "Wood")
                        SDL_SetRenderDrawColor( RenA, 0, 0, valueZ, 0xFF );
                    if(maps[map_target].resource == "Soil")
                        SDL_SetRenderDrawColor( RenA, 0, valueZ, 0, 0xFF );

                    SDL_RenderDrawPoint(RenA,j + offsetX, i + offsetY);

            }
        }
        SDL_SetRenderDrawColor( RenA, 29, 30, 34, 0xFF );



    }
}

void Noise_Handler::change_map_draw(std::string target) //make_better_later like you put resource name or id later
{
    for(int i = 0; i < maps.size(); i++)
    {
        if(maps[i].resource == target)
        {
            type_target = target;
            map_target = i;
            break;
        }

    }
}

std::string Noise_Handler::get_currentmap_target()
{
    return type_target;
}

























