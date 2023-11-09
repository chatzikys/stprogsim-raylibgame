/*
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/ or send a letter to Creative Commons,
PO Box 1866, Mountain View, CA 94042, USA.
*/
#pragma once

#define Width 1280
#define Height 768
#define blocksize 32

enum Win_Lose
{
	Blank,
	Win,
	Lose,
	FullClear,
};

enum Block
{
	Air,
	Wall,
	Door,
	Spawn,
	DoorOpen,
	DoorLocked,
	Exit,
};

enum direction
{
	Left,
	WasLeft,
	Right,
	WasRight,
	Up,
	Down
};

typedef enum AppStates
{
	Loading,
	Menu,
	Game,
	Questions,
	Final,
	GameEnd,
	Quit
};

struct player
{
	Vector2 p;
	enum direction dir;
	int h;
	int w;
	Color color;
	Rectangle player_rect;
};

typedef struct question
{
	char quest[150];
	char ans1[150];
	char ans2[150];
	char ans3[150];
	char ans4[150];
	int correct;
	int tries;
};
