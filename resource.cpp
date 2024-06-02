#include "resource.h"

ALLEGRO_FONT* Resource::builtin8;

ALLEGRO_BITMAP* Resource::genericTitlePng;
ALLEGRO_BITMAP* Resource::genericOverworldPng;
ALLEGRO_BITMAP* Resource::genericResultsPng;
ALLEGRO_BITMAP* Resource::genericBeingPng;
ALLEGRO_BITMAP* Resource::genericTilePng;
ALLEGRO_BITMAP* Resource::serpentSegmentPng[Segment::SEGMENT_CLASS_MARKER_END+1];
ALLEGRO_BITMAP* Resource::serpentKeyLightsPng[3];
ALLEGRO_BITMAP* Resource::serpentGenericLightsPng[2];
ALLEGRO_BITMAP* Resource::foregroundStarPng[2];
ALLEGRO_BITMAP* Resource::centralStarPng[2];
ALLEGRO_BITMAP* Resource::backgroundStarPng[2];
ALLEGRO_BITMAP* Resource::farBackgroundStarPng[2];
ALLEGRO_BITMAP* Resource::gravitonPng;
ALLEGRO_BITMAP* Resource::selectorCirclePng;
ALLEGRO_BITMAP* Resource::propulsionButtonPng[2];
ALLEGRO_BITMAP* Resource::repairButtonPng[2];
ALLEGRO_BITMAP* Resource::alertnessButtonPng[2];

ALLEGRO_SAMPLE* Resource::genericBgmMp3;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericBgmSampleInstance;
ALLEGRO_SAMPLE* Resource::genericPickupCoinWav;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericPickupCoinSampleInstance;
ALLEGRO_SAMPLE* Resource::genericClickWav;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericClickSampleInstance;
ALLEGRO_SAMPLE* Resource::genericLaserShootWav;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericLaserShootSampleInstance;
ALLEGRO_SAMPLE* Resource::starryWalkMp3;
ALLEGRO_SAMPLE_INSTANCE* Resource::starryWalkSampleInstance;

bool Resource::Initialize(char **argv)
{
    PHYSFS_init(argv[0]);
    if(!PHYSFS_mount("./data.zip", "/", 1))
    {
        assert("data.zip not found");
        return false;
    }
    al_set_physfs_file_interface();

    LoadFontResources();
    LoadImageResources();
    LoadAudioResources();

    return true;
}

void Resource::Uninitialize()
{
    UnloadFontResources();
    UnloadImageResources();
    UnloadAudioResources();

    PHYSFS_deinit();
}

void Resource::LoadFontResources()
{
    builtin8 = al_create_builtin_font();
}

void Resource::LoadImageResources()
{
    genericTitlePng = al_load_bitmap("genericTitlePng.png");
    genericOverworldPng = al_load_bitmap("genericOverworldPng.png");
    genericResultsPng = al_load_bitmap("genericResultsPng.png");
    genericBeingPng = al_load_bitmap("genericBeingPng.png");
    genericTilePng = al_load_bitmap("genericTilePng.png");

    serpentSegmentPng[Segment::SEGMENT_CLASS_HEAD] = al_load_bitmap("serpentHeadPng.png");
    serpentSegmentPng[Segment::SEGMENT_CLASS_KEY] = al_load_bitmap("serpentKeyPng.png");
    serpentKeyLightsPng[0] = al_load_bitmap("serpentKeyOneThirdChargePng.png");
    serpentKeyLightsPng[1] = al_load_bitmap("serpentKeyTwoThirdsChargePng.png");
    serpentKeyLightsPng[2] = al_load_bitmap("serpentKeyFullChargePng.png");
    serpentSegmentPng[Segment::SEGMENT_CLASS_TAIL] = al_load_bitmap("serpentTailPng.png");
    serpentSegmentPng[Segment::SEGMENT_CLASS_GENERIC] = al_load_bitmap("serpentGenericPng.png");
    serpentGenericLightsPng[0] = al_load_bitmap("serpentGenericHalfChargePng.png");
    serpentGenericLightsPng[1] = al_load_bitmap("serpentGenericFullChargePng.png");

    foregroundStarPng[0] = al_load_bitmap("foregroundStarPng.png");
    centralStarPng[0] = al_load_bitmap("centralStarPng.png");
    backgroundStarPng[0] = al_load_bitmap("backgroundStarPng.png");
    farBackgroundStarPng[0] = al_load_bitmap("farBackgroundStarPng.png");

    foregroundStarPng[1] = al_load_bitmap("foregroundStar2Png.png");
    centralStarPng[1] = al_load_bitmap("centralStar2Png.png");
    backgroundStarPng[1] = al_load_bitmap("backgroundStar2Png.png");
    farBackgroundStarPng[1] = al_load_bitmap("farBackgroundStar2Png.png");

    gravitonPng = al_load_bitmap("gravitonPng.png");
    selectorCirclePng = al_load_bitmap("selectorCirclePng.png");
    propulsionButtonPng[0] = al_load_bitmap("propulsionButtonPng.png");
    repairButtonPng[0] = al_load_bitmap("repairButtonPng.png");
    alertnessButtonPng[0] = al_load_bitmap("alertnessButtonPng.png");
    propulsionButtonPng[1] = al_load_bitmap("propulsionButtonActivePng.png");
    repairButtonPng[1] = al_load_bitmap("repairButtonActivePng.png");
    alertnessButtonPng[1] = al_load_bitmap("alertnessButtonActivePng.png");
}

