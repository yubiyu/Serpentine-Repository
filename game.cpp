#include "game.h"

bool Game::exit;
bool Game::redraw;

void Game::MainLoop()
{
    while(!exit)
    {
        al_wait_for_event(Event::eventQueue, &Event::event);

        if(Event::event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = true;

        if(Event::event.type == ALLEGRO_EVENT_KEY_DOWN)
            Keyboard::InputKeydown();

        if(Event::event.type == ALLEGRO_EVENT_KEY_UP)
            Keyboard::InputKeyup();

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
        {

        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
        {

        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            Mouse::InputMouseXY();
            Mouse::InputMousewheel();
        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            Mouse::InputMouseDown();

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            Mouse::InputMouseUp();


        if(Event::event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            InputSwitchboard();
            LogicSwitchboard();

            Mouse::mouseAxesAltered = false;
        }

        if(redraw && al_is_event_queue_empty(Event::eventQueue))
        {
            DrawingSwitchboard();
        }
    }
}

bool Game::Initialize(char **argv)
{
    exit = false;
    redraw = true;

    srand(time(NULL));

    al_install_system(ALLEGRO_VERSION_INT,NULL);
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    Display::display = al_create_display(Display::WIDTH, Display::HEIGHT);
    Time::FPSTimer = al_create_timer(1.0/Time::FPS);
    Event::eventQueue = al_create_event_queue();

    al_register_event_source(Event::eventQueue, al_get_display_event_source(Display::display));
    al_register_event_source(Event::eventQueue, al_get_timer_event_source(Time::FPSTimer));
    al_register_event_source(Event::eventQueue, al_get_keyboard_event_source());
    al_register_event_source(Event::eventQueue, al_get_mouse_event_source());

    if(!Resource::Initialize(argv))
    {
        assert("Resource : Initialization failed");
        return false;
    }

    Palette::Initialize();
    Scene::Initialize();

    Camera::Initialize();
    Camera::SetCell(0, 0);
    Camera::WarpToDestination();

    Serpent::Initialize();
    Star::GenerateStarfield();
    Space::Initialize();
    UpgradeMenu::Initialize();
    Station::Initialize();

    al_start_timer(Time::FPSTimer);

    al_set_sample_instance_playmode(Resource::starryWalkSampleInstance, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(Resource::starryWalkSampleInstance);

    return true;
}

void Game::Uninitialize()
{

    for(std::vector<Graviton*>::iterator it = Graviton::streamA.begin(); it != Graviton::streamA.end();)
    {
        delete *it;
        Graviton::streamA.erase(it);
    }
    for(std::vector<Graviton*>::iterator it = Graviton::streamB.begin(); it != Graviton::streamB.end();)
    {
        delete *it;
        Graviton::streamB.erase(it);
    }
    for(std::vector<Graviton*>::iterator it = Graviton::repairParticles.begin(); it != Graviton::repairParticles.end();)
    {
        delete *it;
        Graviton::repairParticles.erase(it);
    }
    for(std::vector<Graviton*>::iterator it = Graviton::damageParticles.begin(); it != Graviton::damageParticles.end();)
    {
        delete *it;
        Graviton::damageParticles.erase(it);
    }

    for(std::vector<Star*>::iterator it = Star::foregroundStarfield.begin(); it != Star::foregroundStarfield.end();)
    {
        delete *it;
        Star::foregroundStarfield.erase(it);
    }
    for(std::vector<Star*>::iterator it = Star::centralStarfield.begin(); it != Star::centralStarfield.end();)
    {
        delete *it;
        Star::centralStarfield.erase(it);
    }
    for(std::vector<Star*>::iterator it = Star::backgroundStarfield.begin(); it != Star::backgroundStarfield.end();)
    {
        delete *it;
        Star::backgroundStarfield.erase(it);
    }
    for(std::vector<Star*>::iterator it = Star::farBackgroundStarfield.begin(); it != Star::farBackgroundStarfield.end();)
    {
        delete *it;
        Star::farBackgroundStarfield.erase(it);
    }

    Serpent::Uninitialize();

    Camera::Uninitialize();
    Resource::Uninitialize();

    al_uninstall_audio();
    al_destroy_display(Display::display);
    al_destroy_timer(Time::FPSTimer);
    al_destroy_event_queue(Event::eventQueue);
    al_uninstall_system();

}


void Game::InputSwitchboard()
{
    Keyboard::InputKeyHold();
    Mouse::InputMouseButtonHold();

    switch(Scene::inputContext)
    {
    case Scene::INPUT_CONTEXT_TESTING:
        TestingInput();
        break;
    case Scene::INPUT_CONTEXT_TITLE:
        TitleInput();
        break;
    case Scene::INPUT_CONTEXT_SETTINGS:
        SettingsInput();
        break;
    case Scene::INPUT_CONTEXT_OVERWORLD:
        OverworldInput();
        break;
    }
}

void Game::TestingInput()
{
    if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_UP])
    {
        al_set_mouse_z(0);
    }
    else if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_DOWN])
    {
        al_set_mouse_z(0);
    }
    else if(Mouse::mouseInput[Mouse::MOUSE_MIDDLE])
    {

    }

    if(Mouse::mouseButtonHoldTicks[Mouse::MOUSE_LEFT] == 1)
    {

    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_LEFT] >= 1)
    {
        Camera::xPosition -= 4;
    }
    if(Keyboard::keyHoldTicks[Keyboard::KEY_RIGHT] >= 1)
    {
        Camera::xPosition += 4;
    }
    if(Keyboard::keyHoldTicks[Keyboard::KEY_UP] >= 1)
    {
        Camera::yPosition -= 4;
    }
    if(Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] >= 1)
    {
        Camera::yPosition += 4;
    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_J] == 1)
    {
        al_play_sample_instance(Resource::genericLaserShootSampleInstance);
    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_K] == 1)
    {
        if(al_get_sample_instance_playing(Resource::genericBgmSampleInstance))
            al_stop_sample_instance(Resource::genericBgmSampleInstance);
        else
        {
            al_set_sample_instance_playmode(Resource::genericBgmSampleInstance, ALLEGRO_PLAYMODE_LOOP);
            al_play_sample_instance(Resource::genericBgmSampleInstance);
        }
    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_ENTER] == 1)
    {
        Scene::ChangeScene(Scene::SCENE_TITLE);
    }
}

