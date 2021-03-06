/*
	I declare that the attached assignment is wholly my own work in accordance with
	Seneca Acadmic Policy. No part of this assignment has been copied manually or
	electronically from any other source (including web sites) or distributed to
	other students.

	Name	Paolo Chanhwan Chang		Student ID	127430155
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

const MAX_INVENTORY_SIZE = 4;
const TAX = .13;

int getTileType(unsigned int index);
void displayBoard(unsigned int size);

int main(void){
	
	int size = 1;

	while(1){

		//Test code
		//If the test fails, the below statements will print.
		//If the test pass, the program starts and ask user to input the size of the
		//board.
	
		if(getTileType(153) != 'W') printf("153 should return W");
		else if(getTileType(65) != 'L') printf("65 should return L");
		else if(getTileType(49) != 'G') printf("49 shuold return G");
		else if(getTileType(0) != 'C') printf("0 should return C");
		else if(getTileType(105) != 'G') printf("105 should be G");
		else if(getTileType(79) != ' ') printf("79 should be space");
		else {
			printf("\n\n-- Program Start --\n\n");
			printf("getTileType test passed!\n");
			printf("Enter board size: ");
			scanf("%d", &size);

			displayBoard(size);

			printf("\n-- Program End --\n");
		}
	}

	return 0;
}

/*
	getTileType function receives an assigned value of each tile from displayBoard and
	it determines to print a letter 'C', 'W', 'L', 'G' or ' ' within the if and else
	if statements.
 */

int getTileType(unsigned int index){

	if(index == 0)	//the 0th tile returns 'C'
		index = 'C';
	else if(index % 7 == 0)	//every 7th tile returns 'G'
		index = 'G';
	else if(index % 5 == 0)	//every 5th tile returns 'L'
		index = 'L';
	else if(index % 3 == 0)	//every 3rd tile returns 'W'
		index = 'W';
	else
		index = ' ';	//otherwise it returns ' ' (blank)

	return index;	//return tile type with character
}

/*
	displayBoard function prints a board according to user input (size),
	then it counts the total number of tiles and assign numbers in clockwise order.
 */

void displayBoard(unsigned int size){

	int row1 = 0, row2 = 0, row3 = 0, space = 0;
	int countUp = 0, countDown = 0;

	//printf("DEBUG: index = %d, (address = %d)\n\n", index, &index);

	int max = (size * 2) + ((size - 2) * 2);	//total number of square boards

	//printf("DEBUG: max = %d\n\n", max);

	countDown = max - 1;	//temp variable to assign decrement numbers in mid layer

	for(row1 = 0; row1 < size; row1++){	//print top layer 
		printf(" ___ ");
	}
	printf("\n");
	for(row2 = 0; row2 < size; row2++){
		printf("| %c |", getTileType(countUp++));	//send variable countUp value
													//into getTileTpye function
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
			printf("| %c |", getTileType(countDown--));	//send variable countDown value
														//into getTileType function
															
			for(space = 0; space < (size - 2); space++){
				printf("     ");	//print empty space
			}
			printf("| %c |\n", getTileType(countUp++));	//send variable countUp value
														//into getTileType function
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
			printf("| %c |", getTileType(countDown--));	//send variable countDown 
														//value into getTileType
														//function
		}
		printf("\n");
		for(row3 = 0; row3 < size; row3++){
			printf("|___|");
		}
		printf("\n");
	}
}

