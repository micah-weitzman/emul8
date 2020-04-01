#ifndef GAMUL_H
#define GAMUL_H

#define SCREEN_WIDTH	64
#define SCREEN_HEIGHT	32
#define FONTSET_SIZE	80

#define MILI_SEC 10

typedef struct gamul8 {
	unsigned char display[SCREEN_WIDTH][SCREEN_HEIGHT];
} gamul8;

const unsigned char fontset[FONTSET_SIZE]; 

extern void display_func(struct state *st, gamul8 *gamer, 
	unsigned char x, unsigned char y, unsigned char n); 

extern void sound_handler(struct state *st); 

extern void delay_handler(struct state *st); 

extern unsigned short get_opt(struct state *st);


#endif