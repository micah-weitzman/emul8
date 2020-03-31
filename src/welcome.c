#include <stdio.h>


int wellc() {
	char str[20];

	printf("Please select a game to play. \n");
	printf("Games are located in /games/. \n");
	printf("\t Example: MAZE. \n");

	scanf("%s",str); 
	return 0; 

}