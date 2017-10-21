#include "raylib.h"

DisplayMenu(int screenHeight, int screenWidth, Texture2D trailIcon,bool unLockTrail, Vector2 mousePosition, Texture2D unLockTexture, int playerGold,bool trailUpgrade, bool trailUpgrade2, Texture2D sawIcon, bool unLockSaw, bool sawUpgrade, bool sawUpgrade2, Texture2D buildingIcon)
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
                            //saw III
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
                            
    return 0;
}