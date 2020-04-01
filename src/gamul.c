#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "state.h"
#include "gamul.h"


// font set for rendering
const unsigned char fontset[FONTSET_SIZE] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0,		// 0
	0x20, 0x60, 0x20, 0x20, 0x70,		// 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0,		// 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0,		// 3
	0x90, 0x90, 0xF0, 0x10, 0x10,		// 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0,		// 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0,		// 6
	0xF0, 0x10, 0x20, 0x40, 0x40,		// 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0,		// 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0,		// 9
	0xF0, 0x90, 0xF0, 0x90, 0x90,		// A
	0xE0, 0x90, 0xE0, 0x90, 0xE0,		// B
	0xF0, 0x80, 0x80, 0x80, 0xF0,		// C
	0xE0, 0x90, 0x90, 0x90, 0xE0,		// D
	0xF0, 0x80, 0xF0, 0x80, 0xF0,		// E
	0xF0, 0x80, 0xF0, 0x80, 0x80		// F
};

 
/*	FUNCTION: load_file
 *  -------------------
 *	Loads the given program/game
 *	PARAMETERS: 
 *  file_name: name of file to be loaded
 *  buffer: system memory which will hold program
 *	RETURNS: 0 if successful, -1 if file error
 */
int load_file(char *file_name, unsigned char *buffer)
{
	FILE *file;
	int file_size;

	// open file stream in binary read-only mode
	file = fopen(file_name, "rb");	//man 3 fopen
	
	fseek(file, 0, SEEK_END);	//man 3 fseek

	file_size = ftell(file);	//man 3 ftell

	rewind(file);				//man 3 rewind
	
	fread(buffer, 1, file_size, file);	//man 3 fread
	return 0;

}


/*	FUNCTION: display_func
 *  ----------------------
 *	Sample function that displays a pixel on the screen
 *	PARAMETERS: 
 *  gamer: architecture to be emulated, defined in gamul.h
 *	RETURNS: none
 */
void display_func(struct state *st, gamul8 *gamer, 
	unsigned char x, unsigned char y, unsigned char n) {
	st->reg[0xF] = 0; 
	for (int j = 0; j < n; j++) {
	 // loop through x values
		unsigned short pxl = st->mem[st->I + j];

		for (int i = 0; i < 8; i ++) {// loop through height 

		//	printf("pxl = %u\n", pxl); 
		//	printf("pxl >> (7 - %i) = %u \n", i,(pxl >> (7 - i)) & 0x1); 
			

			unsigned short x_loc = x+i;
			unsigned short y_loc = y+j; 

			if (x_loc >= SCREEN_WIDTH) {
				x_loc -= SCREEN_WIDTH;
			} 
			if (y_loc >= SCREEN_HEIGHT) {
				y_loc -= SCREEN_HEIGHT; 
			}

		//	printf("x_loc: %u\n", x_loc); 
		//	printf("y_loc: %u\n", y_loc); 

			unsigned char old_px = gamer->display[x_loc][y_loc]; 
			//unsigned char old_px = *(gamer->display + location); 
			if ((pxl >> (7 - i)) & 1) {
				
				gamer->display[x_loc][y_loc] = old_px ^ 1; 
			}

			if ((old_px == 1) && (gamer->display[x_loc][y_loc] == 0)) {
				st->reg[0xF] = 1; 
			}
		}
	}
}



void sound_hanlder(struct state *st) {
	if (st->sound > 0) {
		system("cd .."); 
		system("paplay beep.aiff &> /dev/null &"); 
		st->sound--; 
	}
}

void delay_handler(struct state *st) {
	if (st->del > 0) {
		//clock_t start_time = clock(); 
		//while (clock() <= start_time + MILI_SEC) {;;}
		st->del--; 
	}
}

/*	FUNCTION: get_opt
 *	-----------------
 *	
 *	RETURNS: next optcode to decode 
 */
unsigned short get_opt(struct state *st) {
    unsigned short opt = *(st->mem + st->pc++) << 8; 
    return opt | *(st->mem + st->pc++); 
}
