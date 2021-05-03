#include "raylib.h"

#include "GameScreen.h"
#include "MenuScreen.h"
#include "game.h"




Game::GameScreen::GameScreen() {
    // Your screen initialization code here...
    Vector2 vec = {100.0f, 100.0f};
    this->sprites.push_back(
        std::make_unique<Game::Sprite>(LoadTexture("assets/graphics/background.png"),
            vec,
            true)
    );


    background = LoadTexture("assets/graphics/background.png");
    welt = LoadTexture("assets/graphics/welt.png");



    // Load alien ship texture
    playerTexture = LoadTexture("assets/graphics/player.png");

    // Spieler (Viereck) initialisieren
    player.rect.x = GetScreenWidth() / 2.0f;
    player.rect.y = GetScreenHeight() - 250;
    player.rect.width = 35;
    player.rect.height = 35;
    player.speed.x = 7;
    player.speed.y = 5;
    player.color = WHITE;


    // Bullets initialisieren
    shootRate = 0;

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet[i].rect.x = player.rect.x + 29;                  //Bullet zentrieren
        bullet[i].rect.y = player.rect.y + player.rect.height / 4;
        bullet[i].rect.width = 5;
        bullet[i].rect.height = 10;
        bullet[i].speed.x = 0;
        bullet[i].speed.y = -10;
        bullet[i].active = false;
        bullet[i].color = MAROON;
    }






    // Load alien ship texture
    alienTexture = LoadTexture("assets/graphics/alien.png");

    //Anzahl aktive Gegner 
    activeEnemies = 10;
    // Gegner initialisieren
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rect.width = 50;
        enemy[i].rect.height = 50;
        enemy[i].rect.x = GetRandomValue(0, GetScreenWidth()- 64);
        enemy[i].rect.y = GetRandomValue(-GetScreenHeight(), -20);
        enemy[i].speed.x = 5; 
        enemy[i].speed.y = 10; //Geschwindigkeit Gegner
        enemy[i].active = true;
    }

  

  }


Game::GameScreen::~GameScreen() {
    // Your screen cleanup code here...
    UnloadTexture(sprites[0]->texture);
    UnloadTexture(alienTexture);


}


void Game::GameScreen::ProcessInput() {
    // Your process input code here...
    if (IsKeyPressed(KEY_M)) currentScreen = Game::MenuScreen::getInstance();

    // Spieler bewegen (links-rechts)
    if (IsKeyDown(KEY_RIGHT))
        player.rect.x += player.speed.x;
    if (IsKeyDown(KEY_LEFT))
        player.rect.x -= player.speed.x;

    
   


}

void Game::GameScreen::Update() {
    // Your update game code here...

 if ((player.rect.x + 54) >= GetScreenWidth()) player.rect.x = GetScreenWidth() - 54;           //Spieler an Wänden einschränken
    else if (player.rect.x <= -10) player.rect.x = -10;

 //Bullets
 if (IsKeyDown(KEY_SPACE)) {

     shootRate += 5;


     for (int i = 0; i < NUM_SHOOTS; i++)
     {
         if (!bullet[i].active && shootRate % 40 == 0)
         { 
                // Movement
                 bullet[i].rect.y += bullet[i].speed.y;

             bullet[i].rect.x = player.rect.x + 29;                 //Bullet zentrieren
             bullet[i].rect.y = player.rect.y + player.rect.height / 4;
             bullet[i].active = true;
             break;
         }
     }
 }



 // Shoot logic
 for (int i = 0; i < NUM_SHOOTS; i++)
 {
     if (bullet[i].active)
     {
         // Movement
         bullet[i].rect.y += bullet[i].speed.y;

         // Kollision mit enemy
         for (int j = 0; j < activeEnemies; j++)
         {
             if (enemy[j].active)
             {
                 if (CheckCollisionRecs(bullet[i].rect, enemy[j].rect))
                 {
                     bullet[i].active = false;
                     enemy[j].rect.x = GetRandomValue(0, 1000);
                     enemy[j].rect.y = GetRandomValue(0, GetScreenHeight() - enemy[j].rect.height);
                     shootRate = 0;

                 
                 }

                 if (bullet[i].rect.y <= 0) //goes above the screen
                 {
                     bullet[i].active = false;
                     shootRate = 0;
                 }
             }
         }
     }
 }







  

    // Enemy Verhalten
    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].rect.y += enemy[i].speed.y;

            if (enemy[i].rect.y > GetScreenHeight())
            {
                enemy[i].rect.x = GetRandomValue(0, GetScreenWidth()- 64);
                enemy[i].rect.y = GetRandomValue(-GetScreenHeight(), -20);
            }
        }
    }
}



void Game::GameScreen::Draw() {
    // Your drawing code here...
    ClearBackground(LIGHTGRAY);
    DrawTexture(background, 0, 0, WHITE); //Hintergrund
   

    DrawText("Game - press M for menu", 20, 20, 20, PURPLE);


   

     DrawCircle(GetScreenWidth() / 2, 1190, 350, RED);                   //Hitbox Planet
     DrawTexture(welt, -60, 840, WHITE);                                 //Planet                
        
     //BUllet zeichnen
     for (int i = 0; i < NUM_SHOOTS; i++)
     {
         if (bullet[i].active)
             DrawRectangleRec(bullet[i].rect, bullet[i].color);
     }

     DrawTexture(playerTexture, player.rect.x, player.rect.y, WHITE);               //Player zeichnen

     for (int i = 0; i < activeEnemies; i++)
     {
         if (enemy[i].active)
             DrawTexture(alienTexture, enemy[i].rect.x, enemy[i].rect.y, WHITE);        //Gegner zeichnen
     }

     
     


}

