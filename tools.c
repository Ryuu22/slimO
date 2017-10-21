#include "raylib.h"
#define MAX_ENEMIES 200

void ResetGame(int screenWidth, int screenHeight, int playerSpeed, int playerLife, int playerGold, int enemyX[MAX_ENEMIES],int enemyFramePosition[MAX_ENEMIES], Rectangle enemyFrame[MAX_ENEMIES],int enemyDeathCounter[MAX_ENEMIES], float enemySpeed[MAX_ENEMIES],bool enemyLoot[MAX_ENEMIES], int enemyLife[MAX_ENEMIES], int enemyAlive[MAX_ENEMIES],int deadSlimesCounter, int enemyDamage,float range, bool pause, Vector2 slimeTrail[10],int trailCounter, float trailcoolUp, float trailcoolDown, float trailRadius, int framesCounter, int towerCD, Rectangle buildingTower[5],int towerLife[5], int towerAlive[5],int buildingTCounter, bool buildingON, int buildingKind, bool unLockSaw, bool sawUpgrade, bool sawUpgrade2, bool sawUpgrade3, bool unLockTrail, bool trailUpgrade, bool trailUpgrade2, bool trailUpgrade3, bool unLockBuilding, bool buildingUpgrade, bool buildingUpgrade2, bool buildingUpgrade3)
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
    
    return 0;
}