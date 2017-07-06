/*
	I declare that the attached assignment is wholly my own work in accordance with
	Seneca Acadmic Policy. No part of this assignment has been copied manually or
	electronically from any other source (including web sites) or distributed to
	other students.

	Name	Paolo Chanhwan Chang		Student ID	127430155
*/

#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#define MAX_DICE 3

void clearBuffer();
int getValidInteger(int* count, int* select, int low, int high);
char getValidCharacter(char low, char high);
int initBoard();
void initPlayer(int* ,int pPrizes[], unsigned int*, char*, int*);
void playGame(unsigned int bSize, int* pScore, int pPrizes[], 
			  unsigned int*	prizeCount, char* pName, int* pPosition);
char displayTile(unsigned int max, unsigned int index, 
				 char pName, unsigned int pPosition);
int displayBoard(unsigned int size, char pName, unsigned int pPosition);	
//int getTileType(unsigned int index); from ms1 had replaced to displayBoard()
int getRandom(int low, int high);
unsigned int playerRoll();
void winPrize(int pPrizes[], unsigned int* prizeCount);
void winGrandPrize(int pPrizes[], unsigned int* prizeCount);
int loseItem(int pPrizes[], unsigned int* prizeCount);
int checkout(int* pScore, int pPrizes[], unsigned int* prizeCount);

int main(void){

	int size;
	int pScore = 0, pPrizes[SIZE], pPosition;
	unsigned int prizeCount;
	char pName;
	
	int topScore = 0;
	char topPlayer = ' ';

	int loop = 1;
	char menu, select;

	while(loop == 1){

		//printf("DEBUG: menu: %c\n", menu);

		printf("\nWelcome to CHECKOUT\n\n");

		printf("P - (P)lay the game\n");
		printf("Q - (Q)uit the game\n");
		printf("R - Inst(r)uctions\n");
		printf("S - Highest (s)core\n");

		printf("\nEnter your choice: ");	

		select = getValidCharacter('p', 's');

		if(select == 'P' || select == 'p'){ //initialize player and play game
			
			initPlayer(&pScore, pPrizes,&prizeCount, &pName, &pPosition);
			size = initBoard();
			playGame(size, &pScore, pPrizes, &prizeCount, &pName, &pPosition);

		}
		else if(select == 'Q' || select == 'q') //quit the game
			loop = 0;
		else if(select == 'R' || select == 'r'){ //game instruction
			printf("\n\tCheckout instruction.\n\n");
			printf("Play checkout up to 8 players\n");
			printf("compete to be the first to obtain $1000\n\n");
			printf("Empty Tile\t  - No effect\n");
			printf("Win Tile\t  - Win a random prize\n");
			printf("Lose Tile\t  - Lose a random prize\n");
			printf("Grand Prize Tile  - Win a grand prize\n");
			printf("Checkout Tile\t  - Sells all your prize for cash\n\n");
			printf("Players can roll 1-3 dice for each turn\n");
			printf("If a player lands on the same tile as another player\n");
			printf("that player steals a prize and move 1 tile back\n");
		}
		else if(select == 'S' || select == 's'){ //check the highest score
			printf("\n    __\n");
			printf("      \\_______\n");
			printf("       \\++++++|\n");
			printf("        \\=====|\n");
			printf("        O-----O\n\n");

			if(topScore < pScore){ //keep track topScore & topPlayer
				topScore = pScore;
				topPlayer = pName;
				printf("HIGH SCORE: $%d BY: %c\n", pScore, pName);
			}
			else
				printf("HIGH SCORE: $%d BY: %c\n", topScore, topPlayer);
		}
	}
	
	printf("\nThis game is much more fun than bash...\n");
	
	return 0;
}

void clearBuffer(){
	
	int garbage = 0;
	
	while(garbage != '\n'){
		garbage = getchar();
	}
}

int getValidInteger(int* count, int* select, int low, int high){
	
	while(*count == 0 || *select < low || *select > high){
	
		if(*count == 0){
			clearBuffer();
		}
		printf("Invalid input, try again: ");
		*count = scanf("%d", select);
	}

	return *select;
}

char getValidCharacter(char low, char high){
	
	char name = ' ', garbage;

	do{	
		scanf("%c", &name);
		clearBuffer();
		
		if(name < low || name > high){
		
			printf("Invalid input, try again: ");
		}
	} while(name < low || name > high);

	return name;
}

//Initialize player's states with 0

void initPlayer(int* pScore, int pPrizes[], unsigned int* prizeCount,
				char* pName, int* pPosition){
	
	*pScore = 0;
	
	int i;

	for(i = 0; i < SIZE; i++)
		pPrizes[i] = 0;

	*prizeCount = 0;

	printf("Enter player ID: ");
	*pName = getValidCharacter('!', '~');
	
	*pPosition = 0;
}

