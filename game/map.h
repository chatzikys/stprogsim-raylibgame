/*
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/ or send a letter to Creative Commons,
PO Box 1866, Mountain View, CA 94042, USA.
*/
#include <stdio.h>
#include "include\raylib.h"
#include "game.h"
#pragma once

extern Vector2 spawnpoint;
enum AppStates AppState;

int map[(int)Height / blocksize][(int)Width / blocksize] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
		{1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
		{1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 1, 1, 0, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 2, 0, 0, 2, 1},
		{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 2, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 6, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 2, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // LEAVE BLANK FOR HUD
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // LEAVE BLANK FOR HUD
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// Function that draws the specified block in its place.
void DrawBlock(int i, int j, enum Block block)
{
	switch (block)
	{
	case Air:
		DrawRectangle(j * blocksize, i * blocksize, blocksize, blocksize, LIGHTGRAY);
		break;
	case Wall:
		DrawRectangle(j * blocksize, i * blocksize, blocksize, blocksize, BLACK);
		break;
	case Door:
		DrawRectangle(j * blocksize, i * blocksize, blocksize, blocksize, YELLOW);
		break;
	case Spawn:
		DrawRectangle(j * blocksize, i * blocksize, blocksize, blocksize, GREEN);
		spawnpoint = (Vector2){(float)j, (float)i};
		break;
	case DoorLocked:
		DrawRectangle(j * blocksize, i * blocksize, blocksize, blocksize, RED);
		break;
	case Exit:
		DrawRectangle(j * blocksize, i * blocksize, blocksize, blocksize, VIOLET);
		break;
	default:
		DrawRectangle(j * blocksize, i * blocksize, blocksize, blocksize, RAYWHITE);
		break;
	}
	return;
}
// Function that goes through the array and passes each block position and type to the DrawBlock function.
void UpdateMap(int map[][(int)Width / blocksize])
{
	enum Block block;
	for (int i = 0; i < (int)Height / blocksize; ++i)
	{
		for (int j = 0; j < (int)Width / blocksize; ++j)
		{
			block = map[i][j];
			DrawBlock(i, j, block);
		}
	}
}

Vector2 currentdoor;
// Checks for Collision and Corects the player position if there is ,also it provides the basic block detection for the functionality of the game
int CollisionDetect(int map[][(int)Width / blocksize], struct player *chara, enum direction dir)
{
	Rectangle offset = {0, 0};

	switch (dir)
	{
	case Right:
		offset.x = 1 * blocksize;
		break;
	case Left:
		offset.x = -1 * blocksize;
		break;
	case Up:
		offset.y = -1 * blocksize;
		break;
	case Down:
		offset.y = 1 * blocksize;
		break;
	}
	enum Block block;
	for (int i = 0; i < (int)Height / blocksize; ++i)
	{
		for (int j = 0; j < (int)Width / blocksize; ++j)
			if (chara->player_rect.y + offset.y == i * blocksize)
			{
				if (chara->player_rect.x + offset.x == j * blocksize)
				{
					printf("%d:%d:%d\n", j, i, map[i][j]);
					block = map[i][j];
					switch (block)
					{
					case Wall:
					{
						puts("Wall");
						chara->p.x -= offset.x;
						chara->p.y -= offset.y;
					}
					break;
					case DoorLocked:
					{
						puts("Locked Door");
						chara->p.x -= offset.x;
						chara->p.y -= offset.y;
					}
					break;
					case Door:
					{
						puts("Door");
						chara->p.x -= offset.x;
						chara->p.y -= offset.y;
						currentdoor.x = (float)j;
						currentdoor.y = (float)i;
						AppState = Questions;
					}
					break;
					case Exit:
					{
						puts("Final");
						chara->p.x -= offset.x;
						chara->p.y -= offset.y;
						AppState = Final;
					}
					break;
					}
					offset.x = 0;
					offset.y = 0;
				}
			}
	}
}

// Cleand the current door
void ClearDoor()
{
	puts("Clearing");
	map[(int)currentdoor.y][(int)currentdoor.x] = DoorOpen;
}

// Locks the current door
void LockDoor()
{
	puts("Locking");
	map[(int)currentdoor.y][(int)currentdoor.x] = DoorLocked;
}
