void zero_h(STATE* st, unsigned short opcode); 

void one_h(STATE* st, unsigned short opcode); 

void two_h(STATE* st, unsigned short opcode); 

void three_h(STATE* st, unsigned short opcode); 

void four_h(STATE* st, unsigned short opcode); 

void five_h(STATE* st, unsigned short opcode); 

void six_h(STATE* st, unsigned short opcode); 

void seven_h(STATE* st, unsigned short opcode); 

void eight_h(STATE* st, unsigned short opcode); 

void nine_h(STATE* st, unsigned short opcode); 

void a_h(STATE* st, unsigned short opcode); 

void b_h(STATE* st, unsigned short opcode); 

void c_h(STATE* st, unsigned short opcode); 

void d_h(STATE* st, unsigned short opcode); 

void e_h(STATE* st, unsigned short opcode); 

void f_h(STATE* st, unsigned short opcode); 

void (*handler_ptr_array[]) (STATE*, unsigned short) = {zero_h, one_h, two_h, three_h, four_h, five_h, six_h, seven_h, eight_h, nine_h, a_h, b_h, c_h, d_h, e_h, f_h}; 
