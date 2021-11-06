all:
	g++ main.cc sprite.cc SDF.cc track.cc -Wall -O3 -std=c++17 -ldl `sdl2-config --libs` -lSDL2 -lSDL2_image
