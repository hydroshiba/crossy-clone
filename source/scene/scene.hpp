#ifndef SCENE_HPP_
#define SCENE_HPP_

class Scene {
public:
    virtual void process() = 0;
    virtual void render() = 0;
    virtual void playsound() = 0;
};

#endif