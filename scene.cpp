#include "scene.h"

int Scene::scene;
int Scene::inputContext;

void Scene::Initialize()
{
    ChangeScene(SCENE_OVERWORLD);
}

void Scene::ChangeScene(int whichScene)
{
    scene = whichScene;

    switch(scene)
    {
    case SCENE_TESTING_NOSCENE:
        ChangeInputContext(INPUT_CONTEXT_TESTING);
        break;

    case SCENE_TITLE:
        ChangeInputContext(INPUT_CONTEXT_TITLE);
        break;

    case SCENE_SETTINGS:
        ChangeInputContext(INPUT_CONTEXT_SETTINGS);
        break;

    case SCENE_OVERWORLD:
        ChangeInputContext(INPUT_CONTEXT_OVERWORLD);
        break;
    }
}

void Scene::ChangeInputContext(int whichContext)
{
    inputContext = whichContext;
}
