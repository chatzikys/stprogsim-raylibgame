/*
█▀ ▀█▀ █▀█ █░█ █▀▀ ▀█▀ █░█ █▀█ █▀▀ █▀▄   █▀█ █▀█ █▀█ █▀▀ █▀█ ▄▀█ █▀▄▀█ █▀▄▀█ █ █▄░█ █▀▀   █▀ █ █▀▄▀█ █░█ █░░ ▄▀█ ▀█▀ █▀█ █▀█
▄█ ░█░ █▀▄ █▄█ █▄▄ ░█░ █▄█ █▀▄ ██▄ █▄▀   █▀▀ █▀▄ █▄█ █▄█ █▀▄ █▀█ █░▀░█ █░▀░█ █ █░▀█ █▄█   ▄█ █ █░▀░█ █▄█ █▄▄ █▀█ ░█░ █▄█ █▀▄

█▀▄▀█ ▄▀█ █▀▄ █▀▀   █▄▄ █▄█   █▀▀ █░█ ▄▀█ ▀█▀ ▀█ █ █▄▀ █▄█ █▀ 
█░▀░█ █▀█ █▄▀ ██▄   █▄█ ░█░   █▄▄ █▀█ █▀█ ░█░ █▄ █ █░█ ░█░ ▄█ 
*/
/*
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/ or send a letter to Creative Commons,
PO Box 1866, Mountain View, CA 94042, USA.
*/
#include <stdio.h>
#include <stdlib.h>
#include "include\raylib.h"
#include "movement.h"
#include "game.h"
#include "map.h"
#include "questions.h"

const int screenWidth = Width;
const int screenHeight = Height;
float block_size = blocksize;
Vector2 spawnpoint;
enum AppStates AppState = Loading;
enum Win_Lose wincondition = Blank;

