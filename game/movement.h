/*
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/ or send a letter to Creative Commons,
PO Box 1866, Mountain View, CA 94042, USA.
*/
#include "game.h"
#pragma once

extern const int screenWidth;
extern const int screenHeight;
extern float block_size;

extern int map[(int)Height / blocksize][(int)Width / blocksize];

void UpdatePlayerDir(Rectangle *rec, struct player *chara);
void CheckBounds(struct player *chara);

// Sets the basic player position, direction
void initPlayer(struct player *ptr, Vector2 spawn)
{
	ptr->p.x = spawn.x * block_size;
	ptr->p.y = spawn.y * block_size;
	ptr->h = ptr->w = block_size;
	ptr->dir = WasRight;
	ptr->color = RED;
	ptr->player_rect = (Rectangle){
		ptr->p.x,
		ptr->p.y,
		ptr->h,
		ptr->w,
	};
}

// Updates Player Movement and Texture
void UpdatePlayerPos(struct player *chara, Rectangle *rec)
{
	if (IsKeyDown(KEY_UP))
	{

		chara->p.y -= block_size;
		WaitTime(0.01);
		CollisionDetect(map, chara, Up);
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		chara->p.y += block_size;
		WaitTime(0.01);
		CollisionDetect(map, chara, Down);
	}
	else if (IsKeyDown(KEY_RIGHT))
	{

		chara->p.x += block_size;
		WaitTime(0.01);
		CollisionDetect(map, chara, Right);
		if (chara->dir != WasRight)
		{
			chara->dir = Right;
			UpdatePlayerDir(rec, chara);
			chara->dir = WasRight;
		}
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		chara->p.x -= block_size;
		CollisionDetect(map, chara, Left);
		WaitTime(0.01);
		if (chara->dir != WasLeft)
		{
			chara->dir = Left;
			UpdatePlayerDir(rec, chara);
			chara->dir = WasLeft;
		}
	}
	CheckBounds(chara);
	return;
}
void CheckBounds(struct player *chara)
{
	if (chara->p.x < 0)
		chara->p.x = 0;
	if (chara->p.y < 0)
		chara->p.y = 0;
	if (chara->p.x > screenWidth - chara->w)
		chara->p.x = screenWidth - chara->w;
	if (chara->p.y > screenHeight - chara->h)
		chara->p.y = screenHeight - chara->h;
	chara->player_rect = (Rectangle){
		chara->p.x,
		chara->p.y,
		chara->h,
		chara->w,
	};
	return;
}

// Funtion to determine if there was a change in direction
void UpdatePlayerDir(Rectangle *rec, struct player *chara)
{
	switch (chara->dir)
	{
	case Right:
		rec->width *= -1;
		break;

	case Left:
		rec->width *= -1;
		break;
	}
}