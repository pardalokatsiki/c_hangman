#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void startgame(int *winstreak, char*);
int game_mode_menu();
int lives_generator(int);
void getBuffer(char *, char*);
int line_generator();
void instructions();
void init_hidden(char *, char *);
void spacebar_detector(char *, char *, int *);
void display_word(char *);
void letters_inserted(char *);
void history_modifier(char *, char);
int compare_letter(char, char *, char *, int *);
void countdown();
void bye();

int main (int argc, char* argv[])
{
	system("clear");
	int winstreak = 0;
	char answer;
	if(argc == 1){
	  return 0;
	}
	if(argc > 2){
	  return 0;
	}
	char* path = argv[1];
	do
	{
		system("clear");
		printf("               WELCOME TO HANGMAN!                                      Win streak: %03d\n", winstreak);
		printf("\n               Start game? (Y/N)");
		printf("\n\nWaiting for answer: ");
		scanf(" %c", &answer);
		if(answer == 'Y')
		{
			startgame(&winstreak, path);
		}
	}
	while(answer!= 'N');
	bye();
	return 0;
}

void startgame(int *streak, char* path)
{
	system("clear");
	unsigned int lives = game_mode_menu();
	system("clear");
	instructions();
	char *Buffer, *HiddenArray, *InputHistory;
	Buffer = (char*)malloc(50*sizeof(char));
	getBuffer(Buffer, path);
	HiddenArray = (char*)malloc((strlen(Buffer) + 1)*sizeof(char));
	init_hidden(HiddenArray, Buffer);
	InputHistory = (char*)calloc(26, sizeof(char));
	char letter;
	int answer;
	int correct = 0;
	spacebar_detector(Buffer, HiddenArray, &correct);
	while(lives>0 && correct != strlen(Buffer))
	{
		system("clear");
		printf("Lives remaining: %02d", lives);
		display_word(HiddenArray);
		letters_inserted(InputHistory);
		printf("\n\n\nInsert letter(Remember! UPPERCASE ONLY): ");
		scanf(" %c", &letter);
	    history_modifier(InputHistory, letter);
		answer = compare_letter(letter, Buffer, HiddenArray, &correct);
		if (answer == 0)
		{
			lives--;
			(*streak) = 0;
		}
	}
	if (lives != 0)
	{
		printf("\n\n\n\nYou won! :3 :3");
		printf("\n\nThe answer was %s", Buffer);
		(*streak)++;
	}
	else
	{
		printf("\n\n\n\nGame over, loser (vanessa said calmly)");
		printf("\nThe answer was %s", Buffer);
	}
	free(Buffer);
	free(HiddenArray);
	countdown();
}

int game_mode_menu()
{
	int mode;
	do
	{
	system("clear");
	printf("                   CHOOSE YOUR GAME MODE\n");
	printf("1) Easy (8 lives)    2) Normal (5 lives)   3) Hard (3 lives)\n\n");
	printf("Insert game mode: ");
	scanf("%d", &mode);
	}
	while(lives_generator(mode)!=0);
	return lives_generator(mode);
}

int lives_generator(int input)
{
	switch(input)
	{
		case 1: return 8; break;
		case 2: return 5; break;
		case 3: return 3; break;
		default: return 0; 
	}
}


void instructions()
{
	printf("                                                       INSTRUCTIONS:\n");
	printf("\nInsert UPPERCASE characters and find the hidden word. Enjoy the game!");
	printf("\n\n\n\nPress enter to proceed.");
	getchar(); getchar();
}

int line_generator()
{
	time_t t;
	srand(time(NULL));
	int line = (rand() % 287 + 1);
	return line;
}

void getBuffer(char *Buffer, char* path)
{
	FILE *fp;
	fp = fopen(path, "r");
	int i, line;
	rewind(fp);
	line = line_generator();
	for (i = 0; i < line; i++ )
	{
		fgets(Buffer, 50, fp);
	}
	Buffer[strlen(Buffer) - 1] = 0;
	fclose(fp);
}

void init_hidden(char *array, char *array2)
{
	int i;
    int length = strlen(array2);
	for(i=0; i < length; i++)
	{
		array[i] = '-';
	}
	array[strlen(array2) - 1] = 0;
}

void spacebar_detector(char *array1, char *array2, int *correct)
{
	int i;
	for (i=0; i < strlen(array1); i++)
	{
		if(isspace(array1[i]))
		{
			array2[i] = ' ';
			(*correct)++;
		}
	}
}

void display_word(char *array)
{
	int i;
	printf("\n\n\n\n");
	for (i = 0; i<strlen(array); i++)
	{
		printf("%c ", array[i]);
	}
}

void letters_inserted(char *array)
{
	printf("\n\nLetters inserted: ");
	int i;
	int length = strlen(array);
	for (i=0; i<(length); i++)
	{
		printf("%c ", array[i]);
	}
}

void history_modifier(char *array, char letter)
{
	int i, f;
	f = 0;
	for (i=0; i<26; i++)
	{
		if (array[i]==letter)
		{
			f = 1;
			break;
		}
	}
	if (f == 0)
	{
		for (i=0; i<26; i++)
		{
			if (array[i] == 0)
			{
				array[i] = letter;
				break;
			}
		}
	}
}

int compare_letter(char letter, char *array1, char *array2, int *correct)
{
	int i, f;
	f = 0;
	for (i = 0; i < strlen(array1); i++)
	{
		if (isspace(letter) && isspace(array1[i]))
		{
			array2[i] = ' ';
			f = 1;
			(*correct)++;
		}
		else if(letter == array1[i])
		{
			array2[i] = letter;
			f = 1;
			(*correct)++;
		}
	}
	return f;
}

void countdown()
{
	int i;
	printf("\n\nWaiting to go back to main screen... ");
	sleep(1);
    for (i = 5; i > 1; i--)
    {
    	printf("%d, ", i);
    	sleep(1);
	}
	printf("1...");
	sleep(1);
}

void bye()
{
	system("clear");
	printf("Goodbye, hope to see you again!");
	sleep(2);
}
