#ifndef OVERWORLDUI_H_INCLUDED
#define OVERWORLDUI_H_INCLUDED

struct OverworldUI
{
    static const int STATS1_READOUT_X = 100;
    static const int STATS1_READOUT_Y = 750;

    static const int STATS2_READOUT_X = 375;
    static const int STATS2_READOUT_Y = 750;

    static const int STATS3_READOUT_X = 600;
    static const int STATS3_READOUT_Y = 750;

    static const int STATS4_READOUT_X = 900;
    static const int STATS4_READOUT_Y = 750;


    static const int LIFE_READOUT_Y = STATS1_READOUT_Y + 16*0;
    static const int REPAIR_SPEED_READOUT_Y = STATS1_READOUT_Y + 16*1;
    static const int REPAIR_ACCELERATION_READOUT_Y = STATS1_READOUT_Y + 16*2;
    static const int REPAIR_LOSS_READOUT_Y = STATS1_READOUT_Y + 16*3;

    static const int SPEED_READOUT_Y = STATS2_READOUT_Y + 16*0;
    static const int ACCELERATION_READOUT_Y = STATS2_READOUT_Y + 16*1;
    static const int VISCOUS_DRAG_READOUT_Y = STATS2_READOUT_Y + 16*2;
    static const int WEAR_RATE_READOUT_Y = STATS2_READOUT_Y + 16*3;

    static const int CURRENT_ENERGY_READOUT_Y = STATS3_READOUT_Y + 16*0;
    static const int MAX_ENERGY_READOUT_Y = STATS3_READOUT_Y + 16*1;
    static const int ENERGY_PRODUCTION_READOUT_Y = STATS3_READOUT_Y + 16*2;
    static const int ENERGY_CONSUMPTION_READOUT_Y = STATS3_READOUT_Y + 16*3;

    static const int BASE_ENERGY_CONSUMPTION_READOUT_Y = STATS3_READOUT_Y + 16*5;
    static const int PROPULSION_ENERGY_CONSUMPTION_READOUT_Y = STATS3_READOUT_Y +16*6;
    static const int REPAIR_ENERGY_CONSUMPTION_READOUT_Y = STATS3_READOUT_Y +16*7;
    static const int AMNETIES_ENERGY_CONSUMPTION_READOUT_Y = STATS3_READOUT_Y +16*8;


    static const int PASSENGERS_READOUT_Y = STATS4_READOUT_Y + 16*0;
    static const int AMNETIES_READOUT_Y = STATS4_READOUT_Y + 16*1;
    static const int AMNETIES_GENERATION_READOUT_Y = STATS4_READOUT_Y + 16*2;
    static const int AMNETIES_ATTENUATION_READOUT_Y = STATS4_READOUT_Y + 16*3;


};

#endif // OVERWORLDUI_H_INCLUDED
