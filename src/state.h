#ifndef STATE_H_
#define STATE_H_

extern struct state {

	unsigned char* mem; // memory 
	unsigned short pc; // program counter

	unsigned short* stack; 
	unsigned short sp; // stack pointer

	unsigned short I; // Index register

    unsigned char* reg; 

	unsigned char del;
	unsigned char sound; 

	unsigned char keys[16]; 
}; 

#endif 