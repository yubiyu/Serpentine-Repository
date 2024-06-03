#include "palette.h"

ALLEGRO_COLOR Palette::COL_WHITESPACE;
ALLEGRO_COLOR Palette::COL_NYX8[8];
ALLEGRO_COLOR Palette::COL_OIL6[6];
//ALLEGRO_COLOR Palette::SERPENT_OUTER_COLOURS[20];
//ALLEGRO_COLOR Palette::SERPENT_INNER_COLOURS[20];

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

/*
    SERPENT_OUTER_COLOURS[0] = al_map_rgb(208,23,22);
    SERPENT_OUTER_COLOURS[1] = al_map_rgb(194,24,91);
    SERPENT_OUTER_COLOURS[2] = al_map_rgb(123,31,162);
    SERPENT_OUTER_COLOURS[3] = al_map_rgb(81,45,168);
    SERPENT_OUTER_COLOURS[4] = al_map_rgb(48,63,159);
    SERPENT_OUTER_COLOURS[5] = al_map_rgb(69,94,222);
    SERPENT_OUTER_COLOURS[6] = al_map_rgb(2,136,209);
    SERPENT_OUTER_COLOURS[7] = al_map_rgb(0,151,167);
    SERPENT_OUTER_COLOURS[8] = al_map_rgb(0,121,107);
    SERPENT_OUTER_COLOURS[9] = al_map_rgb(10,126,7);
    SERPENT_OUTER_COLOURS[10] = al_map_rgb(104,159,56);
    SERPENT_OUTER_COLOURS[11] = al_map_rgb(175,180,43);
    SERPENT_OUTER_COLOURS[12] = al_map_rgb(251,192,45);
    SERPENT_OUTER_COLOURS[13] = al_map_rgb(255,160,0);
    SERPENT_OUTER_COLOURS[14] = al_map_rgb(245,124,0);
    SERPENT_OUTER_COLOURS[15] = al_map_rgb(230,74,25);
    SERPENT_OUTER_COLOURS[16] = al_map_rgb(93,64,55);
    SERPENT_OUTER_COLOURS[17] = al_map_rgb(97,97,97);
    SERPENT_OUTER_COLOURS[18] = al_map_rgb(69,90,100);
    SERPENT_OUTER_COLOURS[19] = al_map_rgb(0,0,0);

    SERPENT_INNER_COLOURS[0] = al_map_rgb(243,108,96);
    SERPENT_INNER_COLOURS[1] = al_map_rgb(240,98,146);
    SERPENT_INNER_COLOURS[2] = al_map_rgb(186,104,200);
    SERPENT_INNER_COLOURS[3] = al_map_rgb(149,117,205);
    SERPENT_INNER_COLOURS[4] = al_map_rgb(121,134,203);
    SERPENT_INNER_COLOURS[5] = al_map_rgb(145,167,255);
    SERPENT_INNER_COLOURS[6] = al_map_rgb(79,195,247);
    SERPENT_INNER_COLOURS[7] = al_map_rgb(77,208,225);
    SERPENT_INNER_COLOURS[8] = al_map_rgb(77,182,172);
    SERPENT_INNER_COLOURS[9] = al_map_rgb(66,189,65);
    SERPENT_INNER_COLOURS[10] = al_map_rgb(174,213,129);
    SERPENT_INNER_COLOURS[11] = al_map_rgb(220,231,117);
    SERPENT_INNER_COLOURS[12] = al_map_rgb(255,241,118);
    SERPENT_INNER_COLOURS[13] = al_map_rgb(255,213,79);
    SERPENT_INNER_COLOURS[14] = al_map_rgb(255,183,77);
    SERPENT_INNER_COLOURS[15] = al_map_rgb(255,138,101);
    SERPENT_INNER_COLOURS[16] = al_map_rgb(161,136,127);
    SERPENT_INNER_COLOURS[17] = al_map_rgb(244,224,224);
    SERPENT_INNER_COLOURS[18] = al_map_rgb(144,164,174);
    SERPENT_INNER_COLOURS[19] = al_map_rgb(255,255,255);
*/

    currentClearColour = COLKEY_BACKGROUND;
    transparentColour = al_map_rgba(0,0,0,0);

}