int main(void)
{
	// Initialize the window
	InitWindow(screenWidth, screenHeight, "Structured Programming Simulator");
	InitAudioDevice();
	// FramesCounter
	int framesCounter = 0;

	// Initialize player
	struct player *PlayerChar_ptr, PlayerChar;
	PlayerChar_ptr = &PlayerChar;

	// Remove the default Exit Key
	SetExitKey(KEY_NULL);

	// Exit Logic
	bool exitWindowRequested = false;
	bool exitWindow = false;

	// Draw map to change the spawnpoint
	UpdateMap(map);
	initPlayer(PlayerChar_ptr, spawnpoint);

	// Initialize textures
	Texture2D characterTexture = LoadTexture("./assets/images/sprite.png");
	Texture2D codesnip = LoadTexture("./assets/images/codesnip.png");
	Sound music = LoadSound("assets/sounds/mus.wav");
	SetSoundVolume(music, 0.3);
	PlaySound(music);
	Rectangle *fr;
	Rectangle frameRec = {0.0f, 0.0f, (float)characterTexture.width / 4, (float)characterTexture.height / 3};
	fr = &frameRec;
	// Used to keep Time
	int timelim = 100;
	int pause = 0;
	// Set up the game loop
	SetTargetFPS(30);
	while (!WindowShouldClose() && !exitWindow)
	{
		if (IsKeyPressed(KEY_M))
		{
			if (IsSoundPlaying(music))
			{
				PauseSound(music);
				pause = 1;
			}
			else
			{
				ResumeSound(music);
				pause = 0;
			}
		}
		if (pause == 0 && !IsSoundPlaying(music))
		{
			PlaySound(music);
		}
		// Main Window/Menu Logic
		switch (AppState)
		{
		case Loading:
		{ // Countint to 2 seconds
			framesCounter++;
			if (framesCounter > 60)
			{
				AppState = Menu;
				framesCounter = 0;
			}
		}
		break;
		case Menu:
		{
			framesCounter += 10;
			if (IsKeyPressed(KEY_S))
			{
				framesCounter = 0;
				AppState = Game;
			}
		}
		break;
		case Game:
		{
			framesCounter++;
			if ((1160 / timelim * framesCounter / 30) >= 1160)
			{
				wincondition = Lose;
				framesCounter = 0;
				AppState = GameEnd;
			}
			else if (IsKeyPressed(KEY_R))
			{
				wincondition = Lose;
				framesCounter = 0;
				AppState = GameEnd;
			}
		}
		break;
		case Questions:
		{
			if (IsKeyPressed(KEY_ESCAPE))
			{
				AppState = Game;
			}
		}
		break;
		case Final:
		{
			if (IsKeyPressed(KEY_ESCAPE))
			{
				AppState = Game;
			}
			if (IsKeyPressed(KEY_ENTER))
			{
				framesCounter = 0;
			}
		}
		break;
		case GameEnd:
		{
			framesCounter += 6;
			if (IsKeyPressed(KEY_ENTER))
			{
				AppState = Quit;
				framesCounter = 0;
			}
		}
		break;
		case Quit:
		{
			framesCounter += 6;
			if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
				exitWindowRequested = true;
			if (exitWindowRequested)
				if (IsKeyPressed(KEY_Y))
					exitWindow = true;
				else if (IsKeyPressed(KEY_N))
					exitWindowRequested = false;
		}
		break;
		default:
			break;
		}
		BeginDrawing();
		ClearBackground(DARKGRAY);
		switch (AppState)
		{
		case Loading:
		{
			DrawText("LOADING", 20, 20, 40, LIGHTGRAY);
			DrawText("Please Wait....", 20, screenHeight - 70, 30, LIGHTGRAY);
			DrawRectangle(20, screenHeight - 40, 140 / 60 * framesCounter, 30, BLUE);
		}
		break;
		case Menu:
		{
			DrawText("MENU", 20, 20, 40, LIGHTGRAY);
			DrawText(TextSubtext("YEAR:2222\nYou have just been awoken from cryogenic sleep,\nthe world has changed a lot since you were put to sleep,\nbut dont be sad, because you will have lots of fun here.\nWhile you where asleep your family sold you to our company,\nOur identity or location should not matter to you right now.\nYou have a chance to redeem yourself, even become famous,\nand earn a huge amount of cash. \nThe only catch is that you have to escape this underground \"escape room\"\nThis is basicaly a maze filled with doors\nTo open a door you have to answer a simple question about the C programming language,\nalso keep in mind that there is a timer for this \"challenge\".\nThese rooms are currently filling up with water so I'd recommend that you get started before you are unable to,\nwhat are you waiting for, the exit is the PURPLE door.\nCONTROLS\nARROW KEYS TO MOVE\nA - B - C - D TO CHOOSE THE(HOPEFULLY CORRECT) ANSWER\nIF YOU GET STUCK YOU CAN PRESS R TO END THE GAME.\nM TO MUTE THE MUSIC\nThats it, See you on the other side.\n(Try to answer all the questions without making mistakes, who knows what will happen)", 0, framesCounter / 2), 29, 60, 20, RAYWHITE);
			DrawText("Press S to start game:", 20, screenHeight - 70, 30, LIGHTGRAY);
		}
		break;
		case Game:
		{ // Updates The posision of the player, then updates the map, and then draws the player model
			UpdatePlayerPos(PlayerChar_ptr, fr);
			UpdateMap(map);
			if (characterTexture.id == NULL)
			{
				DrawRectangle(PlayerChar.player_rect.x, PlayerChar.player_rect.y, PlayerChar.player_rect.width, PlayerChar.player_rect.height, PlayerChar.color);
			}
			DrawTexturePro(characterTexture, frameRec, PlayerChar.player_rect, (Vector2){0.0}, 0.0f, WHITE);
			// Draws the water level rectangle
			DrawRectangle(60, screenHeight - 60, 1160 / timelim * framesCounter / 30, 30, BLUE);
			DrawRectangleLines(60, screenHeight - 60, 1160, 30, DARKBLUE); // 1160
			WaitTime(0.08);
		}
		break;
		case Questions:
		{
			DrawText("QUESTION", 20, 20, 40, LIGHTGRAY);
			DrawQuestions();
		}
		break;
		case Final:
		{
			DrawText("EXIT", 20, 20, 40, LIGHTGRAY);
			DrawFinalQuestion(codesnip);
		}
		break;
		case GameEnd:
		{
			switch (wincondition)
			{
			case Win:
			{
				DrawText("YOU WON!!", 20, 20, 40, LIGHTGRAY);
				DrawText(TextSubtext("\"I see you managed to escape, \nI hope you enjoyed this Escape Room as much as I think, \nsee you next time. \"", 0, framesCounter / 2), 29, 60, 20, RAYWHITE);
				DrawText("Press Enter To Continue", 20, screenHeight - 70, 30, LIGHTGRAY);
			}
			break;
			case Lose:
			{
				DrawText("GAME OVER", 20, 20, 40, LIGHTGRAY);
				DrawText(TextSubtext("\"Did you really expect not to fail this, \nwhen you didnt even study for the finals next week,\nbetter luck next time.\"", 0, framesCounter / 2), 29, 60, 20, RAYWHITE);
				DrawText("Press Enter To Continue", 20, screenHeight - 70, 30, LIGHTGRAY);
			}
			break;
			case FullClear:
			{
				DrawText("NICE!!! (SECRET ENDING)", 20, 20, 40, LIGHTGRAY);
				DrawText(TextSubtext("\"This is unexpected, \nyou did pretty well didnt you,\nYou didnt just escape but complete all the questions before that.\nI am certain that you will become a great programmer\"", 0, framesCounter / 2), 29, 60, 20, RAYWHITE);
				DrawText("Press Enter To Continue", 20, screenHeight - 70, 30, LIGHTGRAY);
			}
			break;
			default:
			{
				DrawText("SOMETHING WENT WRONG", 20, 20, 40, LIGHTGRAY);
			}
			break;
			}
		}
		break;
		case Quit:
		{
			if (exitWindowRequested)
			{
				DrawRectangle(0, 100, screenWidth, 200, BLACK);
				DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
			}
			else
			{
				DrawText("Press ESC to close the Game.", 20, 20, 40, LIGHTGRAY);
				DrawText(TextSubtext("This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. \nTo view a copy of this license, visit http ://creativecommons.org/licenses/by-sa/4.0/ \nor send a letter to Creative Commons, \nPO Box 1866, Mountain View, CA 94042, USA.", 0, framesCounter / 2), 29, 60, 20, RAYWHITE);
			}
		}
		break;
		}
		if (pause == 1)
		{
			DrawText("MUTED", screenWidth - 100, screenHeight - 20, 20, RED);
		}
		DrawText("made by @chatzikys for Structured Programming 2022-2023 ECE-AUTH", 300, screenHeight - 20, 20, LIGHTGRAY);
		EndDrawing();
	}

	UnloadSound(music); // Unload sound data
	CloseAudioDevice();
	// Close the window and exit
	CloseWindow();
	return 0;
}
