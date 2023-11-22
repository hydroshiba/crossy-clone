    #ifndef SCENE_REGISTRY_HPP_
    #define SCENE_REGISTRY_HPP_

    #include "scene.hpp"
    #include "menu.hpp"
    // #include "pause.hpp"
    // #include "play.hpp"
    // #include "gameover.hpp

    class SceneRegistry{
    private:
        Scene* menu;
        Scene* play;
        Scene* pause;
        Scene* gameover;
    public:
        SceneRegistry(Engine* engine, AudioDevice* audio , Setting* setting);
        ~SceneRegistry();

        friend class Scene;
        friend class Menu;
        friend class Play;
        friend class Pause;
        friend class Gameover;
    };

    #endif