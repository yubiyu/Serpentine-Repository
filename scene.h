#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

struct Scene
{
    enum enumScene
    {
        SCENE_TESTING_NOSCENE,
        SCENE_TITLE,
        SCENE_SETTINGS,
        SCENE_OVERWORLD
    };
    static int scene;

    enum enumInputContext
    {
        INPUT_CONTEXT_TESTING,
        INPUT_CONTEXT_TITLE,
        INPUT_CONTEXT_SETTINGS,
        INPUT_CONTEXT_OVERWORLD
    };
    static int inputContext;

    static void Initialize();
    static void ChangeScene(int whichScene);
    static void ChangeInputContext(int whichContext);
};


#endif // SCENE_H_INCLUDED
