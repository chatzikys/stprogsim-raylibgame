/*
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/ or send a letter to Creative Commons,
PO Box 1866, Mountain View, CA 94042, USA.
*/
#pragma once
#include "game.h"
bool IsAnyKeyPressed();
extern enum Win_Lose wincondition;
// https://www.sanfoundry.com/c-interview-questions-answers/
struct question quests[20] =
	{
		{"Who is the father of C language?", "a) Steve Jobs", "b) James Gosling", "c) Dennis Ritchie", "d) Rasmus Lerdorf", 2, 0},
		{"Which of the following is not a valid C variable name?", "a) int number;", "b) float rate;", "c) int variable_count;", "d) int $main;", 3, 0},
		{"Which is valid C expression?", "a) int my_num = 100,000;", "b) int my_num = 100000;", "c) int my num = 1000;", "d) int $my_num = 10000;", 1, 0},
		{"Which of the following cannot be a variable name in C?", "a) extern", "b) true", "c) friend", "d) export", 0, 0},
		{"Which keyword is used to prevent changes in a variable?", "a) immutable", "b) mutable", "c) const", "d) volatile", 2, 0},
		{"Functions can return enumeration constants in C", "a) true", "b) false", "c) depends on the compiler", "d) depends on the standard", 0, 0},
		{"In C language, FILE is of which data type?", "a) int", "b) char *", "c) struct", "d) None of the mentioned", 2, 0},
		{"The C-preprocessors are specified with ---- symbol.", "a) #", "b) $", "c) ” ”", "d) &", 0, 0},
		{"Which of the following are C preprocessors?", "a) #ifdef", "b) #define", "c) #endif", "d) all of the mentioned", 3, 0},
		{"C preprocessors can have compiler specific features.", "a) True", "b) False", "c) Depends on the standard", "d) Depends on the platform", 0, 0},
		{"What is an example of iteration in C?", "a) for", "b) while", "c) do-while", "d) all of the mentioned", 3, 0},
		{"How is an array initialized in C language?", "a) int a[3] = {1, 2, 3};", "b) int a = {1, 2, 3}; ", "c)int a[] = new int[3]", "int a(3) = [1, 2, 3];", 0, 0},
		{"What is the sizeof(char) in a 32-bit C compiler?", "a) 1 bit", "b) 2 bits", "c) 1 Byte", "d) 2 Bytes", 2, 0},
		{"Which of the following is not a valid variable name?", "a) int __a3;", "b) int __3a;", "c) int __A3;", "d) None of the mentioned", 3, 0},
		{"Which of the following is not a valid variable name?", "a) float PI = 3.14;", "b) double PI = 3.14;", "c) int PI = 3.14;", "d) #define PI 3.14", 3, 0},
		{"Which type of conversion is NOT accepted?", "a) From char to int", "b) From float to char pointer", "c) From negative int to char", "d) From double to char", 1, 0},
		{"User-defined data type can be derived by____", "a) struct", "b) enum", "c) typedef", "d) all of the mentioned", 3, 0},
		{"Which of the following cannot be a structure member?", "a) Another structure", "b) Function", "c) Array", "d) None of the mentioned", 1, 0},
		{"Which is the correct syntax to add the header file?", "a)#include<userdefined>", "b)#include \"userdefined.h\"", "c)<include> \"userdefined.h\"", "d)Both A and B", 3, 0},
		{"Question", "Ans1", "Ans2", "Ans3", "Ans4", 3, 0}, // BLANK FOR LATER USE IF NEEDED

};
int cq = 0; // current question
int wrong = 0;
// Displays the cq question and waits for user input, also responsible for clearing/locking doors
void DrawQuestions()
{
	if (cq > 20)
		cq = 0;
	DrawText(quests[cq].quest, 50, screenHeight / 2 - 200, 40, SKYBLUE);
	DrawText(quests[cq].ans1, screenWidth / 2 - 500, screenHeight / 2 - 200 + 100, 30, SKYBLUE);
	DrawText(quests[cq].ans2, screenWidth / 2, screenHeight / 2 - 200 + 100, 30, SKYBLUE);
	DrawText(quests[cq].ans3, screenWidth / 2 - 500, screenHeight / 2 - 200 + 200, 30, SKYBLUE);
	DrawText(quests[cq].ans4, screenWidth / 2, screenHeight / 2 - 200 + 200, 30, SKYBLUE);
	if ((IsKeyPressed(KEY_A) && quests[cq].correct == 0) || (IsKeyPressed(KEY_B) && quests[cq].correct == 1) || (IsKeyPressed(KEY_C) && quests[cq].correct == 2) || (IsKeyPressed(KEY_D) && quests[cq].correct == 3))
	{
		puts("Correct");
		cq++;
		ClearDoor();
		AppState = Game;
		return;
	}
	else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_B) || IsKeyPressed(KEY_C) || IsKeyPressed(KEY_D))
	{
		puts("False");
		if (quests[cq].tries < 3)
		{
			puts("Increasing");
			printf("%d", quests[cq].tries);
			quests[cq].tries++;
			wrong++;
		}
		if (quests[cq].tries >= 3)
		{
			LockDoor();
			cq++;
		}
		AppState = Game;
		return;
	}
}

char ans[9 + 1] = "\0";
int letterCount = 0;
// Final question logic, also uses a texture to display an image to the screen
void DrawFinalQuestion(Texture2D codesnip)
{

	DrawText("To exit you must type the output of the following C code.", 50, screenHeight / 2 - 240, 40, SKYBLUE);
	DrawText("Type your answer, then press ENTER.", 50, screenHeight / 2 - 200, 20, SKYBLUE);
	DrawText("Be carefull you only have one chance.", 50, screenHeight / 2 - 180, 20, SKYBLUE);
	DrawTexture(codesnip, screenWidth / 2 - 262 / 2, screenHeight / 2 - 154 / 2 - 50, WHITE);
	if (codesnip.id == NULL)
	{
		DrawText("Texture Loading Failed, the answer is -128,\nmake sure that you have the assets folder", screenWidth / 2 - 262, screenHeight / 2 - 154, 30, MAROON);
	}
	Rectangle textBox = {screenWidth / 2.0f - 100, 480, 225, 50};
	bool mouseOnText = false;

	int framesCounter = 0;

	int key = GetCharPressed();
	while (key > 0)
	{
		if (IsAnyKeyPressed() == true && (letterCount < 9))
		{
			ans[letterCount] = (char)key;
			ans[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
			letterCount++;
		}

		key = GetCharPressed(); // Check next character in the queue
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		letterCount--;
		if (letterCount < 0)
			letterCount = 0;
		ans[letterCount] = '\0';
	}

	framesCounter++;
	DrawRectangleRec(textBox, LIGHTGRAY);
	DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);

	DrawText(ans, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
	if (IsKeyPressed(KEY_ENTER) && atoi(ans) == -128)
	{
		if (wrong == 0 && cq == 19)
		{
			puts("FULL CLEAR");
			wincondition = FullClear;
			framesCounter = 0;
			AppState = GameEnd;
		}
		else
		{
			puts("YOU EXITED");
			wincondition = Win;
			framesCounter = 0;
			AppState = GameEnd;
		}
	}
	else if (IsKeyPressed(KEY_ENTER))
	{
		puts("You Failed");
		wincondition = Lose;
		framesCounter = 0;
		AppState = GameEnd;
	}
}
// Logic for DrawFinalQuestion
bool IsAnyKeyPressed()
{
	bool keyPressed = false;
	int key = GetKeyPressed();

	if ((key >= 32) && (key <= 126))
		keyPressed = true;

	return keyPressed;
}