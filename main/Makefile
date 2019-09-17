all: grid-test2.cpp
	g++ map.cpp mapobject.cpp character.cpp item.cpp gamemanager.cpp grid-test2.cpp -lsfml-graphics -lsfml-window -lsfml-system -o app

test: grid-test2.cpp
	cppcheck grid-test2.cpp --enable=all
