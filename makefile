build:
	$(if $(filter $(OS),Windows_NT), if exist program.exe (del program.exe), rm -f program.exe)
	g++ -g -std=c++11 -Wall main.cpp hashmap.cpp -o program.exe
	
run:
	./program.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program.exe