void Resource::LoadAudioResources()
{
    al_reserve_samples(10);

    genericBgmMp3 = al_load_sample("genericBgmMp3.mp3");
    genericBgmSampleInstance = al_create_sample_instance(genericBgmMp3);
    al_attach_sample_instance_to_mixer(genericBgmSampleInstance, al_get_default_mixer());

    genericPickupCoinWav = al_load_sample("genericPickupCoinWav.wav");
    genericPickupCoinSampleInstance = al_create_sample_instance(genericPickupCoinWav);
    al_attach_sample_instance_to_mixer(genericPickupCoinSampleInstance, al_get_default_mixer());

    genericClickWav = al_load_sample("genericClickWav.wav");
    genericClickSampleInstance = al_create_sample_instance(genericClickWav);
    al_attach_sample_instance_to_mixer(genericClickSampleInstance, al_get_default_mixer());

    genericLaserShootWav = al_load_sample("genericLaserShootWav.wav");
    genericLaserShootSampleInstance = al_create_sample_instance(genericLaserShootWav);
    al_attach_sample_instance_to_mixer(genericLaserShootSampleInstance, al_get_default_mixer());

    starryWalkMp3 = al_load_sample("starryWalkMp3.mp3");
    starryWalkSampleInstance = al_create_sample_instance(starryWalkMp3);
    al_attach_sample_instance_to_mixer(starryWalkSampleInstance, al_get_default_mixer());

}

void Resource::UnloadFontResources()
{
    al_destroy_font(builtin8);
}

void Resource::UnloadImageResources()
{
    al_destroy_bitmap(genericTitlePng);
    al_destroy_bitmap(genericOverworldPng);
    al_destroy_bitmap(genericResultsPng);
    al_destroy_bitmap(genericBeingPng);
    al_destroy_bitmap(genericTilePng);

    for(unsigned i = 0; i <= Segment::SEGMENT_CLASS_MARKER_END; i++)
        al_destroy_bitmap(serpentSegmentPng[i]);

    for(unsigned i = 0; i < 3; i++)
        al_destroy_bitmap(serpentKeyLightsPng[i]);
    for(unsigned i = 0; i < 2; i++)
        al_destroy_bitmap(serpentGenericLightsPng[i]);

    for(unsigned i = 0; i < 2; i++)
    {
        al_destroy_bitmap(foregroundStarPng[i]);
        al_destroy_bitmap(centralStarPng[i]);
        al_destroy_bitmap(backgroundStarPng[i]);
        al_destroy_bitmap(farBackgroundStarPng[i]);
    }

    al_destroy_bitmap(gravitonPng);
    al_destroy_bitmap(selectorCirclePng);

    for(unsigned i = 0; i < 2; i++)
    {
        al_destroy_bitmap(propulsionButtonPng[i]);
        al_destroy_bitmap(repairButtonPng[i]);
        al_destroy_bitmap(alertnessButtonPng[i]);
    }
}

void Resource::UnloadAudioResources()
{
    al_destroy_sample_instance(genericBgmSampleInstance);
    al_destroy_sample(genericBgmMp3);

    al_destroy_sample_instance(genericPickupCoinSampleInstance);
    al_destroy_sample(genericPickupCoinWav);

    al_destroy_sample_instance(genericClickSampleInstance);
    al_destroy_sample(genericClickWav);

    al_destroy_sample_instance(genericLaserShootSampleInstance);
    al_destroy_sample(genericLaserShootWav);

    al_destroy_sample_instance(starryWalkSampleInstance);
    al_destroy_sample(starryWalkMp3);
}
