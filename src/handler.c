#include "gamul.h"

void zero_h(STATE* st, unsigned short opcode) {
    //TODO: clear screan or return from subreoutine 
}

void one_h(STATE* st, unsigned short opcode) {
    st->pc = (opcode & 0x0FFF); 
}


void two_h(STATE* st, unsigned short opcode) {
    st->sp++;
    st->sp = st->pc;
}

void three_h(STATE* st, unsigned short opcode) {
    if(st->reg[(opcode & 0xF00)] == (opcode & 0xFF)) {
        st->pc += 2; 
    }
}

void four_h(STATE* st, unsigned short opcode){
    if(st->reg[(opcode & 0xF00)] != (opcode & 0xFF)) {
        st->pc += 2; 
    }
}

void five_h(STATE* st, unsigned short opcode) {
    if(st->reg[(opcode & 0xF00)] == st->reg[(opcode & 0x0F0)]) {
        st->pc += 2; 
    }
}

void six_h(STATE* st, unsigned short opcode) {
    st->reg[opcode & 0xF00] = (opcode & 0xFF); 
}

void seven_h(STATE* st, unsigned short opcode) {
    st->reg[(opcode & 0xF00)] += (opcode & 0xFF); 
}

void eight_h(STATE* st, unsigned short opcode) {
    switch (opcode & 0x00F) {
        case 0:
            st->reg[(opcode & 0xF00)] = st->reg[(opcode & 0x0F0)]; 
        case 1: 
            st->reg[(opcode & 0xF00)] = st->reg[(opcode & 0xF00)] | st->reg[(opcode & 0x0F0)]; 
        case 2: 
            st->reg[(opcode & 0xF00)] = st->reg[(opcode & 0xF00)] & st->reg[(opcode & 0x0F0)]; 
        case 3: 
             st->reg[(opcode & 0xF00)] = st->reg[(opcode & 0xF00)] ^ st->reg[(opcode & 0x0F0)]; 
        case 4: 
             // TODO 
        case 5: 
             // TODO
        case 6: 
             st->reg[0xF] = st->reg[(opcode &0xF00)] & 0x00F; 
             st->reg[(opcode & 0xF00)] = st->reg[(opcode & 0xF00)] >> 1;
        case 7:
            // TODO
        case 0xE:
             st->reg[0xF] = st->reg[(opcode &0xF00)] & 0xF00;
             st->reg[(opcode & 0xF00)] = st->reg[(opcode & 0xF00)] << 1;
    }
}

void nine_h(STATE* st, unsigned short opcode){
    // TODO 
}

void a_h(STATE* st, unsigned short opcode) {
    st->I = (opcode & 0xFFF); 
}

void b_h(STATE* st, unsigned short opcode) {
    st->pc = (opcode & 0xFFF) + st->reg[0]; 
}

void c_h(STATE* st, unsigned short opcode) {
    st->reg[(opcode & 0xF00)] = (opcode & 0xFF); // & rand num
        // TODO find rand num generator
}

void d_h(STATE* st, unsigned short opcode) {
    // TODO DRAW FUNCTION ???
}

void e_h(STATE* st, unsigned short opcode) {
    //TODO:  skip if keyporessed opcode
}

void f_h(STATE* st, unsigned short opcode) {
    // TODO: lots todo here; 
}


















    
