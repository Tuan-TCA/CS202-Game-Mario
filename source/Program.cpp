#include "Program.hpp"
#include "Global.hpp"
#include "Game.hpp"

Program::Program() {
    InitWindow(screenWidth, screenHeight, "Game Mario CS202");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    SetTargetFPS(60);

    // scenes.push_back(new Scene(SceneMode::GAME));
    // Factory Method ?

    curScene = new Game;
}

void Program::run() {

    while(!WindowShouldClose()) {
        update();
        BeginDrawing();
            BeginMode2D(curScene->getCamera());

                ClearBackground(WHITE);
                display();
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();

}


void Program::update() {
    curScene->update();
}

void Program::display() {
    curScene->display();
}

