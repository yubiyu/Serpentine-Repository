#include "palette.h"

ALLEGRO_COLOR Palette::COL_WHITESPACE;
ALLEGRO_COLOR Palette::COL_NYX8[8];
ALLEGRO_COLOR Palette::COL_OIL6[6];

ALLEGRO_COLOR Palette::currentClearColour;
ALLEGRO_COLOR Palette::transparentColour;

void Palette::Initialize()
{
    COL_WHITESPACE = al_map_rgb( 255, 255, 255);

    COL_NYX8[0] =  al_map_rgb(  8,  20,  30);
    COL_NYX8[1] =  al_map_rgb( 15,  42,  63);
    COL_NYX8[2] =  al_map_rgb( 32,  57,  79);
    COL_NYX8[3] =  al_map_rgb(246, 214, 189);
    COL_NYX8[4] =  al_map_rgb(195, 163, 138);
    COL_NYX8[5] =  al_map_rgb(153, 117, 119);
    COL_NYX8[6] =  al_map_rgb(129,  98, 113);
    COL_NYX8[7] =  al_map_rgb( 78,  73,  95);

    COL_OIL6[0] = al_map_rgb(251, 241, 239); // Bright Space
    COL_OIL6[1] = al_map_rgb(242, 211, 171); // Bright Light
    COL_OIL6[2] = al_map_rgb(198, 159, 165); // Bright Shadow
    COL_OIL6[3] = al_map_rgb(139, 109, 156); // Dark Light
    COL_OIL6[4] = al_map_rgb( 73,  77, 126); // Dark Shadow
    COL_OIL6[5] = al_map_rgb( 39,  39,  68); // Dark Space

    currentClearColour = COLKEY_BACKGROUND;
    transparentColour = al_map_rgba(0,0,0,0);

}
