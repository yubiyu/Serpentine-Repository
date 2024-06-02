#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "time.h"
#include "resource.h"
#include "scene.h"
#include "event.h"
#include "camera.h"
#include "display.h"
#include "keyboard.h"
#include "mouse.h"
#include "palette.h"
#include "hax.h"
#include "overworldUI.h"

#include "serpent.h"
#include "segment.h"
#include "star.h"
#include "graviton.h"
#include "space.h"
#include "upgrademenu.h"

#include <iostream>

struct Game
{
    static bool exit;
    static bool redraw;

    static void MainLoop();

    static bool Initialize(char **argv);
    static void Uninitialize();

    static void InputSwitchboard();
    static void TestingInput();
    static void TitleInput();
    static void SettingsInput();
    static void OverworldInput();

    static void LogicSwitchboard();
    static void TestingNosceneLogic();
    static void TitleSceneLogic();
    static void SettingsSceneLogic();
    static void OverworldSceneLogic();

    static void DrawingSwitchboard();
    static void TestingNosceneDrawing();
    static void TitleSceneDrawing();
    static void SettingsSceneDrawing();
    static void OverworldSceneDrawing();

    static void DrawDebugGrid();
    static void DrawDebugGridCameraCrosshair();
    static void DrawDebugGridText(/*float mouseTransformedX, float mouseTransformedY*/);

    static void LeftClickOnSegment(Segment* s);
    static void LeftClickOnButton(int whichButton);
};

#endif // GAME_H_INCLUDED