void Game::TitleInput()
{

}

void Game::SettingsInput()
{

}

void Game::OverworldInput()
{
    if(Mouse::mouseButtonHoldTicks[Mouse::MOUSE_LEFT] == 1)
    {
        int segmentIndex = 0;
        bool segmentFound = false;
        bool menuButtonFound = false;
        for(std::vector<Segment*>::iterator it = Serpent::segments.begin(); it != Serpent::segments.end(); ++it)
        {
            if(UpgradeMenu::segmentSelected)
            {
                if(Mouse::mouseDisplayY > UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET-8 &&
                        Mouse::mouseDisplayY < UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET+40)
                {
                    if(Mouse::mouseDisplayX > UpgradeMenu::xPosition + UpgradeMenu::PROPULSION_BUTTON_X_OFFSET-8 &&
                            Mouse::mouseDisplayX < UpgradeMenu::xPosition + UpgradeMenu::PROPULSION_BUTTON_X_OFFSET+40)
                    {
                        if(UpgradeMenu::whichSegment->hasPropulsionFunction)
                        {
                            LeftClickOnButton(UpgradeMenu::MENU_BUTTON_PROPULSION);
                            menuButtonFound = true;
                            break;
                        }
                    }
                    else if(Mouse::mouseDisplayX > UpgradeMenu::xPosition + UpgradeMenu::REPAIR_BUTTON_X_OFFSET-8 &&
                            Mouse::mouseDisplayX < UpgradeMenu::xPosition + UpgradeMenu::REPAIR_BUTTON_X_OFFSET+40)
                    {
                        if(UpgradeMenu::whichSegment->hasRepairFunction)
                        {
                            LeftClickOnButton(UpgradeMenu::MENU_BUTTON_REPAIR);
                            menuButtonFound = true;
                            break;
                        }
                    }
                    else if(Mouse::mouseDisplayX > UpgradeMenu::xPosition + UpgradeMenu::ALERTNESS_BUTTON_X_OFFSET-8 &&
                            Mouse::mouseDisplayX < UpgradeMenu::xPosition + UpgradeMenu::ALERTNESS_BUTTON_X_OFFSET+40)
                    {
                        if(UpgradeMenu::whichSegment->hasAlertnessFunction)
                        {
                            LeftClickOnButton(UpgradeMenu::MENU_BUTTON_ALERTNESS);
                            menuButtonFound = true;
                            break;
                        }
                    }
                }

                else if(Mouse::mouseDisplayY > UpgradeMenu::yPosition + UpgradeMenu::RECOLOUR_BUTTON_Y_OFFSET-8 &&
                        Mouse::mouseDisplayY < UpgradeMenu::yPosition + UpgradeMenu::RECOLOUR_BUTTON_Y_OFFSET+40 &&
                        Mouse::mouseDisplayX > UpgradeMenu::xPosition + UpgradeMenu::RECOLOUR_BUTTON_X_OFFSET-8 &&
                        Mouse::mouseDisplayX < UpgradeMenu::xPosition + UpgradeMenu::RECOLOUR_BUTTON_X_OFFSET+40)
                {
                    LeftClickOnButton(UpgradeMenu::MENU_BUTTON_RECOLOUR);
                    menuButtonFound = true;
                    break;
                }

            }

            if(!menuButtonFound)
            {
                if(Mouse::mouseDisplayX > (*it)->xPosition-32 && Mouse::mouseDisplayX < (*it)->xPosition+32
                        && Mouse::mouseDisplayY > (*it)->yPosition-32 && Mouse::mouseDisplayY < (*it)->yPosition+32)
                {
                    //std::cout << "Test: Segment " << segmentIndex << " clicked." << std::endl;
                    LeftClickOnSegment(*it);
                    segmentFound = true;
                    break;
                }

            }
            segmentIndex++;
        }

        if(!menuButtonFound && !segmentFound)
        {
            LeftClickOnSegment(nullptr);
        }
    }
}

