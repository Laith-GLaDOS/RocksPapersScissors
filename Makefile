debug:
	gcc src/pure/main.c -o RocksPapersScissors -lSDL2 -lSDL2_image
	mv RocksPapersScissors bin/debug/
	./bin/debug/RocksPapersScissors

debug_windows:
	gcc src/windows/main.c -o RocksPapersScissors.exe -lSDL2 -lSDL2_image
	move RocksPapersScissors.exe bin/debug/
	.\bin/debug/RocksPapersScissors.exe

release:
	gcc src/pure/main.c -o RocksPapersScissors -lSDL2 -lSDL2_image -O3 -s
	mv RocksPapersScissors bin/release/linux/

release_windows:
	gcc src/windows/main.c -o RocksPapersScissors.exe -lSDL2 -lSDL2_image -O3 -s
	move RocksPapersScissors.exe bin/release/windows/