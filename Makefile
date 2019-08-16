all: grid-test2.cpp
	g++ grid-test2.cpp -lsfml-graphics -lsfml-window -lsfml-system

test: grid-test2.cpp
	cppcheck grid-test2.cpp --enable=all
