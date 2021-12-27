debug:
	gcc src/main.c -o RocksPapersScissors -lSDL2 -lSDL2_image
	mv RocksPapersScissors bin/debug/
	./bin/debug/RocksPapersScissors

release:
	gcc src/main.c -o RocksPapersScissors -lSDL2 -lSDL2_image -O3 -s
	mv RocksPapersScissors bin/release/

clean:
	rm bin/release/RocksPapersScissors
	rm bin/debug/RocksPapersScissors

install:
	mv bin/release/RocksPapersScissors /usr/local/bin/
