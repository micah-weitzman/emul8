/* ESE 350, Spring 2018
 * ------------------
 * Starter code for Lab 4
 *
 * The main purpose is to provide all the FreeGLUT
 * code required to handle display and input.
 * 
 * You are encouraged and, in some cases, required to edit
 * the given functions to suit your implementation.
 *
 * You are by no means bound to use all/any of the given code
 * or required to stick to this style.
 * Feel free to experiment and give a better solution.
 *
 * This uses the FreeGLUT libraries installed in your VM.
 * If you choose to use a different set of third party libraries,
 * please consult a TA.
 */
 
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamul.h"
#include <string.h>
#include "handler.h"
#include "state.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320
 

// MEMORY arrarys
unsigned char memory[4096] = {0};
unsigned short registers[16] = {0};
unsigned short stack[16] = {0};
unsigned char keys[16] = {0};

// struct that hold all of the memory stuff 
 struct state st;

static void init_state() {
	// store font starting at memory addr 0 
	memcpy(memory, fontset, FONTSET_SIZE + 1); 

	// 4k memory location 
    st.mem = memory; 
	st.pc = 0x200; 

	// stack 
    st.stack = stack; 
    st.sp = 0; 

    // general purpose registers 
    st.reg = registers; 

    // delay and sound registers 
    st.del = 0; 
	st.sound = 0;

	// keys pressed
	st.keys = keys; 
}

// current optcode; 
unsigned short opt; 




void degbug() {
	// printf("----------------------------\n");
	// printf("-------    DEBUGG    -------\n");
	// printf("----------------------------\n"); 
	// printf("OPCODE: %X\n", opt);
	// printf("I : [0x%X (%u)] = %u\n", st.I, st.I, st.mem[st.I]); 
	// printf("Program Counter: %X\n", st.pc);
	// for (int i = 0; i < 16; i++) {
	// 	printf("[Reg%X] %d \n", i, *(st.reg + i)); 
	// }
	// if (st.sp > 0 ) {
	// 	printf("--- STACK ---\n");
	// 	for (int j = 0; j < st.sp; j++) {
	// 		printf("[Stack %i] %u \n", j, st.stack[j]); 
	// 	}
	// 	printf("- - - - - -\n");
	// }
	// printf("Sound: %u\n", st.sound);
	// printf("Delay: %u\n", st.del);
	// printf("----------------------------\n");
}


//architecture we are emulating, refer gamul.h
static gamul8 gamer;




// method to draw a single pixel on the screen
void draw_square(float x_coord, float y_coord);

// update and render logic, called by glutDisplayFunc
void render();

// idling function for animation, called by glutIdleFunc
void idle();

// initializes GL 2D mode and other settings
void initGL();

// function to handle user keyboard input (when pressed) 
void your_key_press_handler(unsigned char key, int x, int y);

// function to handle key release
void your_key_release_handler(unsigned char key, int x, int y);



/*	FUNCTION: main
 *  --------------
 *	Main emulation loop. Loads ROM, executes it, and draws to screen.
 *  You may also want to call here the initialization function you have written
 *  that initializes memory and registers.
 *	PARAMETERS:
 *				argv: number of command line arguments
 *				argc[]: array of command line arguments
 *	RETURNS:	usually 0
 */