void Game::LogicSwitchboard()
{
    switch(Scene::scene)
    {
    case Scene::SCENE_TESTING_NOSCENE:
        TestingNosceneLogic();
        break;
    case Scene::SCENE_TITLE:
        TitleSceneLogic();
        break;
    case Scene::SCENE_SETTINGS:
        SettingsSceneLogic();
        break;
    case Scene::SCENE_OVERWORLD:
        OverworldSceneLogic();
        break;
    }
}

void Game::TestingNosceneLogic()
{

}

void Game::TitleSceneLogic()
{

}

void Game::SettingsSceneLogic()
{

}

void Game::OverworldSceneLogic()
{
    Space::Update();
    Serpent::Update();
    UpgradeMenu::Update();
    Station::Update(Serpent::speed, Serpent::pathYMod[0]);

    for(std::vector<Star*>::iterator it = Star::farBackgroundStarfield.begin(); it != Star::farBackgroundStarfield.end(); ++it)
    {
        (*it)->xPosition -= 0.125 + Serpent::speed/2056;
        (*it)->yPosition -= Serpent::pathYMod[0]/2056;
        (*it)->Update();
    }
    for(std::vector<Star*>::iterator it = Star::backgroundStarfield.begin(); it != Star::backgroundStarfield.end(); ++it)
    {
        (*it)->xPosition -= 0.25 + Serpent::speed/256;
        (*it)->yPosition -= Serpent::pathYMod[0]/256;
        (*it)->Update();
    }
    for(std::vector<Star*>::iterator it = Star::centralStarfield.begin(); it != Star::centralStarfield.end(); ++it)
    {
        (*it)->xPosition -= 0.5 + Serpent::speed/128;
        (*it)->yPosition -= Serpent::pathYMod[0]/128;
        (*it)->Update();
    }
    for(std::vector<Star*>::iterator it = Star::foregroundStarfield.begin(); it != Star::foregroundStarfield.end(); ++it)
    {
        (*it)->xPosition -= 1.25 + Serpent::speed/24;
        (*it)->yPosition -= Serpent::pathYMod[0]/24;
        (*it)->Update();
    }


    for(std::vector<Graviton*>::iterator it = Graviton::streamA.begin(); it != Graviton::streamA.end();)
    {
        (*it)->Update();
        (*it)->xPosition -= Serpent::speed/300;
        if(! (*it)->alive)
        {
            delete *it;
            Graviton::streamA.erase(it);
        }
        else
            ++it;
    }
    for(std::vector<Graviton*>::iterator it = Graviton::streamB.begin(); it != Graviton::streamB.end();)
    {
        (*it)->Update();
        (*it)->xPosition -= Serpent::speed/300;
        if(! (*it)->alive)
        {
            delete *it;
            Graviton::streamB.erase(it);
        }
        else
            ++it;
    }

    for(std::vector<Graviton*>::iterator it = Graviton::repairParticles.begin(); it != Graviton::repairParticles.end();)
    {
        (*it)->Update();
        (*it)->xPosition -= Serpent::speed/300;
        if(! (*it)->alive)
        {
            delete *it;
            Graviton::repairParticles.erase(it);
        }
        else
            ++it;
    }

    for(std::vector<Graviton*>::iterator it = Graviton::damageParticles.begin(); it != Graviton::damageParticles.end();)
    {
        (*it)->Update();
        (*it)->xPosition -= Serpent::speed/300;
        if(! (*it)->alive)
        {
            delete *it;
            Graviton::damageParticles.erase(it);
        }
        else
            ++it;
    }
}

