#ifndef GAMUL_H
#define GAMUL_H

#define SCREEN_WIDTH	64
#define SCREEN_HEIGHT	32
#define FONTSET_SIZE	80

typedef struct gamul8 {
	unsigned char display[SCREEN_WIDTH][SCREEN_HEIGHT];
} gamul8;

extern void display_func(struct state *st, gamul8 *gamer, 
	unsigned char x, unsigned char y, unsigned char n); 

extern unsigned short get_opt(struct state *st);


#endif


// typedef struct {

// 	unsigned char* mem; // memory 
// 	unsigned short pc; // program counter

// 	unsigned short* stack; 
// 	unsigned short sp; // stack pointer

// 	unsigned short I; // Index register

//     unsigned char* reg; 

// 	unsigned char del;
// 	unsigned char sound; 

// 	unsigned char keys[16]; 
// } STATE; 
//  