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
#define MAX_PLAYERS 8
#define SIZE 10
#define MAX_DICE 3

struct Player{
	char name;
	int position, prizes[SIZE], prizeCount, score;
};

void clearBuffer();
int getValidInteger(int* count, int* select, int low, int high);
char getValidCharacter(char low, char high);
int initBoard();
void initPlayer(struct Player* player, int numPlayers); 
int playGame(unsigned int bSize, struct Player players[], unsigned int playerCount,
			 unsigned int* topScore);
char displayTile(unsigned int maxTile, unsigned int index, 
				 struct Player* player, unsigned int playerCount); 
int displayBoard(unsigned int size, struct Player* player, 
				 unsigned int playerCount); 
//int getTileType(unsigned int index); from ms1 had replaced to displayBoard()
int getRandom(int low, int high);
unsigned int playerRoll(struct Player* player);
void winPrize(struct Player* player);
void winGrandPrize(struct Player* player);
int loseItem(struct Player* player);
int checkout(struct Player* player, unsigned int* topScore); 

int main(void){

	struct Player player[MAX_PLAYERS];
	int numPlayers, count, i, size;
	
	for(i = 0; i < MAX_PLAYERS; i++){
		player[i].score = 0;
	}
	
	unsigned int p = 0, topScore = 0;
	char topPlayer = ' ';

	int loop = 1;
	char menu, select;

	while(loop == 1){

		printf("\nWelcome to CHECKOUT\n\n");

		printf(" P - (P)lay the game\n");
		printf(" Q - (Q)uit the game\n");
		printf(" R - Inst(r)uctions\n");
		printf(" S - Highest (s)core\n");

		printf("\nEnter your choice: ");	

		select = getValidCharacter('p', 's');

		if(select == 'P' || select == 'p'){ //initialize player and play game
			
			printf("Enter number of players(1-8): ");
			
			count = scanf("%d", &numPlayers);
			clearBuffer();
			numPlayers = getValidInteger(&count, &numPlayers, 1, 8);

			initPlayer(player, numPlayers);
			
			size = initBoard();
			p = playGame(size, player, numPlayers, &topScore); 

		}
		else if(select == 'Q' || select == 'q') //quit the game
			loop = 0;
		else if(select == 'R' || select == 'r'){ //game instruction
			printf("\n _______________________________________________________\n");
			printf("|\t\t\t\t\t\t\t|\n");
			printf("|\t\t  Checkout instruction.\t\t\t|\n");
			printf("|_______________________________________________________|\n");
			printf("|\t\t\t\t\t\t\t|\n");
			printf("| Play checkout up to 8 players\t\t\t\t|\n");
			printf("| compete to be the first to obtain $1000\t\t|\n");
			printf("|\t\t\t\t\t\t\t|\n");
			printf("| Empty Tile\t    - No effect\t\t\t\t|\n");
			printf("| Win Tile\t    - Win a random prize\t\t|\n");
			printf("| Lose Tile\t    - Lose a random prize\t\t|\n");
			printf("| Grand Prize Tile  - Win a grand prize\t\t\t|\n");
			printf("| Checkout Tile\t    - Sells all your prize for cash\t|\n");
			printf("|\t\t\t\t\t\t\t|\n");
			printf("| Players can roll 1-3 dice for each turn\t\t|\n");
			printf("| If a player lands on the same tile as another player  |\n");
			printf("| that player steals a prize and move 1 tile back       |\n");
			printf("|_______________________________________________________|\n\n");
		}
		else if(select == 'S' || select == 's'){ //check the highest score
			printf("\n _______________________________________________________\n");
			printf("|\t\t\t\t\t\t\t|\n");
			printf("|\t\t\t\t\t\t\t|\n");
			printf("|\t\t      __\t\t\t\t|\n");
			printf("|\t\t        \\_______\t\t\t|\n");
			printf("|\t\t         \\++++++|\t\t\t|\n");
			printf("|\t\t          \\=====|\t\t\t|\n");
			printf("|\t\t          O-----O\t\t\t|\n");
			printf("|\t\t\t\t\t\t\t|\n");
			printf("|\t\t\t\t\t\t\t|\n");
			if(topScore < player[p].score){
				topScore = player[p].score;
				topPlayer = player[p].name;
				printf("|\t\t  HIGH SCORE: $%4d BY: %c\t\t|\n", 
						player[p].score, player[p].name); 
			}
			else
				printf("|\t\t  HIGH SCORE: $%4d BY: %c\t\t|\n", topScore, topPlayer);
			
			printf("|\t\t\t\t\t\t\t|\n");
			printf("|_______________________________________________________|\n\n");
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

void initPlayer(struct Player* player, int numPlayers){

	int i, j;

	for(i = 0; i < numPlayers; i++){
		(player+i)->score = 0;	

		for(j = 0; j < SIZE; j++)
			(player+i)->prizes[j] = 0;

		(player+i)->prizeCount = 0;

		printf("Enter player ID: ");
		(player+i)->name = getValidCharacter('!', '~');

		(player+i)->position = 0;
	}
}

int initBoard(){
	int size = 1, count = 0;

	//Test code
	//If the test fails, the below statements will print.
	//If the test pass, the program starts and ask user to input the size of the
	//board.
/*	
	if(displayTile(12, 153, 'p', 1) != 'W') printf("153 should return W\n");
	else if(displayTile(12, 65, 'p', 1) != 'L') printf("65 should return L\n");
	else if(displayTile(12, 49, 'p', 1) != 'G') printf("49 shuold return G\n");
	else if(displayTile(12, 0, 'p', 1) != 'C') printf("0 should return C\n");
	else if(displayTile(12, 105, 'p', 1) != 'G') printf("105 should be G\n");
	else if(displayTile(12, 79, 'p', 1) != ' ') printf("79 should be space\n");
	else {
*/
		//printf("getTileType test passed!\n");
		printf("Enter board size: ");
		count = scanf("%d", &size);

		size = getValidInteger(&count, &size, 5, 15);

//	}

	return size;
}

int playGame(unsigned int size, struct Player player[], unsigned int playerCount,
			 unsigned int* topScore){

	int maxTile, p, i, j, k, l, randPick, stealPrize, result, topPlayer;
	int end = 0;

	while(end != 1){

		for(p = 0; p < playerCount; p++){

			int noPlayer = 0;
			
			maxTile = displayBoard(size, player, playerCount); 

			printf("\n%c's Score: %d\tInventory status (%2d/%2d): \n\n", player[p].name, 
					player[p].score, player[p].prizeCount, SIZE);

			for(j = 0; j < playerCount; j++){

				printf(" %c : [", player[j].name);
				for(i = 0; i < SIZE; i++){
					//if(player[j].prizes[i] != 0){ //pPrizes[i] != 0){
						printf("%4d", player[j].prizes[i]); //pPrizes[i]);
					//	if(player[j].prizes[i+1] != 0) //pPrizes[i+1] != 0)
					//		printf(", ");
					//}else if(player[j].prizes[0] == 0){ //pPrizes[0] == 0){
					//	printf("%2d", player[p].prizes[0]); //pPrizes[0]);
						//i = SIZE;
					//}
				}
				printf(" ]\n");
			}

			printf("\n%c's turn, how many dice will you role?: ", player[p].name);
			result = playerRoll(&player[p]);

			printf("\n < Advancing: %d >\n", result);

			player[p].position += result;
			
			while(noPlayer == 0){

				int steal = 0, noItem = 0;
				
				for(k = 0; k < playerCount; k++){
					
					if((player[p].position % maxTile) == (player[k].position % maxTile)
						&& p != k){
						
						printf("\n < %c has caught %c >\n", 
						player[p].name, player[k].name);
						
						if(player[k].prizeCount > 0){

							randPick = getRandom(1, player[k].prizeCount);	
							printf("\nDEBUG: randPick = %d/%d\n", 
									randPick, player[k].prizeCount);
						
							stealPrize = player[k].prizes[randPick - 1];
							printf("\nDEBUG: %c.prize[%d] = %d\n",
									player[k].name, randPick - 1,
									player[k].prizes[randPick - 1]);
							
							player[k].prizeCount--;
							player[k].prizes[randPick - 1] = 0;
		
							for(l = 0; l < SIZE; l++){ 
								if(player[k].prizes[l] == 0 && l < SIZE - 1){ 
									player[k].prizes[l] = player[k].prizes[l+1];
									player[k].prizes[l+1] = 0;
								}
							}

							steal = 1;
							k = playerCount;
						}
						else{
							printf("\n < %c's inventory is empty! >\n", 
									player[k].name);
							noItem = 1;
							k = playerCount;
						}
					}	
				}

				if(steal == 1){
					player[p].prizes[player[p].prizeCount] += stealPrize;
					printf("\n < %c stole %d >\n", player[p].name, 
							player[p].prizes[player[p].prizeCount]);
					player[p].prizeCount++;
					player[p].position -= 1;
				}
				else if(noItem == 1)
					player[p].position -= 1;
				else{
					noPlayer = 1;
				}
			}

			if((player[p].position % (maxTile)) == 0){
				printf("\n < %c has landed on checkout! >\n", player[p].name);
				end = checkout(&player[p], topScore);
				topPlayer = p;
				p = playerCount;
			}

			else if((player[p].position % (maxTile)) % 7 == 0){
				printf("\n < %c has landed on Win Grand Prize Tile! >\n", player[p].name);
				winGrandPrize(&player[p]);
			}
			else if((player[p].position % (maxTile)) % 5 == 0){
				printf("\n < %c has landed on Lose Prize tile! >\n", player[p].name);
				loseItem(&player[p]);
			}
			else if((player[p].position % (maxTile)) % 3 == 0){
				printf("\n < %c has landed on Win Prize tile! >\n", player[p].name);
				winPrize(&player[p]);
			}
			else{
				printf("\n < %c has landed on Empty tile! >\n", player[p].name);
				printf("\n < Nothing happens, %c's turn is over! >\n", player[p].name);
			}
		}
	}

	printf("\n");
	clearBuffer();

	return topPlayer;
}

/*
	getTileType function receives an assigned value of each tile from displayBoard and
	it determines to print a letter 'C', 'W', 'L', 'G' or ' ' within the if and else
	if statements.
*/

char displayTile(unsigned int maxTile, unsigned int index, struct Player player[], 
				 unsigned int playerCount){

	int i;
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

	for(i = 0; i < playerCount; i++){
		if(index == player[i].position % (maxTile + 1)){
			tileType = player[i].name;
			i = playerCount;
		}
	}
	
	return tileType;	//return tile type with character
}

/*
	displayBoard function prints a board according to user input (size),
	then it counts the total number of tiles and assign numbers in clockwise order.
 */

int displayBoard(unsigned int size, struct Player player[], unsigned int playerCount){

	int row1 = 0, row2 = 0, row3 = 0, space = 0;
	int countUp = 0, countDown = 0;

	int maxTile = (size * 2) + ((size - 2) * 2);	//total number of square boards

	countDown = maxTile - 1;	//temp variable to assign decrement numbers in mid layer

	for(row1 = 0; row1 < size; row1++){	//print top layer 
		printf(" ___ ");
	}
	printf("\n");
	for(row2 = 0; row2 < size; row2++){
		printf("| %c |", displayTile(maxTile-1, countUp++, player, playerCount)); 
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
			printf("| %c |", displayTile(maxTile-1, countDown--, player, playerCount)); 
			//send variable countDown value into displayTile function
															
			for(space = 0; space < (size - 2); space++){
				printf("     ");	//print empty space
			}
			printf("| %c |\n", displayTile(maxTile-1, countUp++, player, playerCount));
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
			printf("| %c |", displayTile(maxTile-1, countDown--, player, playerCount));
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

unsigned int playerRoll(struct Player* player){
	
	int numDice = 0, dice[MAX_DICE], i, sum = 0;
	
	int count = scanf("%d", &numDice);
	
	//get random number of dice between 1 to 3
	numDice = getValidInteger(&count, &numDice, 1,3);

	for(i = 0; i < numDice; i++){
		dice[i] = getRandom(1,6); //roll the dice (1-3) times and assign into dice[i]
	}

	printf("\n < %c rolled: ", player->name);
	
	for(i = 0; i < numDice; i++){
		printf("%d ", dice[i]);
		sum += dice[i];
	}

	printf(" >\n");

	return sum;
}

void winPrize(struct Player* player){

	int i, temPrize = 0;

	if(player->prizeCount < SIZE){
		for(i = 0; i < SIZE; i++){
			if(player->prizes[i] == 0){
				temPrize = getRandom(10, 91); //Win Prize between 10-100
				player->prizes[i] = temPrize;
				i = SIZE;
			}
		}
		player->prizeCount += 1;
		printf("\n < %c won a prize of %d >\n", player->name, temPrize);
	}
	else
		printf("\n < %c's inventory is full! >\n", player->name);
}

void winGrandPrize(struct Player* player){
	
	int i, temPrize = 0;
	
	if(player->prizeCount < SIZE){
		for(i = 0; i < SIZE; i++){
			if(player->prizes[i] == 0){
				temPrize = getRandom(100, 101); //Grand Prize between 100-200
				player->prizes[i] = temPrize;
				i = SIZE;
			}
		}
		player->prizeCount += 1;
		printf("\n < %c won a grand prize of %d >\n", player->name, temPrize);
	}
	else
		printf("\n < %c's inventory is full! >\n", player->name);
}

int loseItem(struct Player* player){
	
	int randomPick = 0, temPrize = 0, i;

	if(player->prizeCount > 0){
		randomPick= getRandom(0,player->prizeCount); //pick random number
	
		temPrize = player->prizes[randomPick];
		
		player->prizes[randomPick] = 0;	//lose the prize
	
		player->prizeCount -= 1;
	
		printf("\n < %c lost a prize valued at %d! >\n", player->name, temPrize);

		//keep prize on right side of pPrizes[] while empties place left

		for(i = 0; i < SIZE; i++){ 
			if(player->prizes[i] == 0 && i < SIZE - 1){ 
				player->prizes[i] = player->prizes[i+1];
				player->prizes[i+1] = 0;
			}
		}
	}
	else
		printf("\n < %c inventory is empty! >\n", player->name);
}

int checkout(struct Player* player, unsigned int* topScore){
	
	int result = 0, i, temScore = 0;

	for(i = 0; i < player->prizeCount; i++){ //make total of prizes
		if(player->prizes[i] != 0){
			temScore += player->prizes[i];
		}
	}

	//checkout the game if player score higher than 200 points

	if(temScore >= 200){
		
		player->score = temScore;
		
		for(i = 0; i < player->prizeCount; i++){
			player->prizes[i] = 0;
		}
		player->prizeCount = 0;
		printf("\n _____________________________________\n");
		printf("|\t\t\t\t      |\n");
		printf("|\t    %c won the game!\t      |\n", player->name);
		printf("|\t\t\t\t      |\n");
		printf("|\t%c checked out for $%4d\t      |\n", player->name, player->score);
		printf("|\t\t\t\t      |\n");

		if(player->score <= *topScore)
			printf("|        Highest Score is $%4d       |\n", *topScore);
			
		else if(player->score > *topScore)
			printf("|      Highest Score is now $%4d     |\n", player->score);

		printf("|_____________________________________|\n");
		
		result = 1;
	} else
		result = 0;

	return result;
}