void Game::DrawingSwitchboard()
{
    Game::redraw = false;

    switch(Scene::scene)
    {
    case Scene::SCENE_TESTING_NOSCENE:
        al_clear_to_color(COLKEY_BACKGROUND);
        TestingNosceneDrawing();
        break;
    case Scene::SCENE_TITLE:
        TitleSceneDrawing();
        break;
    case Scene::SCENE_SETTINGS:
        SettingsSceneDrawing();
        break;
    case Scene::SCENE_OVERWORLD:
        al_clear_to_color(al_map_rgb(Space::rComponent, Space::gComponent, Space::bComponent));
        OverworldSceneDrawing();
        break;
    }

    al_flip_display();
}

void Game::TestingNosceneDrawing()
{
    DrawDebugGrid();
    DrawDebugGridCameraCrosshair();
    DrawDebugGridText();

    al_draw_multiline_text(Resource::builtin8, COLKEY_TEXT_LIGHT, Display::WIDTH, 0, 600, 16, ALLEGRO_ALIGN_RIGHT,
                           "<Enter> to proceed to title.\n<UDLR> to test camera.\n<J> to test SFX.\n<K> to toggle test BGM.");
}

void Game::TitleSceneDrawing()
{

}

void Game::SettingsSceneDrawing()
{

}