int initBoard(){
	int size = 1, count = 0;

	//Test code
	//If the test fails, the below statements will print.
	//If the test pass, the program starts and ask user to input the size of the
	//board.
	
	if(displayTile(12, 153, 'p', 1) != 'W') printf("153 should return W\n");
	else if(displayTile(12, 65, 'p', 1) != 'L') printf("65 should return L\n");
	else if(displayTile(12, 49, 'p', 1) != 'G') printf("49 shuold return G\n");
	else if(displayTile(12, 0, 'p', 1) != 'C') printf("0 should return C\n");
	else if(displayTile(12, 105, 'p', 1) != 'G') printf("105 should be G\n");
	else if(displayTile(12, 79, 'p', 1) != ' ') printf("79 should be space\n");
	else {
		//printf("\n\n-- Program Start --\n\n");
		//printf("getTileType test passed!\n");
		printf("Enter board size: ");
		count = scanf("%d", &size);

		size = getValidInteger(&count, &size, 5, 15);

		//displayBoard(size, pPosition, pName);
		//printf("\n-- Program End --\n");
	}

	return size;
}

void playGame(unsigned int size, int* pScore, int pPrizes[],
			unsigned int* prizeCount, char* pName, int* pPosition){

	int end = 0;

	while(end != 1){

		int maxTile, i, result; // numDice = 0;

		maxTile = displayBoard(size, *pName, *pPosition);

		printf("\nScore: %d\n\nInventory (%2d/%2d): \n\n", *pScore, *prizeCount, SIZE);

		printf("[");
		for(i = 0; i < SIZE; i++){
			if(pPrizes[i] != 0){
				printf("%3d", pPrizes[i]);
				if(pPrizes[i+1] != 0)
					printf(", ");
			}else if(pPrizes[0] == 0){
				printf("%2d", pPrizes[0]);
				i = SIZE;
			}
		}
		printf(" ]\n");

		/*	
		for(i = 0; i < SIZE; i++){
			printf("%3d, ",pPrizes[i]);
		}
		printf("\n");
		*/

		printf("\nYour turn, how many dice will you role?: ");
		result = playerRoll();
	
		printf("\nAdvancing: %d\n", result);

		*pPosition += result;

		//printf("\nDEBUG: pPosition: %d\ttile number: %d\n", 
		//		*pPosition, *pPosition % maxTile);

		if((*pPosition % (maxTile)) == 0){
			printf("\n < Land on checkout! >\n");
			end = checkout(pScore, pPrizes, prizeCount);
		}

		else if((*pPosition % (maxTile)) % 7 == 0){
			printf("\n < Land on Win Grand Prize Tile! >\n");
			winGrandPrize(pPrizes, prizeCount);
		}
		else if((*pPosition % (maxTile)) % 5 == 0){
			printf("\n < Land on Lose Prize tile! >\n");
			loseItem(pPrizes, prizeCount);
		}
		else if((*pPosition % (maxTile)) % 3 == 0){
			printf("\n < Land on Win Prize tile! >\n");
			winPrize(pPrizes, prizeCount);
		}
		else{
			printf("\n < Land on Empty tile! >\n");
			printf("\nNothing happens, roll the dices again!\n");
		}
	}

	printf("\n < You won the game! >\n");
	clearBuffer();
}

/*
	getTileType function receives an assigned value of each tile from displayBoard and
	it determines to print a letter 'C', 'W', 'L', 'G' or ' ' within the if and else
	if statements.
 */

char displayTile(unsigned int maxTile, unsigned int index, 
				 char pName, unsigned int pPosition){

	char tileType;

	if(index == 0)	//the 0th tile returns 'C'
		tileType = 'C';
	else if(index % 7 == 0)	//every 7th tile returns 'G'
		tileType = 'G';
	else if(index % 5 == 0)	//every 5th tile returns 'L'
		tileType = 'L';
	else if(index % 3 == 0)	//every 3rd tile returns 'W'
		tileType = 'W';
	else
		tileType = ' ';	//otherwise it returns ' ' (blank)

	if(index == pPosition % (maxTile + 1)) // && tileType = 'C'){
		tileType = pName;

	return tileType;	//return tile type with character
}

/*
	displayBoard function prints a board according to user input (size),
	then it counts the total number of tiles and assign numbers in clockwise order.
 */

