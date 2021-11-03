all:
	g++ main.cc sprite.cc -Wall -O3 -std=c++17 -ldl `sdl2-config --libs`
