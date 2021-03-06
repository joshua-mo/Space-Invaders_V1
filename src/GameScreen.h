#pragma once

#include <vector>
#include <memory>

#include "raylib.h"

#include "Screen.h"
#include "Sprite.h"
#include "math.h"
#include "Entity.h"


#define NUM_SHOOTS 50
#define NUM_MAX_ENEMIES 50
#define FIRST_WAVE 10
#define SECOND_WAVE 20
#define THIRD_WAVE 50


namespace Game {
    class GameScreen : public Screen {
   
    private:
        //Texturen definieren
        Texture2D playerTexture;
        Texture2D alienTexture;
        Texture2D background;
        Texture2D welt;

    
    private:
        std::vector<std::unique_ptr<Sprite>> sprites;

        GameScreen();


    public:
        static Screen *getInstance() {
            static GameScreen instance;
            return &instance;
        }

        GameScreen(GameScreen const &) = delete;

        void operator=(GameScreen const &) = delete;

        ~GameScreen();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };


    static Player player;
    static Bullet bullet[NUM_SHOOTS];
    static Enemy enemy[NUM_MAX_ENEMIES];
    static int activeEnemies;
    static int shootRate;

}
