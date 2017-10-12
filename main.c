
#include "raylib.h"
#include <math.h>
#define MAX_ENEMIES 200
#define MAX_PARTICLES 20

typedef enum GameScreen { LOGO, TITLE, LOADING, GAMEPLAY, ENDING, SETTINGS } GameScreen;





int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;
    
    InitWindow(screenWidth, screenHeight, "slimO");
    
    InitAudioDevice();
    HideCursor();
    GameScreen currentScreen = LOGO;
    
    //Variables   
    int floor = (screenHeight/3) * 2;
    Rectangle player = {screenWidth/3,floor,64,64};
    int playerSpeed = 4;
    int playerLife = 100;
    int playerDamage = 2;
    
    int criticalDamage = 5;
    int criticalChance = 10;
    bool critik = 0;
    
    int playerGold = 0;
    
    bool isReceivingDMG = 0;
    int receivingDMGCounter = 0;
    int enemyMakingDMG = 0;
    float slimeForce = 5.0f;
    
    bool selected = 0;
    float musicVolume = 0.1f;
    Vector2 mousePosition;
    int phase = 1;   
    bool pause = 0;  
    bool debbugMode = 0;
    
    //Skill Menu
    
    bool skillMenu = 0;
    bool unLockSaw = 0;
    bool sawUpgrade = 0;
    bool sawUpgrade2 = 0;
    bool sawUpgrade3 = 0;
    
    bool unLockTrail = 0;
    bool trailUpgrade = 0;
    bool trailUpgrade2 = 0;
    bool trailUpgrade3 = 0;
    
    bool unLockBuilding = 0;
    bool buildingUpgrade = 0;
    bool buildingUpgrade2 = 0;
    bool buildingUpgrade3 = 0;
    
    //Enemies
    Rectangle enemy[MAX_ENEMIES];
    int enemySpeed[MAX_ENEMIES];
    int enemyLife[MAX_ENEMIES];
    bool enemyAlive[MAX_ENEMIES];
    int enemyLoot[MAX_ENEMIES];
    int enemyDeathCounter[MAX_ENEMIES];
    int enemyFramePosition[MAX_ENEMIES];
    Rectangle enemyFrame[MAX_ENEMIES];
    Vector2 lootPosition[MAX_ENEMIES];
    int deadSlimesCounter = 0;
    int enemyDamage = 2;
    
    for (int i = 0; i < MAX_ENEMIES;i++)
    {
        enemy[i].x = GetRandomValue(-1000,1000) * i;
        if(enemy[i].x > 0 && enemy[i].x < screenWidth) enemy[i].x = screenWidth * i;
        enemy[i].y = GetRandomValue(-1000,1000) * i;
        if(enemy[i].y > 0 && enemy[i].y < screenHeight) enemy[i].y = screenHeight * i;
        enemy[i].width = 50;
        enemy[i].height = 50;
        enemyLife[i] = GetRandomValue(50,200); 
        enemySpeed[i] = GetRandomValue(1,4);
        enemyAlive[i] = 1;
        enemyLoot[i] = GetRandomValue(0,10);
        enemyDeathCounter[i] = 12;
        enemyFramePosition[i] = 0;
        enemyFrame[i].x = 0;
        enemyFrame[i].y = 0;
        enemyFrame[i].width = 64;
        enemyFrame[i].height = 64;

    }
    Rectangle boss = {-512,-512,512,512};
    Vector2 bossSpeed = {2,2};
    bool bossFight = 0;
    
    
    //Weapon Vars
    float angle;
    float dx, dy;
    float range = 100;
    
    bool weaponSawActive = 0;
    int sawCounter = 0;
    int sawDamage = 10;    
    Vector2 slimeTrail[10];
    int trailCounter = 0;
    int trailcoolUp = 200;
    int trailcoolDown = 0;
    int trailRadius = 15;
    int trailDamage = 2;
    float trailAlpha = 1.0f;
    for(int i = 0; i < 10; i++)
    {
        slimeTrail[i].x = -99;
        slimeTrail[i].y = -99;
    }
    Vector2 blood[MAX_PARTICLES];
    int bloodTTL[MAX_PARTICLES];
    for(int i = 0; i < MAX_PARTICLES;i++)
    {
        blood[i].x = -99;
        blood[i].y = -99;
        bloodTTL[i]= 15;
    }
    Vector2 weapon;
    //WeaponKind currentWeapon = SLIMEBALL;

    int framesCounter = 0;      // General pourpose frames counter
    int framesCounterBack = 0;
    int gameResult = -1;        // 0 - Loose, 1 - Win, -1 - Not defined


    //Load Textures
    
    //logo
    Texture2D logo = LoadTexture("resources/karmysoft.png");
    float logoAlpha = 0.0f;
    
    //Main Character
    
    Texture2D slimo = LoadTexture("resources/slime.png");
    Rectangle slimoFrame = {0,0,64,64};
    int slimoFrameCounter = 1;
    int animationFrameCounter = 0;
    
    //enemy
    Texture2D enemyTileSet = LoadTexture("resources/enemy.png");
    Texture2D enemyDeath = LoadTexture("resources/enemy_empty.png");
    Texture2D enemyDeathLoot = LoadTexture("resources/enemy_loot.png");
    Texture2D lootball = LoadTexture("resources/lootball.png");
    
    Texture2D bossTexture = LoadTexture("resources/boss.png");
    
    //weapons
    Texture2D slimoball = LoadTexture("resources/slimeball.png");
    Texture2D slimoballSaw = LoadTexture("resources/weaponsaw.png");
    Texture2D slimeBlood = LoadTexture("resources/blood.png");

    //GUI
    Texture2D titlename = LoadTexture("resources/title.png");
    Texture2D cursor = LoadTexture("resources/cursor.png");
    Texture2D lifeBar = LoadTexture("resources/lifebar.png");
    Texture2D GUIBars = LoadTexture("resources/GUI_Bars.png");
    Texture2D circle = LoadTexture("resources/circle.png");
    
    Texture2D trailIcon = LoadTexture("resources/trailIcon.png");
    Texture2D sawIcon = LoadTexture("resources/sawIcon.png");
    Texture2D buildingIcon = LoadTexture("resources/buildingIcon.png");
    
    Texture2D instructions = LoadTexture("resources/instructions.png");
    
    Texture2D unLockTexture = LoadTexture("resources/unlock.png");
    
    //BG
    Texture2D backGround = LoadTexture("resources/bg.png");
    
    //Structures
    Rectangle placement = {-99, -99,64,64};
    Texture2D buildingTowerTexture = LoadTexture("resources/building.png");
    Rectangle buildingTower[5];
    int towerLife[5];
    int towerAlive[5];
    for(int i = 0; i < 5;i++)
    {
        buildingTower[i].width = 64;
        buildingTower[i].height = 64;
        buildingTower[i].x = -999999;
        buildingTower[i].y = -999999;
        towerLife[i] = 500;
        towerAlive[i] = 0;
    }
    int towerCD = 0;
    int buildingTCounter = 0;
    bool buildingON = 0;
    int buildingKind = 1;

    //music
    Music mainTheme = LoadMusicStream("resources/arcade.ogg");
    
    //fonts
    SpriteFont curly = LoadSpriteFontEx("resources/Bigcurls.ttf",20,0,0);
    SpriteFont fontforHUD = LoadSpriteFontEx("resources/fontforHUD.ttf",50,0,0);
    
    //sfx
    Sound selectSound = LoadSound("resources/sfx/select.wav");
    Sound selectSound2 = LoadSound("resources/sfx/select2.wav");
    Sound deathSound = LoadSound("resources/sfx/death.wav");
    Sound enemyDeathSound = LoadSound("resources/sfx/enemydeath.wav");
    Sound gotLoot = LoadSound("resources/sfx/lootsound.wav");
    //Sound appearLoot = LoadSound("resources/sfx/lootappearsound.wav");
    Sound trailSound = LoadSound("resources/sfx/trail.wav");
    Sound buildingSound = LoadSound("resources/sfx/building.wav");
    Sound sawSound = LoadSound("resources/sfx/sfx.wav");
    
    SetMusicVolume(mainTheme, musicVolume);
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        mousePosition = GetMousePosition();
        switch(currentScreen) 
        {
            case LOGO: 
            {
                // Update LOGO screen data here!
                
                framesCounter++;
                if(framesCounter <= 90)logoAlpha += 0.0111f;                
                if(framesCounter >= 210)logoAlpha -= 0.0111f; 

                if(framesCounter > 300)
                {
                    currentScreen = TITLE;
                    framesCounter = 0;
                }

                if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))currentScreen = TITLE;
                // TODO: Logo fadeIn and fadeOut logic...............(0.5p)
                
            } break;
            case TITLE: 
            {

                if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
                {
                    currentScreen = GAMEPLAY;
                    PlayMusicStream(mainTheme);
                    PlaySound(selectSound);
                }
                if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Play", 50)/2 , screenHeight/2 - 50,MeasureText("Play", 50),50}) && selected == 0)
                {
                    PlaySound(selectSound2);
                    selected = 1;
                }
                if(!CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Play", 50)/2 , screenHeight/2 - 50,MeasureText("Play", 50),50})
                    && !(CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Settings", 50)/2 , screenHeight/2 + 30,MeasureText("Settings", 50),50})) &&
                !(CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Credits", 50)/2 , screenHeight/2 + 130,MeasureText("Credits", 50),50}))) selected = 0;
                
                if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Settings", 50)/2 , screenHeight/2 + 30,MeasureText("Settings", 50),50}) && selected == 0)
                    {
                        PlaySound(selectSound2);
                        selected = 1;
                    }
                    
                if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Play", 50)/2 , screenHeight/2 - 50,MeasureText("Play", 50),50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))

                    {
                    currentScreen = LOADING;
                    PlayMusicStream(mainTheme);
                    PlaySound(selectSound);
                    }
                    
                if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Settings", 50)/2 , screenHeight/2 + 30,MeasureText("Settings", 50),50})&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                     currentScreen = SETTINGS;
                     PlaySound(selectSound);
                    }
                    
                if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Credits", 50)/2 , screenHeight/2 + 130,MeasureText("Credits", 50),50}) && selected == 0)
                    {
                        PlaySound(selectSound2);
                        selected = 1;   
                    }
                    
                if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Credits", 50)/2 , screenHeight/2 + 130,MeasureText("Credits", 50),50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        currentScreen = ENDING;
                        PlaySound(selectSound);
                    }
            } break;
            case LOADING: 
            {
                framesCounter++;
                if(framesCounter > /*ADD 5 BEFORE RELEASE*/12)
                {
                    currentScreen = GAMEPLAY;
                    framesCounter = 0;
                }
                        if(framesCounter%5 == 1)enemyFramePosition[1]++;
                        if(enemyFramePosition[1] > 3)enemyFramePosition[1] = 0;
                        enemyFrame[1].x = enemyFramePosition[1] * 64;
                
            } break;
            case GAMEPLAY:
            {  
                //DEBUG MODE
                if(IsKeyPressed(KEY_J))debbugMode = !debbugMode;
                if(debbugMode == 1)
                {
                    if(IsKeyPressed(KEY_U))playerGold+=100;
                }
                        
                framesCounter++;
                
                //Pause Logic
                if (IsKeyPressed(KEY_P))pause = !pause;
                if(pause == 1)StopMusicStream(mainTheme);
                
                
                //Skill Menu
                if (IsKeyPressed(KEY_E))
                {
                    skillMenu = !skillMenu;
                }
                if(skillMenu == 1)
                {   
                    //Trail
                    if (unLockTrail == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,300,256,64}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerGold >= 500)
                    {
                        unLockTrail = 1;
                        playerGold -= 500;
                    }
                    if (unLockTrail == 1 && trailUpgrade == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,400,256,64}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerGold >= 1000)
                    {
                        trailUpgrade = 1;
                        playerGold -= 1000;
                        trailDamage *= 2;
                    }
                    if (trailUpgrade == 1 && trailUpgrade2 == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,500,256,64}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerGold >= 2000)
                    {
                        trailUpgrade2 = 1;
                        playerGold -= 2000;
                        trailDamage *= 3;
                    }
                    //saw
                    if (unLockSaw == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,300,256,64}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerGold >= 100)
                    {
                        unLockSaw = 1;
                        playerGold -= 100;
                    }
                    if (unLockSaw == 1 && sawUpgrade == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,400,256,64}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerGold >= 200)
                    {
                        sawUpgrade = 1;
                        playerGold -= 200;
                        sawDamage *= 2;
                    }
                    if (sawUpgrade == 1 && sawUpgrade2 == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,500,256,64}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerGold >= 300)
                    {
                        sawUpgrade2 = 1;
                        playerGold -= 300;
                        sawDamage *= 3;
                    }
                    //TODO: building 
                }
                
                if (playerLife <= 0) PlaySound(deathSound);//Check Player Death
                
                if (playerLife > 0 && (!pause) && (!skillMenu))
                {               
                    //Weapon
                    
                    dx = mousePosition.x - player.x;
                    dy = mousePosition.y - player.y;
                    
                    angle = atan2f(dy,dx);
                
                    weapon.x = (player.x + player.width/2) + (range*cosf(angle));
                    weapon.y = (player.y + player.height/2) + (range*sinf(angle));
                    
                    //weaponSaw
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && unLockSaw)
                    {
                        weaponSawActive = 1;
                        sawCounter = 30;
                        PlaySound(sawSound);

                    }
                    if(sawCounter > 0)sawCounter--;
                    else weaponSawActive = 0;
                    
                        //slimeTrail
                        if(IsKeyPressed(KEY_LEFT_SHIFT) && trailcoolDown <= 0)
                        {
                            trailRadius = 15;
                            PlaySound(trailSound);
                        }
                        if(unLockTrail == 1 && trailcoolDown <= 0 && IsKeyDown(KEY_LEFT_SHIFT))
                        {
                            trailcoolUp = 0;
                            if(framesCounter%3 == 1)
                            {
                                if(trailCounter < 10)
                                {
                                    trailAlpha = 1.0f;
                                    trailCounter++;
                                    slimeTrail[trailCounter].x = weapon.x;
                                    slimeTrail[trailCounter].y = weapon.y;
                                }
                                else
                                {
                                    trailCounter = 0;
                                    trailcoolUp = 0;
                                    trailcoolDown = 720;
                                }
                                
                            }
                        
                        }
                        if(trailcoolDown > 0)trailcoolDown--;
                        
                        
                        if (trailcoolUp > 400)
                        {
                            for(int i = 0; i < 10; i++)
                            {
                                slimeTrail[i].x = -99;
                                slimeTrail[i].y = -99;
                            }
                        }
                        else 
                        {
                            trailcoolUp++;
                            if(framesCounter%15 == 1)
                            {
                                trailRadius++;
                                trailAlpha -= 0.03f;
                            }
                        }
                    //Player movement                      
                    if (IsKeyDown(KEY_A) && player.x > 0)player.x -= playerSpeed;
                    if (IsKeyDown(KEY_D)&& player.x < screenWidth -player.width)player.x += playerSpeed;                    
                    if (IsKeyDown(KEY_W)&& player.y > 1)player.y -= playerSpeed;
                    if (IsKeyDown(KEY_S)&& player.y < screenHeight -player.height)player.y += playerSpeed;                                                
         
                    animationFrameCounter = 10 - playerSpeed;
                    if((framesCounter % animationFrameCounter) == 1)slimoFrameCounter++;
                    if (slimoFrameCounter > 4)slimoFrameCounter = 0;
                    if (slimoFrameCounter == 1)slimoFrame.x = 0;
                    else if (slimoFrameCounter == 2)slimoFrame.x = 64;
                    else if (slimoFrameCounter == 3)slimoFrame.x = 128;
                    else if (slimoFrameCounter == 4)slimoFrame.x = 64;
                    
                    //enemies
                        //enemy phases

                            if(deadSlimesCounter > 15 && phase == 1)
                            {
                                enemyDamage = 3;
                                for(int i = 1; i < MAX_ENEMIES;i++)
                                    {
                                        enemySpeed[i] += 3;
                                    }
                                phase = 2;
                            }
                            if(deadSlimesCounter > 50 && phase == 2)
                            {
                                enemyDamage += 2;
                                for(int i = 1; i < MAX_ENEMIES;i++)
                                    {
                                        enemySpeed[i] += 3;
                                    }
                                phase = 3;
                            }
                            
                            if(deadSlimesCounter > 100 && phase == 3)
                            {
                                enemyDamage += 3;
                                for(int i = 1; i < MAX_ENEMIES;i++)
                                    {
                                        enemySpeed[i] += 3;
                                    }
                                phase = 4;
                            }
                            if(deadSlimesCounter > 150 && phase == 4)
                            {
                                
                            }

                    
                    for (int i = 1; i < MAX_ENEMIES;i++)
                    {
                        if(framesCounter%5 == 1)enemyFramePosition[i]++;
                        if(enemyFramePosition[i] > 3)enemyFramePosition[i] = 0;
                        enemyFrame[i].x = enemyFramePosition[i] * 64;
                        

                        //enemies  collision with towers
                        if(!CheckCollisionCircleRec(weapon,20,enemy[i]) && enemyAlive[i] &&
                        !CheckCollisionCircleRec((Vector2){player.x + player.width/2,player.y + player.height/2},20,enemy[i]))                        
                        {
                            if(player.x < enemy[i].x &&
                            !(CheckCollisionRecs(buildingTower[0],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[1],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[2],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[3],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[4],enemy[i])))enemy[i].x -= enemySpeed[i];
                            if(player.x > enemy[i].x &&
                            !(CheckCollisionRecs(buildingTower[0],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[1],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[2],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[3],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[4],enemy[i])))enemy[i].x += enemySpeed[i];
                            if(player.y > enemy[i].y &&
                            !(CheckCollisionRecs(buildingTower[0],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[1],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[2],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[3],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[4],enemy[i])))enemy[i].y += enemySpeed[i];
                            if(player.y < enemy[i].y &&
                            !(CheckCollisionRecs(buildingTower[0],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[1],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[2],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[3],enemy[i]))&&
                            !(CheckCollisionRecs(buildingTower[4],enemy[i])))enemy[i].y -= enemySpeed[i];                            
                        }

                        if((CheckCollisionRecs(buildingTower[0],enemy[i])) && enemyAlive[i] == 1 && towerAlive[0] == 1)towerLife[0] -= 1;
                        else enemySpeed[i] = GetRandomValue(1,5);
                        
                        if((CheckCollisionRecs(buildingTower[1],enemy[i])) && enemyAlive[i] == 1 && towerAlive[1] == 1)towerLife[1] -= 1;
                        else enemySpeed[i] = GetRandomValue(1,5);
                        
                        if((CheckCollisionRecs(buildingTower[2],enemy[i])) && enemyAlive[i] == 1 && towerAlive[2] == 1)towerLife[2] -= 1;
                        else enemySpeed[i] = GetRandomValue(1,5);
                        
                        if((CheckCollisionRecs(buildingTower[3],enemy[i])) && enemyAlive[i] == 1 && towerAlive[3] == 1)towerLife[3] -= 1;
                        else enemySpeed[i] = GetRandomValue(1,5);
                        
                        if((CheckCollisionRecs(buildingTower[4],enemy[i])) && enemyAlive[i] == 1 && towerAlive[4] == 1)towerLife[4] -= 1;
                        else enemySpeed[i] = GetRandomValue(1,5);  
                        
                        if(CheckCollisionCircleRec(weapon,20,enemy[i]))
                        {
                            
                            enemyLife[i] -= playerDamage;
                            if(GetRandomValue(0,100) < criticalChance) 
                            {
                                critik = 1;
                                if(weaponSawActive == 1) enemyLife[i] -= sawDamage;
                                else enemyLife[i] -= playerDamage;
                            }
                            else critik = 0;
                        }
                        
                        //Enemy Attacks player
                        if(CheckCollisionCircleRec((Vector2){player.x + player.width/2,player.y + player.height/2},20,enemy[i]) && enemyAlive[i])
                            {

                               
                                playerLife -= enemyDamage;
                                enemyLife[i]--;
                                receivingDMGCounter = 15;
                                enemyMakingDMG = i;
                            }
   
                         
                         if (enemyLife[i] <= 0 && enemyAlive[i] == 1)
                         {
                            enemyFramePosition[i] = 0;
                            enemyAlive[i] = 0;
                            lootPosition[i].x = enemy[i].x;
                            lootPosition[i].y = enemy[i].y;
                            PlaySound(enemyDeathSound);
                            playerGold += 10;
                            deadSlimesCounter++;
                            //if(enemyLoot[i] == 1) PlaySound(appearLoot);
                         }
                        //trail damage
                        for(int j = 0; j < 10;j++)
                        {
                            if(CheckCollisionCircleRec(slimeTrail[j],trailRadius,enemy[i]))
                            {
                                enemyLife[i] -= trailDamage;
                                enemySpeed[i] = 2;
                            }                               
                        }
                        //enemy is dead
                        if(enemyAlive[i] == 0)
                        {
                            if (enemyDeathCounter[i] > 0)enemyDeathCounter[i]--;
                            if (CheckCollisionCircleRec(lootPosition[i],30,player) && enemyLoot[i] == 1)
                            {
                                playerGold += 100;
                                lootPosition[i].x = -999;
                                
                                PlaySound(gotLoot);
                                
                            }
                        }
                    }
                    
                    
                    if(receivingDMGCounter > 0)
                    {
                        receivingDMGCounter--;
                        slimeForce -= 0.1f;
                        
                        if(player.x + player.width/2 < enemy[enemyMakingDMG].x + enemy[enemyMakingDMG].width/2)player.x -= slimeForce;
                        if(player.x + player.width/2 > enemy[enemyMakingDMG].x + enemy[enemyMakingDMG].width/2)player.x += slimeForce;
                        if(player.y + player.height/2 < enemy[enemyMakingDMG].y + enemy[enemyMakingDMG].height/2)player.y -= slimeForce;
                        if(player.y + player.height/2 > enemy[enemyMakingDMG].y + enemy[enemyMakingDMG].height/2)player.y += slimeForce;
                                
                        }
                    else
                    {
                        enemyMakingDMG = 0;
                        
                        slimeForce = 5.0f;
                    }     
                    
                    /*BOSS
                    if(IsKeyPressed(KEY_B) && bossFight == 0)
                    {
                        bossFight = 1;
                        boss.x = screenWidth/2;
                        boss.y = screenHeight/2;
                        
                    }
                    if(bossFight == 1)
                    {
                        if(boss.x + boss.width > screenWidth)bossSpeed.x *= -1;
                        if(boss.x < 0)bossSpeed.x *= -1;
                        if(boss.y + boss.height > screenHeight)bossSpeed.y *= -1;
                        if(boss.x < 0)bossSpeed.y *= -1;
                        boss.x += bossSpeed.x;
                        boss.y += bossSpeed.y;
                    }
                    */
                    if(IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
                    {
                        buildingON = !buildingON;
                    }                    
                    if (buildingON == 1)
                    {
                        placement.x = mousePosition.x;
                        placement.y = mousePosition.y;

                    }
                    towerCD--;
                    if(towerCD < 0)towerCD = 0;
                    for(int i = 0; i < 5;i++)
                    {
                        if(towerLife[i] <= 0)
                        {
                            towerAlive[i] = 0;
                            buildingTower[i].x = -999999999;
                        } 
                    }
                    //Tower
                    if (buildingON == 1 && buildingKind == 1 && towerCD <= 0)
                    {
                        placement.x = mousePosition.x;
                        placement.y = mousePosition.y;
                        
                        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                        {                        
                            towerCD = 900;
                            buildingTower[buildingTCounter].x = mousePosition.x;
                            buildingTower[buildingTCounter].y = mousePosition.y;
                            towerAlive[buildingTCounter] = 1;
                            towerLife[buildingTCounter] = 500;
                            buildingON = !buildingON;
                            PlaySound(buildingSound);
                            buildingTCounter++;
                            if(buildingTCounter > 4)buildingTCounter = 0;
                        }
                        
                    }
                    
                } 
                    if(pause == 1 || playerLife <= 0)
                    {
                        //RESET GAME        
                        if(IsKeyPressed(KEY_R))
                        {
                            playerSpeed = 4;
                            playerLife = 100;
                            playerGold = 0;
                            enemy[MAX_ENEMIES];
                            enemySpeed[MAX_ENEMIES];
                            enemyLife[MAX_ENEMIES];
                            enemyAlive[MAX_ENEMIES];    
                            for (int i = 0; i < MAX_ENEMIES;i++)
                            {
                                enemy[i].x = GetRandomValue(-1000,1000) * i;
                                if(enemy[i].x > 0 && enemy[i].x < screenWidth) enemy[i].x = screenWidth * i;
                                enemy[i].y = GetRandomValue(-1000,1000) * i;
                                if(enemy[i].y > 0 && enemy[i].y < screenHeight) enemy[i].y = screenHeight * i;
                                enemy[i].width = 50;
                                enemy[i].height = 50;
                                enemyLife[i] = GetRandomValue(50,200); 
                                enemySpeed[i] = GetRandomValue(1,4);
                                enemyAlive[i] = 1;
                                enemyLoot[i] = GetRandomValue(0,10);
                                enemyDeathCounter[i] = 12;
                                enemyFramePosition[i] = 0;
                                enemyFrame[i].x = 0;
                                enemyFrame[i].y = 0;
                                enemyFrame[i].width = 64;
                                enemyFrame[i].height = 64;
                            }
                            deadSlimesCounter = 0;
                            enemyDamage = 2;
                            range = 100;    
                            pause = 0;
                            slimeTrail[10];
                            trailCounter = 0;
                            trailcoolUp = 0;
                            trailcoolDown = 0;
                            trailRadius = 15;    
                            framesCounter = 0;                       
                        }
                        for(int i = 0; i < 10; i++)
                        {
                            slimeTrail[i].x = -99;
                            slimeTrail[i].y = -99;
                        }
                        for(int i = 0; i < 5;i++)
                        {
                            buildingTower[i].width = 64;
                            buildingTower[i].height = 64;
                            towerLife[i] = 500;
                            towerAlive[i] = 0;
                        }
                        towerCD = 0;
                        buildingTCounter = 0;
                        buildingON = 0;
                        buildingKind = 1;

                        unLockSaw = 0;
                        sawUpgrade = 0;
                        sawUpgrade2 = 0;
                        sawUpgrade3 = 0;
    
                        unLockTrail = 0;
                        trailUpgrade = 0;
                        trailUpgrade2 = 0;
                        trailUpgrade3 = 0;
    
                        unLockBuilding = 0;
                        buildingUpgrade = 0;
                        buildingUpgrade2 = 0;
                        buildingUpgrade3 = 0;
                    }                 
                } break;
                case ENDING: 
                {
                    // Update ENDING screen data here!
                    
                    // TODO: Replay / Exit game logic....................(0.5p)[x]
                    
                } break;
                case SETTINGS: 
                {
                    if(IsKeyPressed(KEY_ENTER))currentScreen = TITLE; 
                    
                } break;
                default: break;
            }
            
            UpdateMusicStream(mainTheme);
            //----------------------------------------------------------------------------------
            
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            
                ClearBackground(RAYWHITE);
                
                switch(currentScreen) 
                {
                    case LOGO: 
                    {
                        // Draw LOGO screen here!
                       
                        DrawRectangle(0,0,screenWidth,screenHeight,BLACK);
                        DrawTexture(logo,screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, Fade(WHITE,logoAlpha));
                         // DrawText(FormatText("%i", logoAlpha ), 125,50,25,YELLOW);

                        
                    } break;
                    case TITLE: 
                    {
                        // Draw TITLE screen here!
                       
                        DrawRectangle(0,0,screenWidth,screenHeight,SKYBLUE);
                        DrawTexture(titlename,screenWidth/2 - titlename.width/2, 50,WHITE);
                        // TODO: Draw Title texture......................(0.5p)
                        
                        // TODO: Draw "PRESS ENTER" message..............(0.5p)
                        DrawTextEx(fontforHUD,"Play", (Vector2){screenWidth/2 - MeasureText("Play", 50)/2 , screenHeight/2 - 20}, 50,5,WHITE);
                        if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Play", 50)/2 , screenHeight/2 - 50,MeasureText("Play", 50),50}))
                        {
                            DrawTextEx(fontforHUD,"Play", (Vector2){screenWidth/2 - MeasureText("Play", 55)/2 , screenHeight/2 - 20}, 55,5,Fade(WHITE,0.5f));
                        }
                        
                        DrawTextEx(fontforHUD,"Settings", (Vector2){screenWidth/2 - MeasureText("Settings", 50)/2 , screenHeight/2 + 70}, 50,5,WHITE); 
                        if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Settings", 50)/2 , screenHeight/2 + 30,MeasureText("Settings", 50),50}))
                        {
                            DrawTextEx(fontforHUD,"Settings", (Vector2){screenWidth/2 - MeasureText("Settings", 55)/2 , screenHeight/2 + 70}, 55,5,Fade(WHITE,0.5f));
                        }
                        DrawTextEx(fontforHUD,"Credits", (Vector2){screenWidth/2 - MeasureText("Credits", 50)/2 , screenHeight/2 + 170}, 50,5,WHITE); 
                        if (CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - MeasureText("Credits", 50)/2 , screenHeight/2 + 130,MeasureText("Credits", 50),50}))
                        {
                            DrawTextEx(fontforHUD,"Credits", (Vector2){screenWidth/2 - MeasureText("Credits", 55)/2 , screenHeight/2 + 170}, 55,5,Fade(WHITE,0.5f));
                        }
                        DrawText("Alpha 0.0.5", screenWidth - 200,screenHeight-50,20,YELLOW);
                        DrawTexture(cursor,mousePosition.x, mousePosition.y,WHITE);
                    } break;
                    case LOADING: 
                    {
                        DrawRectangle(0,0,screenWidth,screenHeight,BLACK);
                        DrawTexture(instructions,200,200,WHITE);
                        DrawRectangle(0,screenHeight - 210,250 + framesCounter * 2,50,RED);
                        DrawText("Loading",framesCounter,screenHeight - 200,30,WHITE);
                        DrawTextureRec(enemyTileSet,enemyFrame[1],(Vector2){framesCounter + 30,screenHeight-270},WHITE);
                
                    } break;
                    case GAMEPLAY:
                    { 
                        // Draw GAMEPLAY screen here!
                        

                        DrawRectangle(0,0,screenWidth,screenHeight,SKYBLUE);
                        DrawTexture(backGround,0,0,WHITE);

                        if (trailcoolUp < 400)
                        {
                            for(int i = 0; i < 10; i++)
                            {
                                DrawCircleV(slimeTrail[i],trailRadius,Fade(DARKGREEN,trailAlpha));
                            }
                        }
                        
                        for(int i = 0; i < 5;i++)
                        {
                            if(towerAlive[i] == 1)
                            {
                                DrawTexture(buildingTowerTexture,buildingTower[i].x,buildingTower[i].y,WHITE);
                                DrawRectangle(buildingTower[i].x + buildingTower[i].width/2 - towerLife[i]/8, buildingTower[i].y - 20, towerLife[i]/4, 5, GREEN);
                            }
                        }
                        if (buildingON)
                        {
                            DrawRectangleLines(placement.x+10,placement.y+15,placement.width, placement.height,RED);
                            if(towerCD == 0)DrawTexture(buildingTowerTexture,placement.x ,placement.y ,Fade(GREEN,0.3f));
                            else if (towerCD > 0)DrawTexture(buildingTowerTexture,placement.x ,placement.y ,Fade(RED,0.3f));
                        }
                        
                        for (int i = 1; i < MAX_ENEMIES;i++)
                        {
                            if(enemyAlive[i] && enemy[i].x > -200 && enemy[i].x < screenWidth + 200 && enemy[i].y > -200 && enemy[i].y < screenHeight + 200)
                            {
                                
                                DrawTextureRec(enemyTileSet,enemyFrame[i],(Vector2){enemy[i].x -5,enemy[i].y - 5},WHITE);
                                DrawRectangle(enemy[i].x + enemy[i].width/2 - enemyLife[i]/4, enemy[i].y - 20, enemyLife[i]/2, 5, RED);
                                if(CheckCollisionCircleRec(weapon,20,enemy[i]))DrawText(FormatText("%i",playerDamage),enemy[i].x,enemy[i].y,12,YELLOW);
                                if((critik == 1) && CheckCollisionCircleRec(weapon,20,enemy[i]))DrawText(FormatText("%i",playerDamage),enemy[i].x,enemy[i].y -15,17,RED); 
                               
                            }
                            if(enemyAlive[i] == 0 && enemyLoot[i] == 1)
                            {
                                DrawTexture(lootball,lootPosition[i].x + 15,lootPosition[i].y +15,WHITE);
                            }
                            if(enemyAlive[i] == 0 && enemyDeathCounter[i] > 0)
                            {
                                if(enemyLoot[i] != 1)DrawTextureRec(enemyDeath,enemyFrame[i],(Vector2){enemy[i].x -5,enemy[i].y - 5},WHITE);
                                else DrawTextureRec(enemyDeathLoot,enemyFrame[i],(Vector2){enemy[i].x -5,enemy[i].y - 5},WHITE);

                            }
                            
                            
                            //NOTE: Enemies are not being Drawn while far from the player
                        } 
                        /*BOSS
                        if(bossFight == 1)
                        {
                            DrawTexture(bossTexture,boss.x,boss.y,WHITE);
                        }*/
                        
                        //DRAW SAW
                        if(weaponSawActive == 0)DrawTexture(slimoball,weapon.x - (slimoball.width/2),weapon.y - (slimoball.height/2),WHITE);                        
                        else if (weaponSawActive == 1)DrawTexture(slimoballSaw,weapon.x - (slimoballSaw.width/2),weapon.y - (slimoballSaw.height/2),WHITE);
                        
                        //DRAW PLAYER
                        if (receivingDMGCounter > 0)
                        {
                            DrawTextureRec(slimo,slimoFrame,(Vector2){player.x,player.y},Fade(PINK,1.0f/(5.0f - slimeForce)));
                            //Makes Dmg FX.
                        }
                        else
                        {
                            DrawTextureRec(slimo,slimoFrame,(Vector2){player.x,player.y},Fade(WHITE,0.8));
                        }
                        
                        
                        //GUI bars
                        DrawTextureRec(circle, (Rectangle){0,57 - trailcoolDown/14 ,57,trailcoolDown/14}, (Vector2){102, 84 - trailcoolDown/14},Fade(RED,0.5f));                     
                        if(trailcoolDown == 0)DrawTextureRec(circle, (Rectangle){0,0,57,57}, (Vector2){102, 27},Fade(GREEN,0.5f));
                        
                        DrawTextureRec(circle, (Rectangle){0,57 - towerCD/16 ,57,towerCD/16}, (Vector2){194, 84 - towerCD/16},Fade(RED,0.5f));
                        if(towerCD == 0)DrawTextureRec(circle, (Rectangle){0,0,57,57}, (Vector2){194, 27},Fade(GREEN,0.5f));
                        
                        DrawTextEx(fontforHUD,FormatText("%i", trailcoolDown/60 ), (Vector2){120,70},45,5,YELLOW);  
                        DrawTextEx(fontforHUD,FormatText("%i", towerCD/60 ), (Vector2){210,70},45,5,YELLOW); 
                        DrawTextEx(fontforHUD,FormatText("Gold: %i", playerGold ), (Vector2){410,70},45,5,YELLOW); 
                        
                        DrawTexture(GUIBars, 100,25,WHITE);
                         
                        
                        //LIFEBAR
                        DrawRectangle(27,64 + ((float){240} - (float){playerLife * 240 /100}) ,40, (float){playerLife * 240 /100}, Fade(GREEN,0.9));
                        DrawTexture(lifeBar,15,50,WHITE);  
                        
                        if(playerLife <= 0)
                        {
                            DrawRectangle(0,0,screenWidth,screenHeight,Fade(BLACK,0.5));
                            
                            DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER", 40)/2 , screenHeight/2 - 20, 40,WHITE);
                            DrawText("PRESS R TO RESTART", screenWidth/2 - MeasureText("PRESS R TO RESTART", 15)/2 , screenHeight/2 + 80, 15,WHITE);
                            //DrawText(FormatText("HIGH SCORE: %i", highScore),  screenWidth/2 - MeasureText("HIGH SCORE: %i", 20)/2 , screenHeight/2 + 20, 20,YELLOW);
                        }
                        if(pause)
                        {
                            DrawRectangle(0,0,screenWidth,screenHeight,Fade(BLACK,0.5));
                            if((framesCounter/40) %2)DrawText("PAUSE", screenWidth/2 - MeasureText("PAUSE", 40)/2 , screenHeight/2 - 20, 40,WHITE);
                            PauseMusicStream(mainTheme);
                        }
                        //Skill Menu
                        if(skillMenu)
                        {
                            DrawRectangle(100,100,screenWidth - 200,screenHeight -200,Fade(BLACK,0.5));
                            
                            //Trail
                            DrawTexture(trailIcon, screenWidth/2 - 300 - trailIcon.width/2,200,WHITE);
                            
                            //Trail I
                            if (unLockTrail == 0 && !CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,300,256,64}))
                                {
                                    DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,300},WHITE);
                                    DrawText("Unlock",screenWidth/2 - 380, 320, 30, GREEN);
                                }
                            else if (unLockTrail == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,300,256,64}) && playerGold < 500)
                                {
                                    DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,300},RED);
                                    DrawText("500Gold",screenWidth/2 - 380, 320, 30, BLACK);
                                }
                            else if (unLockTrail == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,300,256,64}))
                                {
                                    DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,300},GREEN);
                                    DrawText("500Gold",screenWidth/2 - 380, 320, 30, BLACK);
                                }
                            else if (unLockTrail == 1)
                            {
                                DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,300},WHITE);
                                DrawText("Unlocked",screenWidth/2 - 380, 320, 30, GREEN);
                            }
                            
                            //Trail II
                            if (trailUpgrade == 0 && !CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,400,256,64}))
                                {
                                    if(unLockTrail == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,400},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,400},WHITE);
                                    DrawText("x2 Damage",screenWidth/2 - 380, 420, 30, GREEN);
                                }
                            else if (trailUpgrade == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,400,256,64}) && playerGold < 1000)
                                {
                                    if(unLockTrail == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,400},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,400},RED);
                                    DrawText("1000Gold",screenWidth/2 - 380, 420, 30, BLACK);
                                }
                            else if (trailUpgrade == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,400,256,64}))
                                {
                                    if(unLockTrail == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,400},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,400},GREEN);
                                    DrawText("1000Gold",screenWidth/2 - 380, 420, 30, BLACK);
                                }
                            else if (trailUpgrade == 1)
                            {
                                DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,400},WHITE);
                                DrawText("x2 Damage",screenWidth/2 - 380, 420, 30, GREEN);
                            }
                            
                            //Trail III
                            if (trailUpgrade2 == 0 && !CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,500,256,64}))
                                {
                                    if(trailUpgrade == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,500},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,500},WHITE);
                                    DrawText("x3 Damage",screenWidth/2 - 380, 520, 30, GREEN);
                                }
                            else if (trailUpgrade2 == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,500,256,64}) && playerGold < 2000)
                                {
                                    if(trailUpgrade == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,500},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,500},RED);
                                    DrawText("2000Gold",screenWidth/2 - 380, 520, 30, BLACK);
                                }
                            else if (trailUpgrade2 == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 400,500,256,64}))
                                {
                                    if(trailUpgrade == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 400,500},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,500},GREEN);
                                    DrawText("2000Gold",screenWidth/2 - 380, 520, 30, BLACK);
                                }
                            else if (trailUpgrade2 == 1)
                            {
                                DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 400,500},WHITE);
                                DrawText("x3 Damage",screenWidth/2 - 380, 520, 30, GREEN);
                            }
                            
                            //Saw
                            DrawTexture(sawIcon, screenWidth/2 - sawIcon.width/2, 200,WHITE);
                            //Saw I
                            if (unLockSaw == 0 && !CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,300,256,64}))
                                {
                                    DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,300},WHITE);
                                    DrawText("Unlock",screenWidth/2 - 80, 320, 30, GREEN);
                                }
                            else if (unLockSaw == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,300,256,64}) && playerGold < 100)
                                {
                                    DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,300},RED);
                                    DrawText("100Gold",screenWidth/2 - 80, 320, 30, BLACK);
                                }
                            else if (unLockSaw == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,300,256,64}))
                                {
                                    DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,300},GREEN);
                                    DrawText("100Gold",screenWidth/2 - 80, 320, 30, BLACK);
                                }
                            else if (unLockSaw == 1)
                            {
                                DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,300},WHITE);
                                DrawText("Unlocked",screenWidth/2 - 80, 320, 30, GREEN);
                            }
                            //Saw II
                            if (sawUpgrade == 0 && !CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,400,256,64}))
                                {
                                    if(unLockSaw == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,400},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,400},WHITE);
                                    DrawText("x2 Damage",screenWidth/2 - 80, 420, 30, GREEN);
                                }
                            else if (sawUpgrade == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,400,256,64}) && playerGold < 200)
                                {
                                    if(unLockSaw == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,400},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,400},RED);
                                    DrawText("200Gold",screenWidth/2 - 80, 420, 30, BLACK);
                                }
                            else if (sawUpgrade == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,400,256,64}))
                                {
                                    if(unLockSaw == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,400},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,400},GREEN);
                                    DrawText("200Gold",screenWidth/2 - 80, 420, 30, BLACK);
                                }
                            else if (sawUpgrade == 1)
                            {
                                DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,400},WHITE);
                                DrawText("x2 Damage",screenWidth/2 - 80, 420, 30, GREEN);
                            }
                            //DrawRectangle(screenWidth/2 - 100,500,200,50,WHITE);
                            if (sawUpgrade2 == 0 && !CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,500,256,64}))
                                {
                                    if(sawUpgrade == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,500},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,500},WHITE);
                                    DrawText("x3 Damage",screenWidth/2 - 80, 520, 30, GREEN);
                                }
                            else if (sawUpgrade2 == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,500,256,64}) && playerGold < 300)
                                {
                                    if(sawUpgrade == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,500},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,500},RED);
                                    DrawText("300Gold",screenWidth/2 - 80, 520, 30, BLACK);
                                }
                            else if (sawUpgrade2 == 0 && CheckCollisionPointRec(mousePosition,(Rectangle){screenWidth/2 - 100,500,256,64}))
                                {
                                    if(sawUpgrade == 0)DrawTextureRec(unLockTexture,(Rectangle){0,0,255,73},(Vector2){screenWidth/2 - 100,500},GRAY);
                                    else DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,500},GREEN);
                                    DrawText("300Gold",screenWidth/2 - 80, 520, 30, BLACK);
                                }
                            else if (sawUpgrade2 == 1)
                            {
                                DrawTextureRec(unLockTexture,(Rectangle){255,0,255,73},(Vector2){screenWidth/2 - 100,500},WHITE);
                                DrawText("x3 Damage",screenWidth/2 - 80, 520, 30, GREEN);
                            }
                            
                            DrawTexture(buildingIcon, screenWidth/2 + 300 - buildingIcon.width/2,200,WHITE);
                            DrawRectangle(screenWidth/2 + 200,300,200,50,WHITE);
                            DrawRectangle(screenWidth/2 + 200,400,200,50,WHITE);
                            DrawRectangle(screenWidth/2 + 200,500,200,50,WHITE);
                        }
                        //if(IsMusicPlaying)DrawText("MUSIC IS PLAYING", screenWidth/2 - MeasureText("MUSIC IS PLAYING", 40)/2 , screenHeight/2 - 20, 40,WHITE);
                    
                    DrawTexture(cursor,mousePosition.x, mousePosition.y,WHITE);
                    
                } break;
                case ENDING: 
                {
                    // Draw END screen here!
                    DrawRectangle(0,0,screenWidth,screenHeight,BLACK);
                    DrawText("Congratulations, you could beat my game\n -Daniel 'RyuuSuke' Carmona",150,screenHeight/2 - 60,30,WHITE);
                    // TODO: Draw ending message (win or loose)......(0.5p)
                    
                } break;
                case SETTINGS: 
                {
                    
                    DrawRectangle(0,0,screenWidth,screenHeight,YELLOW);
                    DrawTexture(cursor,mousePosition.x, mousePosition.y,WHITE);
                    
                } break;
                default: break;
            }
        
            DrawFPS(10, 10);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // TODO: Unload textures, spritefonts, sounds and music
    
    CloseAudioDevice();
    //Textures
    UnloadTexture(titlename);
    UnloadTexture(cursor);
    UnloadTexture(slimo);
    UnloadTexture(slimoball);
    UnloadTexture(slimoballSaw);
    UnloadTexture(lifeBar);
    UnloadTexture(GUIBars);
    UnloadTexture(enemyTileSet);
    UnloadTexture(enemyDeath);
    UnloadTexture(enemyDeathLoot);
    UnloadTexture(enemyTileSet);
    UnloadTexture(backGround);
    UnloadTexture(logo);
    UnloadTexture(buildingTowerTexture);
    UnloadTexture(lootball);
    UnloadTexture(sawIcon);
    UnloadTexture(buildingIcon);
    UnloadTexture(trailIcon);
    UnloadTexture(bossTexture);
    UnloadTexture(instructions);
    UnloadTexture(slimeBlood);
    //UnloadTexture(unLockTexture);
    
    //UnloadSpriteFont(curly);
    UnloadSpriteFont(fontforHUD);
    //Music
    UnloadMusicStream(mainTheme);

    UnloadSound(selectSound);
    UnloadSound(selectSound2);
    UnloadSound(deathSound);
    UnloadSound(enemyDeathSound);
    UnloadSound(gotLoot);
    //UnloadSound(appearLoot);
    UnloadSound(trailSound);
    UnloadSound(buildingSound);
    UnloadSound(sawSound); 

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}
