#include "leaderboard.hpp"

Leaderboard::Leaderboard(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard),
                                                                                                                                                 GOLD("asset/texture/cup/gold.bmp"),
                                                                                                                                                 SILVER("asset/texture/cup/silver.bmp"),
                                                                                                                                                 COPPER("asset/texture/cup/copper.bmp"),
                                                                                                                                                 gold((width - GOLD.getWidth()) / 2, (height - GOLD.getHeight()) / 3, GOLD),
                                                                                                                                                 silver((width - SILVER.getWidth()) / 2 - 400, (height - SILVER.getHeight()) / 3 + 180, SILVER),
                                                                                                                                                 copper((width - COPPER.getWidth()) / 2 + 400, (height - COPPER.getHeight()) / 3 + 180, COPPER) 
                                                                                                                                                  {}

Leaderboard::~Leaderboard() {
}

Scene* Leaderboard::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();

    if(pressedKey == Key::ESC) {
        next = sceneRegistry->scene(SceneID::MENU);
    }

    return next;
}

void Leaderboard::render() {
    engine->fill(0, 162, 232);
    gold.render(engine);
    silver.render(engine);
    copper.render(engine);
}

void Leaderboard::playsound() {
    // this->audio->playSound(this->buttonSound);
}