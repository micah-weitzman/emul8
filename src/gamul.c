#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"
#include "gamul.h"


#define SCALE 10 

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

		for (int i = 0; i < 8; i ++) {

			printf("pxl = %u\n", pxl); 
			printf("pxl >> (7 - %i) = %u \n", i,(pxl >> (7 - i)) & 0x1); 
		  // loop through height 
			if (gamer->display[x+i][y+j] != 0)
				if (gamer->display[x+i][y+j] == 1) {
					st->reg[0xF] = 1;
				}
				if ((pxl >> (7 - i)) & 1) {
					gamer->display[x+i][y+j] = gamer->display[x+i][y+j] ^ 1; 
				} 
			}
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