int main(int argc, char *argv[])
{
    init_state(); 

	// Get input from user which game to play
	char dest[100] = "./games/";
	
	char str[100] = " "; 
	if (argc != 2) {
		printf("Game to play?: \n");
		scanf("%s", str);
		load_file(strcat(dest, str),  &st.mem[0x200]); 
	} else {
		load_file(strcat(dest, argv[1]),  &st.mem[0x200]); 
	}


	// DEBUG: print out first 20 register values 
	int l = 20;
	printf("-----------------------------\n");
	printf("----- FIRST %d REGISTERS ----\n", l);
	printf("-----------------------------\n");
	for (int i = 0; i < l*2; i+=2) {
		printf("%X : %2.2X%2.2X \n", st.pc + i, st.mem[st.pc + i], st.mem[st.pc+i+1]); 
	}
	printf("-----------------------------\n");





	// seed random variable for use in emulation
	srand(time(NULL));

	// initialize GLUT
	glutInit(&argc, argv);

	// initialize display and window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("ESE 519 - Gamul8r");

	// initialize orthographic 2D view, among other things
	initGL();
	 
	// handle key presses and releases
	glutKeyboardFunc(your_key_press_handler);
	glutKeyboardUpFunc(your_key_release_handler);

	// GLUT draw function
	glutDisplayFunc(render);

	// GLUT idle function, causes screen to redraw
	glutIdleFunc(idle);

	// main loop, all events processed here
	glutMainLoop();

	return 0;
}

/*	FUNCTION: draw_square
 *  ----------------------
 *	Draws a square. Represents a single pixel
 *  (Up-scaled to a 640 x 320 display for better visibility)
 *	PARAMETERS: 
 *	x_coord: x coordinate of the square
 *	y_coord: y coordinate of the square
 *	RETURNS: none
 */
void draw_square(float x_coord, float y_coord)
{
	// draws a white 10 x 10 square with the coordinates passed

	glBegin(GL_QUADS);  //GL_QUADS treats the following group of 4 vertices 
						//as an independent quadrilateral

		glColor3f(1.0f, 1.0f, 1.0f); 	//color in RGB
										//values between 0 & 1
										//E.g. Pure Red = (1.0f, 0.0f, 0.0f)
		glVertex2f(x_coord, y_coord);			//vertex 1
		glVertex2f(x_coord + 10, y_coord);		//vertex 2
		glVertex2f(x_coord + 10, y_coord + 10);	//vertex 3
		glVertex2f(x_coord, y_coord + 10);		//vertex 4

		//glVertex3f lets you pass X, Y and Z coordinates to draw a 3D quad
		//only if you're interested

	glEnd();
}

/*	FUNCTION: render
 *  ----------------
 *	GLUT render function to draw the display. Also emulates one
 *	cycle of emulation.
 *	PARAMETERS: none
 *	RETURNS: none
 */
void render()
{

	// clears screen
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	// get optcode and pass to optcode handler 
    opt = get_opt(&st); 
    (*handler_ptr_array[(opt >> 12)])(&st, opt);     
    // Debugging function 
    degbug(); 

    // handlers for delay and sound
    sound_hanlder(&st); 
    delay_handler(&st); 


	// draw a pixel for each display bit
	int i, j;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		for (j = 0; j < SCREEN_HEIGHT; j++) {
			if (gamer.display[i][j] == 1) {
				draw_square((float)(i * 10), (float)(j * 10));
			}
		}
	}

	// swap buffers, allows for smooth animation
	glutSwapBuffers();
}

/*	FUNCTION: idle
 *  -------------- 
 *	GLUT idle function. Instructs GLUT window to redraw itself
 *	PARAMETERS: none
 *	RETURNS: none
 */
void idle()
{
	// gives the call to redraw the screen
	glutPostRedisplay();
}

/*	FUNCTION: initGL
 *  ----------------
 *	Initializes GLUT settings.
 *	PARAMETERS: none
 *	RETURN VALUE: none
 */
