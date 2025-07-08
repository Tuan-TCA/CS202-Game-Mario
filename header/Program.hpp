#pragma once
#include "Global.hpp"
#include "Scene.hpp"
class Program {
public:
    Program();
    void update();
    void display();
    void run();

    void changeScene(SceneMode a);

private: 
    Scene* curScene;
    vector<Scene*> scenes;
};