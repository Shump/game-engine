
CXX = clang++
CFLAGS = -Wall -std=c++11 -stdlib=libc++ -Wno-extra-tokens -O0 -g

LIBS = 	-lglfw \
				-lboost_filesystem \
				-lboost_system \
				-lassimp \
				-framework Cocoa \
				-framework OpenGL

all:
	$(CXX) $(CFLAGS) $(LIBS) ../Scene.cpp ../Model.cpp ../AssImporter.cpp import.cpp
