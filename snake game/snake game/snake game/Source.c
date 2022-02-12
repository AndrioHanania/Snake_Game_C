#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 25
#define COLS 75

typedef struct _Item
{
	char data;
	struct Item* next;
	int x;
	int y;
}Item;

typedef struct _List
{
	Item* head;
	Item* tail;
	int length;
}List;
Item* createNewItem(char ch, int x, int y, Item* next);
List makeEmptyList();
void printSnake(List list);
void init(void);
void gotoxy(int x, int y);
void sleep(float secs);
void printFrameBoard();
void moveSnakeForward(List* list, char* c, char* prevC, int* step, int* lastHeadX, int* lastHeadY, bool flag);
void moveToDirection(List* list, char* c, char* prevC);
void swithXYToAllSnake(List* list);
void printDolar(List snake, List* dolars);
void duplicateTail(List* list);
bool isSnakeStrikeHimself(List list);
bool isSnakeStrikeTheFrame(List list);
bool isTheGameOver(List list);
bool ifDolarOnTheWay(char* c, char* prevC, List* dolars, List* snake, int* step, int* lastHeadX, int* lastHeadY);
int random_int(int min, int max);


int main()
{
	int step = 1;
	char c = 'd', prevC = 'd';
	double second = 1;
	int lastHeadX, lastHeadY;
	List snake = makeEmptyList();
	List dolars = makeEmptyList();
	snake.head = createNewItem('@', ROWS / 2, COLS / 2, NULL);
	snake.tail = snake.head;
	lastHeadX = snake.head, lastHeadY = snake.tail;

	init();
	printFrameBoard();
	while (!isTheGameOver(snake))
	{
		gotoxy(lastHeadX, lastHeadY);
		printf(" ");
		printSnake(snake);
		if (step % 5 == 0)
			if (second >= 0.1)
				second -= 0.03;
		sleep(second);

		if(!ifDolarOnTheWay(&c, &prevC, &dolars, &snake, &step, &lastHeadX, &lastHeadY, &step, &lastHeadX, &lastHeadY))
			moveSnakeForward(&snake, &c, &prevC, &step, &lastHeadX, &lastHeadY, false);
		if (step % 4 == 0)
			printDolar(snake, &dolars);
	}
}

bool ifDolarOnTheWay(char* c, char* prevC, List* dolars, List* snake, int* step, int* lastHeadX, int* lastHeadY)
{
	Item* curr = NULL, * next;
	switch (*c)
	{
	case 'w':
		next = dolars->head;
		while (next != NULL)
		{
			if (next->x == snake->tail->x - 1 && next->y == snake->tail->y)
			{
				moveSnakeForward(snake, c, prevC, step, lastHeadX, lastHeadY, true);

				if (next == dolars->head && next == dolars->tail)
				{
					dolars->head = dolars->tail = NULL;
					free(next);
					dolars->length--;
				}
				else if(next == dolars->head)
				{
					dolars->head = next->next;
					free(next);
					dolars->length--;
				}
				else if (next == dolars->tail)
				{
					dolars->tail = curr;
					curr->data = NULL;
					free(next);
					dolars->length--;
				}
				else
				{
					curr->next = next->next;
					free(next);
					dolars->length--;
				}

				return true;
			}

			curr = next;
			next = next->next;
		}
		break;
		/////////////////////////////////////////////
	case 's':
		next = dolars->head;
		while (next != NULL)
		{
			if (next->x == snake->tail->x + 1 && next->y == snake->tail->y)
			{
				moveSnakeForward(snake, c, prevC, step, lastHeadX, lastHeadY, true);


				if (next == dolars->head && next == dolars->tail)
				{
					dolars->head = dolars->tail = NULL;
					free(next);
					dolars->length--;
				}
				else if (next == dolars->head)
				{
					dolars->head = next->next;
					free(next);
					dolars->length--;
				}
				else if (next == dolars->tail)
				{
					dolars->tail = curr;
					curr->data = NULL;
					free(next);
					dolars->length--;
				}
				else
				{
					curr->next = next->next;
					free(next);
					dolars->length--;
				}

				return true;
			}

			curr = next;
			next = next->next;
		}
		break;
		/////////////////////////////////////////////
	case 'a':
		next = dolars->head;
		while (next != NULL)
		{
			if (next->x == snake->tail->x && next->y == snake->tail->y - 1)
			{
				moveSnakeForward(snake, c, prevC, step, lastHeadX, lastHeadY, true);


				if (next == dolars->head && next == dolars->tail)
				{
					dolars->head = dolars->tail = NULL;
					free(next);
					dolars->length--;
				}
				else if (next == dolars->head)
				{
					dolars->head = next->next;
					free(next);
					dolars->length--;
				}
				else if (next == dolars->tail)
				{
					dolars->tail = curr;
					curr->data = NULL;
					free(next);
					dolars->length--;
				}
				else
				{
					curr->next = next->next;
					free(next);
					dolars->length--;
				}

				return true;
			}

			curr = next;
			next = next->next;
		}
		break;
		/////////////////////////////////////////////
	case 'd':
		next = dolars->head;
		while (next != NULL)
		{
			if (next->x == snake->tail->x && next->y == snake->tail->y + 1)
			{
				moveSnakeForward(snake, c, prevC, step, lastHeadX, lastHeadY, true);

				if (next == dolars->head && next == dolars->tail)
				{
					dolars->head = dolars->tail = NULL;
					free(next);
					dolars->length--;
				}
				else if (next == dolars->head)
				{
					dolars->head = next->next;
					free(next);
					dolars->length--;
				}
				else if(next == dolars->tail)
				{
					dolars->tail = curr;
					curr->data = NULL;
					free(next);
					dolars->length--;
				}
				else
				{
					curr->next = next->next;
					free(next);
					dolars->length--;
				}

				return true;
			}

			curr = next;
			next = next->next;
		}
		break;
	}

	return false;
}

