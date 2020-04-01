#include "state.h"
#include "gamul.h"

void zero_h(struct state *st, unsigned short opcode) {
    printf("[handler] 0 called \n"); 
    //TODO: clear screan or return from subreoutine 
}

// WORKS
// 1NNN - jumps to line NNN
void one_h(struct state *st, unsigned short opcode) {
    //printf("[handler] 1 called \n"); 
    st->pc = (opcode & 0x0FFF); 
}


void two_h(struct state *st, unsigned short opcode) {
    printf("[handler] 2 called \n"); 
    st->sp++;
    st->sp = st->pc;
}

// WORKS 
// 3RNN - if rgstr R == NN, then next instr is skipped
void three_h(struct state *st, unsigned short opcode) {
    //printf("[handler] 3 called \n"); 
    if (st->reg[(opcode >> 8) & 0xF] == (opcode & 0xFF)){
        st->pc += 2; 
    }
}

// WORKS 
// 4RNN - if rgstr R != NN, then next instr is skipped
void four_h(struct state* st, unsigned short opcode){
    //printf("[handler] 4 called \n"); 
    if (st->reg[(opcode >> 8) & 0xF] != (opcode & 0xFF)){
        st->pc += 2; 
    }
}


// WORKS 
// 5XY0 - if rgstr X == rgstr Y, then next instr is skipped
void five_h(struct state *st, unsigned short opcode) {
    printf("[handler] 5 called \n"); 
    if (st->reg[(opcode >> 8) & 0xF] == st->reg[(opcode >> 4) & 0xF]) {
        st->pc += 2; 
    }
}


// WORKS
// 6RNN - places the value of NN into register R
void six_h(struct state *st, unsigned short opcode) {
    //printf("[handler] 6 called \n"); 
    st->reg[(opcode >> 8) & 0x0F] = (opcode & 0xFF); 
}

// WORKS 
// 7RNN - adds NN to register R 
void seven_h(struct state *st, unsigned short opcode) {
    //printf("[handler] 7 called \n"); 
    st->reg[(opcode >> 8) & 0x0F] += (opcode & 0xFF); 
}



void eight_h(struct state *st, unsigned short opcode) {
    printf("[handler] 8 called \n"); 
    switch (opcode & 0x000F) {
        case 0:
            st->reg[(opcode << 8)& 0xF] = st->reg[(opcode << 4) & 0x000F]; 
        case 1: 
            st->reg[(opcode << 8)& 0xF] = st->reg[((opcode << 8)& 0xF)] | st->reg[(opcode << 4) & 0x0F]; 
        case 2: 
            st->reg[(opcode << 8)& 0xF] = st->reg[((opcode << 8)& 0xF)] & st->reg[(opcode << 4) & 0x0F]; 
        case 3: 
             st->reg[(opcode << 8)& 0xF] = st->reg[((opcode << 8)& 0xF)] ^ st->reg[(opcode << 4) & 0x0F]; 
        case 4: 
             // TODO 
        case 5: 
             // TODO
        case 6: 
             st->reg[0xF] = st->reg[(opcode << 8)& 0xF] & 0xF; 
             st->reg[(opcode << 8)& 0xF] = st->reg[(opcode << 8)& 0xF] >> 1;
        case 7:
            // TODO
        case 0xE:
             st->reg[0xF] = (st->reg[(opcode << 8)& 0xF] << 8) & 0xF;
             st->reg[(opcode << 8)& 0xF] = st->reg[(opcode << 8)& 0xF] << 1;
    }
}

// WORKS 
// 9XY0 - if rgstr X and Y are not equal, then skip next instr
void nine_h(struct state *st, unsigned short opcode){
    // printf("[handler] 9 called \n"); 
    // printf("X[val]: %i\n", st->reg[(opcode >> 4) & 0xF0]); 
    // printf("y[val]: %i\n", st->reg[(opcode >> 4) & 0xF]); 

    if (st->reg[(opcode >> 8) & 0xF] != st->reg[(opcode >> 4) & 0xF]) {
        st->pc += 2; 
    }
}

// WORKS 
// ANNN - sets I to NNN
void a_h(struct state *st, unsigned short opcode) {
    //printf("[handler] A called \n"); 
    st->I = (opcode & 0xFFF); 
}

// WORKS 
// BNNN - jumps to address NNN + value of register 0 
void b_h(struct state *st, unsigned short opcode) {
    //printf("[handler] B called \n"); 
    st->pc = (opcode & 0xFFF) + st->reg[0]; 
}

// WORKS 
// CRNN - sets reigster R to the output of a bitwise & on NN and random number (0-255)
void c_h(struct state *st, unsigned short opcode) {
    //printf("[handler] C called \n"); 
    int num = rand() % (254); 
    printf("RAND NUM: %i\n", num);
    st->reg[(opcode >> 8) & 0xF] = (opcode & 0xFF) & num; // & rand num
        
}


// DXYN - draws using I reg, at location (rgstr X, rgstr Y) 8 wide and N tall
void d_h(struct state *st, unsigned short opcode) {
    //printf("[handler] D called \n"); 
    unsigned char x = st->reg[(opcode >> 8) & 0xF]; 
    unsigned char y = st->reg[(opcode >> 4) & 0xF];
    unsigned char n = opcode & 0xF;

    printf("(x = %i, y = %i )\n", x, y);
    // go to emul8.c -> gamul.c
    disp_f(x, y, n); 
}

void e_h(struct state *st, unsigned short opcode) {
    printf("[handler] E called \n"); 
    //TODO:  skip if keyporessed opcode
}

void f_h(struct state *st, unsigned short opcode) {
    printf("[handler] F called \n"); 
    // TODO: lots todo here; 
}


















    