void Game::OverworldSceneDrawing()
{
    for(std::vector<Star*>::iterator it = Star::farBackgroundStarfield.begin(); it != Star::farBackgroundStarfield.end(); ++it)
        al_draw_bitmap(Resource::farBackgroundStarPng[(*it)->variant], (*it)->xPosition, (*it)->yPosition, 0);
    for(std::vector<Star*>::iterator it = Star::backgroundStarfield.begin(); it != Star::backgroundStarfield.end(); ++it)
        al_draw_bitmap(Resource::backgroundStarPng[(*it)->variant], (*it)->xPosition, (*it)->yPosition, 0);


    if(Station::atStation)
        al_draw_bitmap(Resource::stationPng[Station::currentStation],Station::drawX,Station::drawY,0);


    for(std::vector<Star*>::iterator it = Star::centralStarfield.begin(); it != Star::centralStarfield.end(); ++it)
        al_draw_bitmap(Resource::centralStarPng[(*it)->variant], (*it)->xPosition, (*it)->yPosition, 0);

    for(std::vector<Graviton*>::iterator it = Graviton::streamB.begin(); it != Graviton::streamB.end(); ++it)
    {
        al_draw_bitmap(Resource::gravitonPng, (*it)->xPosition, (*it)->yPosition, 0);
    }

    for(std::vector<Segment*>::reverse_iterator it = Serpent::segments.rbegin(); it != Serpent::segments.rend(); ++it)
    {
        al_draw_rotated_bitmap(Resource::serpentSegmentSubBitmap[(*it)->colour][(*it)->classification], 32, 32,
                               (*it)->xPosition, (*it)->yPosition,
                               (*it)->rotationAngle,
                               0);
    }

    int energyPerLight = Serpent::maxEnergy / Serpent::totalLights;
    int energyCounted = 0;
    for(std::vector<Segment*>::iterator it = Serpent::segments.begin(); it != Serpent::segments.end(); ++it)
    {
        if((*it)->numLights > 0)
        {
            int segmentLightLevel = 0;
            for(int i = 0; i < (*it)->numLights; i++)
            {
                energyCounted += energyPerLight;
                if(Serpent::currentEnergy >= energyCounted)
                    segmentLightLevel ++;
                else
                    break;
            }

            if(segmentLightLevel > 0)
            {
                if((*it)->classification == Segment::SEGMENT_CLASS_KEY)
                    al_draw_rotated_bitmap(Resource::serpentKeyLightsPng[segmentLightLevel-1], 32, 32,
                                           (*it)->xPosition, (*it)->yPosition,
                                           (*it)->rotationAngle,
                                           0);
                else if((*it)->classification == Segment::SEGMENT_CLASS_GENERIC)
                    al_draw_rotated_bitmap(Resource::serpentGenericLightsPng[segmentLightLevel-1], 32, 32,
                                           (*it)->xPosition, (*it)->yPosition,
                                           (*it)->rotationAngle,
                                           0);
            }
        }

        if(energyCounted > Serpent::currentEnergy)
            break;
    }

    for(std::vector<Graviton*>::iterator it = Graviton::repairParticles.begin(); it != Graviton::repairParticles.end(); ++it)
    {
        al_draw_bitmap(Resource::gravitonGreenPng, (*it)->xPosition, (*it)->yPosition, 0);
    }
    for(std::vector<Graviton*>::iterator it = Graviton::damageParticles.begin(); it != Graviton::damageParticles.end(); ++it)
    {
        al_draw_bitmap(Resource::gravitonRedPng, (*it)->xPosition, (*it)->yPosition, 0);
    }

    for(std::vector<Graviton*>::iterator it = Graviton::streamA.begin(); it != Graviton::streamA.end(); ++it)
    {
        al_draw_bitmap(Resource::gravitonPng, (*it)->xPosition, (*it)->yPosition, 0);
    }

    for(std::vector<Star*>::iterator it = Star::foregroundStarfield.begin(); it != Star::foregroundStarfield.end(); ++it)
        al_draw_tinted_bitmap(Resource::foregroundStarPng[(*it)->variant], al_map_rgba_f(1.0,1.0,1.0,0.05), (*it)->xPosition, (*it)->yPosition, 0);

    if(UpgradeMenu::segmentSelected)
    {
        al_draw_tinted_rotated_bitmap(Resource::selectorCirclePng, al_map_rgba_f(1.0,1.0,1.0,0.5),
                                      64, 64,
                                      UpgradeMenu::xPosition,
                                      UpgradeMenu::yPosition,
                                      UpgradeMenu::selectorCircleRotation,
                                      0);

        if(UpgradeMenu::whichSegment->hasRepairFunction)
        {
            if(UpgradeMenu::whichSegment->repairFunctionActive)
                al_draw_tinted_bitmap(Resource::repairButtonPng[1], al_map_rgba_f(1.0,1.0,1.0,0.8),
                                      UpgradeMenu::xPosition + UpgradeMenu::REPAIR_BUTTON_X_OFFSET,
                                      UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET,
                                      0);
            else
                al_draw_tinted_bitmap(Resource::repairButtonPng[0], al_map_rgba_f(1.0,1.0,1.0,0.8),
                                      UpgradeMenu::xPosition + UpgradeMenu::REPAIR_BUTTON_X_OFFSET,
                                      UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET,
                                      0);
        }

        if(UpgradeMenu::whichSegment->hasPropulsionFunction)
        {
            if(UpgradeMenu::whichSegment->propulsionFunctionActive)
                al_draw_tinted_bitmap(Resource::propulsionButtonPng[1], al_map_rgba_f(1.0,1.0,1.0,0.8),
                                      UpgradeMenu::xPosition + UpgradeMenu::PROPULSION_BUTTON_X_OFFSET,
                                      UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET,
                                      0);
            else
                al_draw_tinted_bitmap(Resource::propulsionButtonPng[0], al_map_rgba_f(1.0,1.0,1.0,0.8),
                                      UpgradeMenu::xPosition + UpgradeMenu::PROPULSION_BUTTON_X_OFFSET,
                                      UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET,
                                      0);
        }
        if(UpgradeMenu::whichSegment->hasAlertnessFunction)
        {
            if(UpgradeMenu::whichSegment->alertnessFunctionActive)
                al_draw_tinted_bitmap(Resource::alertnessButtonPng[1], al_map_rgba_f(1.0,1.0,1.0,0.8),
                                      UpgradeMenu::xPosition + UpgradeMenu::ALERTNESS_BUTTON_X_OFFSET,
                                      UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET,
                                      0);
            else
                al_draw_tinted_bitmap(Resource::alertnessButtonPng[0], al_map_rgba_f(1.0,1.0,1.0,0.8),
                                      UpgradeMenu::xPosition + UpgradeMenu::ALERTNESS_BUTTON_X_OFFSET,
                                      UpgradeMenu::yPosition + UpgradeMenu::BUTTONS_Y_OFFSET,
                                      0);
        }

        al_draw_tinted_bitmap(Resource::recolourButtonPng, al_map_rgba_f(1.0,1.0,1.0,0.8),
                              UpgradeMenu::xPosition + UpgradeMenu::RECOLOUR_BUTTON_X_OFFSET,
                              UpgradeMenu::yPosition + UpgradeMenu::RECOLOUR_BUTTON_Y_OFFSET,
                              0);
    }

    if(Station::atStation)
    {
        al_draw_bitmap(Resource::exitStationArrowPng, Station::STATION_ARROW_X, Station::STATION_ARROW_Y, 0);
        al_draw_text(Resource::lowresPixelRegular16,Palette::COLKEY_TEXT_LIGHT, Station::STATION_ARROW_X, Station::STATION_ARROW_Y, ALLEGRO_ALIGN_RIGHT, "Departure");
        Hax::string_al_draw_text(Resource::lowresPixelRegular16,Palette::COLKEY_TEXT_LIGHT, Station::STATION_ARROW_X, Station::STATION_ARROW_Y+16, ALLEGRO_ALIGN_RIGHT, std::to_string((int)Station::widthRemaining) + " m");
    }
    else // !atStation
    {
        al_draw_bitmap(Resource::nextStationArrowPng, Station::STATION_ARROW_X, Station::STATION_ARROW_Y, 0);
        Hax::string_al_draw_text(Resource::lowresPixelRegular16,Palette::COLKEY_TEXT_LIGHT, Station::STATION_ARROW_X, Station::STATION_ARROW_Y, ALLEGRO_ALIGN_RIGHT, Station::stationNames[Station::nextStation]);
        Hax::string_al_draw_text(Resource::lowresPixelRegular16,Palette::COLKEY_TEXT_LIGHT, Station::STATION_ARROW_X, Station::STATION_ARROW_Y+16, ALLEGRO_ALIGN_RIGHT, std::to_string((int)Station::distanceToStation) + " m");

    }



    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS1_READOUT_X, OverworldUI::LIFE_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Hull: " + std::to_string((int)Serpent::currentLife) + " / " + std::to_string((int)Serpent::maxLife) + "HP");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS1_READOUT_X, OverworldUI::REPAIR_SPEED_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Repair speed: " + std::to_string((int)Serpent::repairSpeed) + "HP/s");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS1_READOUT_X, OverworldUI::REPAIR_ACCELERATION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Repair acceleration: " +  std::to_string((int)Serpent::repairAcceleration) + " HP/s^2");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS1_READOUT_X, OverworldUI::REPAIR_LOSS_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Repair speed loss: " +  std::to_string((int)Serpent::repairLoss) + " HP/s");

    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS2_READOUT_X, OverworldUI::SPEED_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Speed: " + std::to_string((int)Serpent::speed) + " m/s");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS2_READOUT_X, OverworldUI::ACCELERATION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Acceleration: " + std::to_string((int)Serpent::acceleration) + " m/s^2");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS2_READOUT_X, OverworldUI::VISCOUS_DRAG_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Viscous drag: " + std::to_string((int)Serpent::viscousDrag) + " N");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS2_READOUT_X, OverworldUI::WEAR_RATE_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Wear Rate: " + std::to_string((int)Serpent::wearRate) + " HP/s");


    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::CURRENT_ENERGY_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Current energy: " + std::to_string((int)Serpent::currentEnergy) + " J");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::MAX_ENERGY_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Energy capacity: " + std::to_string((int)Serpent::maxEnergy) + " J");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::ENERGY_PRODUCTION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "EN production: " + std::to_string((int)Serpent::energyProduction) + " W");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::ENERGY_CONSUMPTION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "EN consumption: " + std::to_string((int)Serpent::energyConsumption) + " W");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::BASE_ENERGY_CONSUMPTION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Life support EN: " + std::to_string((int)Serpent::BASE_ENERGY_CONSUMPTION) + " W");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::PROPULSION_ENERGY_CONSUMPTION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Propulsion EN: " + std::to_string((int)Serpent::propulsionEnergyTotal) + " W");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::REPAIR_ENERGY_CONSUMPTION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Repair EN: " + std::to_string((int)Serpent::repairEnergyTotal) + " W");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS3_READOUT_X, OverworldUI::AMNETIES_ENERGY_CONSUMPTION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Shield EN: " + std::to_string((int)Serpent::alertnessEnergyTotal) + " W");

    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS4_READOUT_X, OverworldUI::PASSENGERS_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Passengers: " + std::to_string((int)Serpent::numPassengers) + " pipol");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS4_READOUT_X, OverworldUI::AMNETIES_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Amneties: " + std::to_string((int)Serpent::currentAmneties) + " happy");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS4_READOUT_X, OverworldUI::AMNETIES_GENERATION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Amneties generation: " + std::to_string((int)Serpent::amnetiesGeneration) + " happy/s");
    Hax::string_al_draw_text(Resource::lowresPixelRegular16, COLKEY_TEXT_LIGHT, OverworldUI::STATS4_READOUT_X, OverworldUI::AMNETIES_ATTENUATION_READOUT_Y, ALLEGRO_ALIGN_LEFT, "Amneties attenuation: " + std::to_string((int)Serpent::amnetiesAttenuation) + " happy/s");

}

