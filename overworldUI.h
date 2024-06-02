#ifndef OVERWORLDUI_H_INCLUDED
#define OVERWORLDUI_H_INCLUDED

struct OverworldUI
{
    static const int STATS_READOUT_X = 800;
    static const int STATS_READOUT_Y = 800;

    static const int LIFE_READOUT_Y = STATS_READOUT_Y + 16*0;
    static const int SPEED_READOUT_Y = STATS_READOUT_Y + 16*1;
    static const int ACCELERATION_READOUT_Y = STATS_READOUT_Y + 16*2;
    static const int CURRENT_ENERGY_READOUT_Y = STATS_READOUT_Y + 16*3;
    static const int MAX_ENERGY_READOUT_Y = STATS_READOUT_Y + 16*4;
    static const int ENERGY_PRODUCTION_READOUT_Y = STATS_READOUT_Y + 16*5;
    static const int ENERGY_CONSUMPTION_READOUT_Y = STATS_READOUT_Y + 16*6;
};

#endif // OVERWORLDUI_H_INCLUDED
