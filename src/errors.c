#include <stdio.h>

// FUNCTION: checks an opcode to make sure its valid 
// 		If invalid, it exits the program 
void valid_opcode_err(unsigned short op) {
 
	if (
		// 00E0/00EE
		(
			(((op >> 12) & 0xF) == 0) &&
				(
					((op & 0xFFF) != 0x0E0) &&
					((op & 0xFFF) != 0x0EE)
				)
		) ||

		// 1NNN - all valid 
		// 2NNN - all valid
		// 3NNN - all valid
		// 4XNN - all valid 

		// 5XY0 
		(
			(((op >> 12) & 0xF) == 5) && 
				((op & 0xF) != 0)
		) || 

		// 6XNN - all valid 
		// 7XNN - all valid 

		// 8XY_ - last # 8-D and F 
		(
			(((op >> 12) & 0xF) == 8) && 
				(
					((op & 0xF > 7 ) && ((op & 0xF) < 0xE)) || 
					((op & 0xF) == 0xF)
				)
		) ||

		// 9XY0 
		(
			(((op >> 12) & 0xF) == 9) && 
			((op & 0xF) != 0)
		) || 

		// ANNN - all valid 
		// BNNN - all valid 
		// CXNN - all valid 
		// DXYN - all valid 

		// EX9E/EXA1 
		(
			(((op >> 12) & 0xF) == 0xE) && 
				(
					((op & 0xFF) != 0x9E) && 
					((op & 0xFF) != 0xA1)
				)
		) || 

		// FX07 / FX0A / FX15 / FX18 / FX1E  
		// FX29 / FX33 / FX55 / FX66 
		(
			(((op >> 12) & 0xF) == 0xF) && 
				(
					((op & 0xFF) != 0x07) && 
					((op & 0xFF) != 0x0A) && 
					((op & 0xFF) != 0x15) && 
					((op & 0xFF) != 0x18) && 
					((op & 0xFF) != 0x1E) && 
					((op & 0xFF) != 0x29) && 
					((op & 0xFF) != 0x33) && 
					((op & 0xFF) != 0x55) && 
					((op & 0xFF) != 0x66)
				)
		)


		) {
		fprintf(stderr, "[err] Invalid opcode: %.4X\n", op); 
		exit(3); 
	}
}

// FUNCTION: checks to see if imput file is too big
void file_too_big_err(int file_size) {
	if (file_size > (0xFFF - 0x200)) {
		fprintf(stderr, "[err] File size is too large\n");
		exit(1); 
	}
}