int displayBoard(unsigned int size, char pName, unsigned int pPosition){

	int row1 = 0, row2 = 0, row3 = 0, space = 0;
	int countUp = 0, countDown = 0;

	//printf("DEBUG: index = %d, (address = %d)\n\n", index, &index);

	int maxTile = (size * 2) + ((size - 2) * 2);	//total number of square boards

	//printf("DEBUG: maxTile = %d\n\n", max);

	countDown = maxTile - 1;	//temp variable to assign decrement numbers in mid layer

	for(row1 = 0; row1 < size; row1++){	//print top layer 
		printf(" ___ ");
	}
	printf("\n");
	for(row2 = 0; row2 < size; row2++){
		printf("| %c |", displayTile(maxTile-1, countUp++, pName, pPosition));	
		//send variable countUp value into displayTile function
	}
	printf("\n");
	for(row3 = 0; row3 < size; row3++){
		printf("|___|");
	}
	printf("\n");

	if(size != 1){
		for(row1 = 0; row1 < (size - 2); row1++){	//print middle layer
			printf(" ___ ");
			for(space = 0; space < (size - 2); space++){
				printf("     ");
			}
			printf(" ___ \n");
			printf("| %c |", displayTile(maxTile-1, countDown--, pName, pPosition));	
			//send variable countDown value into displayTile function
															
			for(space = 0; space < (size - 2); space++){
				printf("     ");	//print empty space
			}
			printf("| %c |\n", displayTile(maxTile-1, countUp++, pName, pPosition));	
			//send variable countUp value into displayTile function
			printf("|___|");
			for(space = 0; space < (size - 2); space++){
				printf("     ");
			}
			printf("|___|\n");
		}
	
		for(row1 = 0; row1 < size; row1++){	//print bottom layer
			printf(" ___ ");
		}
		printf("\n");
		for(row2 = 0; row2 < size; row2++){
			printf("| %c |", displayTile(maxTile-1, countDown--, pName, pPosition));	
			//send variable countDown value into displayTile function
		}

		printf("\n");
		for(row3 = 0; row3 < size; row3++){
			printf("|___|");
		}
		printf("\n");
	}

	return maxTile;
}


int getRandom(int low, int high){
	return low + rand()%high;
}

unsigned int playerRoll(){
	
	int numDice = 0, dice[MAX_DICE], i, sum = 0;
	
	int count = scanf("%d", &numDice);
	
	//get random number of dice between 1 to 3
	numDice = getValidInteger(&count, &numDice, 1,3);

	for(i = 0; i < numDice; i++){
		dice[i] = getRandom(1,6); //roll the dice (1-3) times and assign into dice[i]
	}

	printf("\nYou rolled: ");
	
	for(i = 0; i < numDice; i++){
		printf("%d ", dice[i]);
		sum += dice[i];
	}

	printf("\n");

	return sum;
}

void winPrize(int pPrizes[], unsigned int* prizeCount){

	int i, temPrize = 0;

	if(*prizeCount < SIZE){
		for(i = 0; i < SIZE; i++){
			if(pPrizes[i] == 0){
				temPrize = getRandom(10, 91); //Win Prize between 10-100
				pPrizes[i] = temPrize;
				i = SIZE;
			}
		}
		*prizeCount += 1;
		printf("\nYou won a prize of %d\n", temPrize);
	}
	else
		printf("\nYour inventory is full!\n");
}

void winGrandPrize(int pPrizes[], unsigned int* prizeCount){
	
	int i, temPrize = 0;
	
	if(*prizeCount < SIZE){
		for(i = 0; i < SIZE; i++){
			if(pPrizes[i] == 0){
				temPrize = getRandom(100, 101); //Grand Prize between 100-200
				pPrizes[i] = temPrize;
				i = SIZE;
			}
		}
		*prizeCount += 1;
		printf("\nYou won a grand prize of %d\n", temPrize);
	}
	else
		printf("\nYour inventory is full!\n");
}

int loseItem(int pPrizes[], unsigned int* prizeCount){
	
	int randomPick = 0, temPrize = 0, i;

	if(*prizeCount > 0){
		randomPick= getRandom(0,*prizeCount); //pick random number
	
		temPrize = pPrizes[randomPick];
		
		pPrizes[randomPick] = 0; //lose the prize
	
		*prizeCount -= 1;
	
		printf("\nYou lost a prize valued at %d!\n", temPrize);

		//keep prize on right side of pPrizes[] while empties place left

		for(i = 0; i < SIZE; i++){ 
			if(pPrizes[i] == 0 && i < SIZE - 1){
				pPrizes[i] = pPrizes[i+1];
				pPrizes[i+1] = 0;
			}
		}
	}
	else
		printf("\nYour inventory is empty!\n");
}

int checkout(int* pScore, int pPrizes[], unsigned int* prizeCount){
	
	int result = 0, i;

	for(i = 0; i < *prizeCount; i++){ //make total of prizes
		if(pPrizes[i] != 0)
			*pScore += pPrizes[i];
	}

	//checkout the game if player score higher than 200 points

	if(*pScore >= 200){
		for(i = 0; i < *prizeCount; i++){
			pPrizes[i] = 0;
		}
		*prizeCount = 0;
		printf("\nYou checked out for $%d\nScore is now: $%d\n", 
			   *pScore, *pScore);
		result = 1;
	} else
		result = 0;

	return result;
}