void Game::DrawDebugGrid()
{
    for(int x = 0; x <= Display::WIDTH / Tile::WIDTH; x++) //Columns
    {
        al_draw_line(x*Tile::WIDTH - (int)Camera::xPosition%(int)Tile::HEIGHT,
                     0,
                     x*Tile::WIDTH  - (int)Camera::xPosition%(int)Tile::HEIGHT,
                     Display::HEIGHT,
                     COLKEY_GRID,1);
    }

    for(int y = 0; y <= Display::HEIGHT / Tile::HEIGHT; y++) //Rows
    {
        al_draw_line(0,
                     y*Tile::WIDTH  - (int)Camera::yPosition%(int)Tile::HEIGHT,
                     Display::WIDTH,
                     y*Tile::WIDTH  - (int)Camera::yPosition%(int)Tile::HEIGHT,
                     COLKEY_GRID,1);
    }
}



void Game::DrawDebugGridCameraCrosshair()
{
    al_draw_line(Display::WIDTH/2, 0, Display::WIDTH/2, Display::HEIGHT, COLKEY_CAMERA_CROSSHAIR_LOCKED, 1);
    al_draw_line(0, Display::HEIGHT/2, Display::WIDTH, Display::HEIGHT/2, COLKEY_CAMERA_CROSSHAIR_LOCKED, 1);
}



