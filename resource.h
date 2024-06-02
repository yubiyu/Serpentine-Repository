#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro_physfs.h>
#include <physfs.h>

#include "segment.h"

struct Resource
{
    static ALLEGRO_FONT *builtin8;

    static ALLEGRO_BITMAP *genericTitlePng;
    static ALLEGRO_BITMAP *genericOverworldPng;
    static ALLEGRO_BITMAP *genericResultsPng;
    static ALLEGRO_BITMAP *genericBeingPng;
    static ALLEGRO_BITMAP *genericTilePng;
    static ALLEGRO_BITMAP *serpentSegmentPng[Segment::SEGMENT_CLASS_MARKER_END+1];
    static ALLEGRO_BITMAP *serpentKeyLightsPng[3];
    static ALLEGRO_BITMAP *serpentGenericLightsPng[2];
    static ALLEGRO_BITMAP *foregroundStarPng[2];
    static ALLEGRO_BITMAP *centralStarPng[2];
    static ALLEGRO_BITMAP *backgroundStarPng[2];
    static ALLEGRO_BITMAP *farBackgroundStarPng[2];
    static ALLEGRO_BITMAP *gravitonPng;
    static ALLEGRO_BITMAP *selectorCirclePng;
    static ALLEGRO_BITMAP *propulsionButtonPng[2];
    static ALLEGRO_BITMAP *repairButtonPng[2];
    static ALLEGRO_BITMAP *alertnessButtonPng[2];

    static ALLEGRO_SAMPLE *genericBgmMp3;
    static ALLEGRO_SAMPLE_INSTANCE *genericBgmSampleInstance;
    static ALLEGRO_SAMPLE *genericPickupCoinWav;
    static ALLEGRO_SAMPLE_INSTANCE *genericPickupCoinSampleInstance;
    static ALLEGRO_SAMPLE *genericClickWav;
    static ALLEGRO_SAMPLE_INSTANCE *genericClickSampleInstance;
    static ALLEGRO_SAMPLE *genericLaserShootWav;
    static ALLEGRO_SAMPLE_INSTANCE *genericLaserShootSampleInstance;

    static ALLEGRO_SAMPLE *starryWalkMp3;
    static ALLEGRO_SAMPLE_INSTANCE *starryWalkSampleInstance;

    static bool Initialize(char **argv);
    static void Uninitialize();

private:
    static void LoadFontResources();
    static void LoadImageResources();
    static void LoadAudioResources();

    static void UnloadFontResources();
    static void UnloadImageResources();
    static void UnloadAudioResources();
};

#endif // RESOURCE_H_INCLUDED