//print dolar to the screen - food for the snake that he can get bigger
void printDolar(List snake, List* dolars)
{
	int xDolar;
	int yDolar;

	while (true)
	{
		xDolar = random_int(2, ROWS - 1);
		yDolar = random_int(2, COLS - 1);
		bool flag = true;
		Item* curr = snake.head;

		while (curr != NULL)
		{
			if (curr->x == xDolar && curr->y == yDolar)
			{
				flag = false;
				break;
			}

			else
				curr = curr->next;
		}

		if (flag == true)
		{
			gotoxy(xDolar, yDolar);
			printf("$");
			break;
		}
	}

	Item* newItem = createNewItem('$', xDolar, yDolar, NULL);
	if (dolars->head == NULL)
	{
		dolars->head = dolars->tail = newItem;
	}
	else
	{
		dolars->tail->next = newItem;
		dolars->tail = newItem;
	}

	dolars->length++;
}


//return random int from min to max
int random_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

// Turn escape codes ON.
void init(void)
{
	system("cls");
}

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y)
{
	printf("\x1b[%d;%df", x, y);
}

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs)
{
	clock_t clocks_start = clock();
	while (clock() - clocks_start < secs * CLOCKS_PER_SEC);
}

//print the frame of the game
void printFrameBoard()
{
	int i, j;
	for (i = 1; i <= ROWS; i++)
	{
		for (j = 1; j <= COLS; j++)
		{
			gotoxy(i, j);
			if (i == 1 || i == ROWS || j == 1 || j == COLS)
				printf("#");
			else
				printf(" ");
		}
	}
}

//duplicate the Tail of the list ans update the new tail
void duplicateTail(List* list)
{
	Item* tail = createNewItem('@', list->tail->x, list->tail->y, NULL);
	list->tail->next = tail;
	list->tail = tail;
	list->length++;
}

//create new item with data and next that i decided
Item* createNewItem(char ch, int x, int y, Item* next)
{
	Item* node = (Item*)malloc(sizeof(Item));
	node->data = ch;
	node->x = x;
	node->y = y;
	node->next = next;
	return node;
}

//make empty list with no pointer to some item 
List makeEmptyList()
{
	List list = { NULL, NULL, 0};
	return list;
}

//print the snake
void printSnake(List list)
{
	Item* curr = list.head;
	while (curr != NULL)
	{
		gotoxy(curr->x, curr->y);
		printf("%c", curr->data);
		curr = curr->next;
	}
}

// chick if the head of the snake touch the frame board
bool isSnakeStrikeTheFrame(List list)
{
	int row = list.tail->x;
	int col = list.tail->y;
	if (row == ROWS || row == 1 || col == COLS || col == 1)
		return true;
	return false;
}

//chick is the head of the snake touch in the rest of his limbs
bool isSnakeStrikeHimself(List list)
{
	Item* check = list.head;
	if (list.head->next != NULL)
	{
		while (check != list.tail)
		{
			if (check->x == list.tail->x && check->y == list.tail->y)
				return true;
			check = check->next;
		}
	}
	return false;
}

//chick if the player lose
bool isTheGameOver(List list)
{
	if (isSnakeStrikeTheFrame(list) || isSnakeStrikeHimself(list))
	{
		printFrameBoard();
		gotoxy(ROWS / 2, COLS / 2);
		printf("GAME OVER");
		gotoxy(ROWS, 1);
		return true;
	}
	return false;
}

//print The Movement Of The Snake and update the row ans the col
void moveSnakeForward(List* list, char* c, char* prevC, int* step, int* lastHeadX, int* lastHeadY, bool flag)
{
	if (*step % 5 == 0 || flag == true)
	{
		duplicateTail(list);
	}
	else
	{
		*lastHeadX = list->head->x;
		*lastHeadY = list->head->y;
		swithXYToAllSnake(list);
	}
	moveToDirection(list, c, prevC);
	(*step)++;
}

//Moves the snake according to the input
void moveToDirection(List* list, char* c, char* prevC)
{
	if (_kbhit())
		*c = _getch();
	if (*c != 'd' && *c != 'a' && *c != 'w' && *c != 's')
		*c = *prevC;
	switch (*c)
	{
	case 'd':
		(list->tail->y)++;
		break;
	case 'a':
		(list->tail->y)--;
		break;
	case 'w':
		(list->tail->x)--;
		break;
	case 's':
		(list->tail->x)++;
		break;
	}
	*prevC = *c;
}

//update The X and Y Of Th eWhole Snake Just Not The tail
void swithXYToAllSnake(List* list)
{
	Item* curr = list->head;
	Item* next = list->head->next;

	if (curr->next != NULL)
	{
		while (next != NULL && next != list->tail)
		{
			curr->x = next->x;
			curr->y = next->y;
			curr = next;
			next = next->next;
		}

		if (next != NULL) 
		{
			curr->x = next->x;
			curr->y = next->y;
		}
	}
}