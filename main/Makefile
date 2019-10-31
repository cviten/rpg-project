build: grid-test2.cpp # main # imgui.o
	# g++ main.o imgui.o -lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL -lglut -o app
	g++ map.cpp mapobject.cpp character.cpp item.cpp  gamemanager.cpp infowindow.cpp hud.cpp gameaction.cpp grid-test2.cpp \
	./SFML-imgui/libimgui.a \
	-Wall -Wextra \
	-lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL -lglut -o app \
	> compile-errors.log 2>&1

main: map.cpp mapobject.cpp character.cpp item.cpp gamemanager.cpp grid-test2.cpp
	g++ -c map.cpp mapobject.cpp character.cpp item.cpp gamemanager.cpp grid-test2.cpp \
	-Wall -Wextra
	# mv *.o ./bin/

#imgui.o: ./SFML-imgui/imgui-SFML.cpp ./GUI/SFML-imgui/imgui.cpp ./GUI/SFML-imgui/imgui_demo.cpp ./GUI/SFML-imgui/imgui_draw.cpp ./GUI/SFML-imgui/imgui_widgets.cpp
#	g++ -c ./SFML-imgui/imgui-SFML.cpp ./GUI/SFML-imgui/imgui.cpp ./GUI/SFML-imgui/imgui_demo.cpp \
	./GUI/SFML-imgui/imgui_draw.cpp ./GUI/SFML-imgui/imgui_widgets.cpp

# imgui-SFML.cpp imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_widgets.cpp

test: map.cpp hud.cpp ./tests/hudtests.h ./tests/maptests.h ./tests/maintest.cpp # mapobject.cpp character.cpp item.cpp gamemanager.cpp infowindow.cpp hud.cpp grid-test2.cpp
	g++ map.cpp hud.cpp ./tests/maintest.cpp \
	-lgtest -lgtest_main \
	-lsfml-graphics -lsfml-window -lsfml-system \
	-o test

runtest : test
	./test

# -lgtest -lgtest_main
# ./SFML-imgui/libimgui.a