void initGL()
{
	// sets up GLUT window for 2D drawing
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// clears screen color (RGBA)
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

/*	FUNCTION: your_key_press_handler
 *  --------------------------------
 *	Handles all keypresses and passes them to the emulator.
 *  This is also where you will be mapping the original GAMUL8
 *  keyboard layout to the layout of your choice
 *  Something like this:
 *  |1|2|3|C|		=>		|1|2|3|4|
 *	|4|5|6|D|		=>		|Q|W|E|R|
 *	|7|8|9|E|		=>		|A|S|D|F|
 *	|A|0|B|F|		=>		|Z|X|C|V|
 *	PARAMETERS: 
 *	key: the key that is pressed.
 *	x: syntax required by GLUT
 *	y: syntax required by GLUT
 *  (x & y are callback parameters that indicate the mouse location
 *  on the window. We are not using the mouse, so they won't be used, 
 *  but still pass them as glutKeyboardFunc needs it.) 
 *	RETURNS: none
 *  NOTE: If you intend to handle this in a different manner, you need not
 *  write this function.
 */
void your_key_press_handler(unsigned char key, int x, int y)
{
	switch (key) {
		case '1':
			st.keys[1] = 1; 
			break;
		case '2':
			st.keys[2] = 1; 
			break;
		case '3':
			st.keys[3] = 1;  
			break;
		case '4':
			st.keys[0xC] = 1; 
			break;
		case 'q':
			st.keys[4] = 1; 
			break;
		case 'w':
			st.keys[5] = 1; 
			break;
		case 'e':
			st.keys[6] = 1; 
			break;
		case 'r':
			st.keys[0xD] = 1; 
			break;
		case 'a':
			st.keys[7] = 1; 
			break;
		case 's':
			st.keys[8] = 1;
			break; 
		case 'd':
			st.keys[9] = 1;
			break; 
		case 'f':
			st.keys[0xE] = 1; 
			break;
		case 'z':
			st.keys[0xA] = 1; 
			break;
		case 'x':
			st.keys[0] = 1; 
			break;
		case 'c':
			st.keys[0xB] = 1; 
			break;
		case 'v':
			st.keys[0xF] = 1; 
			break;
	}

}

/*	FUNCTION: your_key_release_handler
 *  --------------------------------
 *	Tells emulator if any key is released. You can maybe give
 *  a default value if the key is released.
 *	PARAMETERS: 
 *	key: the key that is pressed.
 *	x: syntax required by GLUT
 *	y: syntax required by GLUT
 *  (x & y are callback parameters that indicate the mouse location
 *  on the window. We are not using the mouse, so they won't be used, 
 *  but still pass them as glutKeyboardFunc needs it.) 
 *	RETURNS: none
 *  NOTE: If you intend to handle this in a different manner, you need not
 *  write this function.
 */
void your_key_release_handler(unsigned char key, int x, int y)
{
	switch (key) {
		case '1':
			st.keys[1] = 0;
			break;
		case '2':
			st.keys[2] = 0;
			break;
		case '3':
			st.keys[3] = 0;
			break;
		case '4':
			st.keys[0xC] = 0;
			break;
		case 'q':
			st.keys[4] = 0;
			break; 
		case 'w':
			st.keys[5] = 0;
			break;
		case 'e':
			st.keys[6] = 0;
			break;
		case 'r':
			st.keys[0xD] = 0;
			break;
		case 'a':
			st.keys[7] = 0;
			break;
		case 's':
			st.keys[8] = 0;
			break; 
		case 'd':
			st.keys[9] = 0;
			break; 
		case 'f':
			st.keys[0xE] = 0;
			break;
		case 'z':
			st.keys[0xA] = 0;
			break;
		case 'x':
			st.keys[0] =  0;
			break;
		case 'c':
			st.keys[0xB] = 0; 
			break;
		case 'v':
			st.keys[0xF] = 0;
			break;
	}

}



// BAD FUNCTION THAT draws 
// If clr param == 0 , then clear the screen
// Otherwise, draw as normal 
void disp_f(unsigned char x, unsigned char y, unsigned char n, unsigned char clr) {
	if (clr == 0) {
		for (int i = 0; i < SCREEN_WIDTH; i++) {
			for (int j = 0; j < SCREEN_HEIGHT; j++) {
				gamer.display[i][j] = 0; 
			}
		}
	} else {
		display_func(&st, &gamer, x, y, n); 
	}
}