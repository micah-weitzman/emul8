#include <math.h>
#include "state.h"
#include "gamul.h"

// WORKS
// 00E0 and 00EE
void zero_h(struct state *st, unsigned short opcode) {
 //   printf("[handler] 0 called \n"); 
    if ((opcode & 0xF) == 0) {
        // WORKS 
        // 00E0 - clears screen 
        disp_f(0,0,0,0); 
    } else if ((opcode & 0xF) == 0xE) {
        // WORKS 
        // 00EE - return from subrt - pop stack to PC 
        st->pc = st->stack[(--st->sp)]; 
    }
}

// WORKS
// 1NNN - jumps to line NNN
void one_h(struct state *st, unsigned short opcode) {
    //printf("[handler] 1 called \n"); 
    st->pc = (opcode & 0x0FFF); 
}

// WORKS
// 2NNN - call subrt at addr NNNN
void two_h(struct state *st, unsigned short opcode) {
 //   printf("[handler] 2 called \n"); 
    st->stack[st->sp] = st->pc;
    st->sp++;
    st->pc = (opcode & 0x0FFF); 
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
  //  printf("[handler] 5 called \n"); 
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
   // printf("[handler] 8 called \n"); 
    unsigned long n; 
    int bitpos; 
    signed long d; 
    switch (opcode & 0xF) {
        case 0:
            st->reg[(opcode >> 8)& 0xF] = st->reg[(opcode >>4) & 0xF]; 
            break;

        case 1: 
            st->reg[(opcode >> 8)& 0xF] = st->reg[(opcode >> 8)& 0xF] | st->reg[(opcode>> 4) & 0xF]; 
            break;

        case 2: 
            st->reg[(opcode >>8)& 0xF] = st->reg[(opcode >> 8)& 0xF] & st->reg[(opcode >> 4) & 0xF]; 
            break; 

        case 3: 
             st->reg[(opcode >> 8)& 0xF] = st->reg[(opcode >> 8)& 0xF] ^ st->reg[(opcode >> 4) & 0xF]; 
             break; 

        case 4: 
             n = st->reg[(opcode>> 8) & 0xF] + st->reg[(opcode >>4) & 0xF]; 
             if (n > 0xFF) {
                st->reg[0xF] = 1; 
             } else {
                st->reg[0xF] = 0; 
             }
             st->reg[((opcode >> 8)& 0xF)] = n; 
             break; 

        case 5: 
             d = st->reg[(opcode >> 8)& 0xF] - st->reg[(opcode >> 4) & 0xF]; 
             if (d < 0) {
                st->reg[0xF] = 0; 
             } else {
                st->reg[0xF] = 1; 
             }
             st->reg[((opcode >> 8)& 0xF)] -= st->reg[(opcode >> 4) & 0xF]; 
             break; 

        case 6: 
             st->reg[0xF] = st->reg[(opcode >> 8)& 0xF] & 0x1; 
             st->reg[(opcode >> 8)& 0xF] = st->reg[(opcode >>8)& 0xF] >> 1;
             break; 

        case 7:
             d = st->reg[(opcode >> 4) & 0xF] - st->reg[((opcode>> 8)& 0xF)]; 
             if (d < 0) {
                st->reg[0xF] = 0; 
             } else {
                st->reg[0xF] = 1; 
             }
             st->reg[((opcode >> 8)& 0xF)] =  st->reg[(opcode >> 4) & 0xF] - st->reg[((opcode >> 8)& 0xF)]; 
             break; 
             
        case 0xE:
             n = st->reg[(opcode >>8)& 0xF]; 
             bitpos = 0; 
             while (n != 0) {
                 bitpos++;          
                 n = n >> 1 ; 
             }
             st->reg[0xF] = (1 << bitpos); 
             st->reg[(opcode >> 8)& 0xF] = st->reg[(opcode >> 8)& 0xF] << 1; 
             break;
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

// probably works 
// DXYN - draws using I reg, at location (rgstr X, rgstr Y) 8 wide and N tall
void d_h(struct state *st, unsigned short opcode) {
    //printf("[handler] D called \n"); 
    unsigned char x = st->reg[(opcode >> 8) & 0xF]; 
    unsigned char y = st->reg[(opcode >> 4) & 0xF];
    unsigned char n = opcode & 0xF;

   // printf("(x = %i, y = %i )\n", x, y);
    // go to emul8.c -> gamul.c
    disp_f(x, y, n, 1); 
}

// probably works (not tested)
// EX9E / EXA1
void e_h(struct state *st, unsigned short opcode) {
  //  printf("[handler] E called \n"); 
    unsigned short k = st->reg[(opcode >> 8) & 0xF];
    switch (opcode & 0xFF) {
        case 0x9E: // EX9E - skips next instr if key in rgstr X is pressed
            if(st->keys[k & 0xF] == 1) {
                st->pc += 2; 
            }
            break; 

        case 0xA1: // EXA1 skips next instr if key in rgstr X is not pressed
            if(st->keys[k & 0xF] == 0) {
                st->pc += 2; 
            }
            break; 
    }
}

void f_h(struct state *st, unsigned short opcode) {
 //   printf("[handler] F called \n"); 
    unsigned short x; 
    unsigned char c =  0; 
     switch (opcode & 0xFF) {
        case 0x07:
            // FX07, set rgstr X to value of delay timer
            st->reg[(opcode >> 8) & 0xF] = st->del; 
            break; 
        case 0x0A:
            // FX0A, wait for keypress and store in rgstr X 
            while (x != 1) {
                for(c; c < 0xF; c++) {
                    if (st->keys[c] == 1) {
                        x = 1;
                    }
                }
            }
            st->reg[(opcode >> 8) & 0xF] = c; 
            break; 
        case 0x15:
            // FX15, set delay timer to rgstr X
            st->del = st->reg[(opcode >> 8) & 0xF]; 
            break; 
        case 0x18: 
            /// WORKS 
            // FX18, set sound timer to rgstr X
            st->sound = st->reg[(opcode >> 8) & 0xF]; 
            break; 
        case 0x1E:
            // WORKS 
            // FX1E - add rgstr X to I 
            st->I += st->reg[(opcode >> 8) & 0xF]; 
            break; 
        case 0x29:
            // WORKS 
            // FX29 - set I to to location of char in rgstr X
            st->I = st->reg[((opcode >> 8) & 0xF)] * 5; 
            break; 
        case 0x33: 
            // WORKS 
            // FX33 - take value of rgstr X, 
            //      stores 100's dgt in I, 10's in I+1, and 1's in I+2
            x = st->reg[(opcode >> 8) & 0xF]; 
            st->mem[st->I] = (unsigned char) floor((double)x/(double)100.00); // 100's 
            st->mem[st->I + 1] = (unsigned char)floor((x % 100) / 10.0); // 10's
            st->mem[st->I + 2] = x % 10; // 1's 
            break; 
        case 0x55: 
            // WORKS 
            // FX55 - stores rgstrs 0 - X (included) start at I 
            for (int i = 0; i <= ((opcode >> 8) & 0xF); i++) {
                st->mem[st->I + i] = st->reg[i]; 
            }
            break; 
        case 0x65:
            // WORKS 
            // FX65 - fills rgstrs 0 - X (included) with values from mem starting at I 
            for (int i = 0; i <= ((opcode >> 8) & 0xF); i++) {
                st->reg[i] = st->mem[st->I + i];  
            }
            break; 
    }
}