void Game::DrawDebugGridText()
{
    int camXPos = Camera::xPosition;
    int camYPos = Camera::yPosition;

    int camXCell = std::round(camXPos/Tile::WIDTH);
    int camYCell = std::round(camYPos/Tile::HEIGHT);

    int zoomPercentage = Camera::zoomScale*100;

    std::string cameraPositionString = "Crosshair position: (" + std::to_string(camXPos) + ", " + std::to_string(camYPos) + ") : ("
                                       + std::to_string(camXCell) + ", " + std::to_string(camYCell) + ") "
                                       + std::to_string(zoomPercentage) + "% zoom";

    Hax::string_al_draw_text(Resource::builtin8,COLKEY_CAMERA_CROSSHAIR_LOCKED,0,0,ALLEGRO_ALIGN_LEFT,cameraPositionString);

}

void Game::LeftClickOnSegment(Segment* s)
{
    if(s != nullptr)
        UpgradeMenu::segmentSelected = true;
    else
        UpgradeMenu::segmentSelected = false;

    UpgradeMenu::whichSegment = s;
}

void Game::LeftClickOnButton(int whichButton)
{
    switch(whichButton)
    {
    case UpgradeMenu::MENU_BUTTON_REPAIR:
        UpgradeMenu::whichSegment->ToggleRepairFunction();
        Serpent::UpdateRepairLevel();
        break;

    case UpgradeMenu::MENU_BUTTON_PROPULSION:
        UpgradeMenu::whichSegment->TogglePropulsionFunction();
        Serpent::UpdatePropulsionLevel();
        break;

    case UpgradeMenu::MENU_BUTTON_ALERTNESS:
        UpgradeMenu::whichSegment->ToggleAlertnessFunction();
        Serpent::UpdateAlertnessLevel();
        //std::cout << "Alertness button pushed " << std::endl;
        break;

    case UpgradeMenu::MENU_BUTTON_RECOLOUR:
        UpgradeMenu::whichSegment->ChangeColour();
        break;
    }
}
