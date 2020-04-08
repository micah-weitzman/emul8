## Emul8 : Micah Weitzman - ESE350 Spring 2020
[`wmicah at seas dot upenn dot edu`](mailto:wmicah@seas.upenn.edu)
### Compilation
Run the following commands to clear logs and old object files, and to create a new `./Executeable` file. 
```shell 
$ make clean 
$ make 
```
### Plaing a Game
To play anyone of the games listed in the `games/` folder, either run the following from the command line: 
```shell 
$./Executable [GAME]
```
Or, you could run `$ ./Executable` and input the game when prompted. 
###Files
```
├── beep.aiff
├── Executable
├── games
│   ├── 15PUZZLE
│   ...
│   └── WIPEOFF
├── LICENSE
├── Makefile
├── obj
│   ├── emul8.o
│   ├── errors.o
│   ├── gamul.o
│   └── handler.o
├── README.md
├── run.sh
├── src
│   ├── emul8.c
│   ├── errors.c
│   ├── errors.h
│   ├── gamul.c
│   ├── gamul.h
│   ├── handler.c
│   ├── handler.h
│   └── state.h
└── test.py
```
