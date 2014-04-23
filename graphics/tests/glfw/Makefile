
CXX = clang++
CFLAGS = -Wall -std=c++11 -stdlib=libc++

LIBS = 	-lglfw \
				-lboost_filesystem \
				-lboost_system \
				-lassimp \
				-framework Cocoa \
				-framework OpenGL

all:
	$(CXX) $(CFLAGS) $(LIBS) main.cpp

gcc:
	g++ -Wall -lglfw -framework Cocoa -framework OpenGL main.cpp

AssImporter.o: AssImporter.cpp
	$(CXX) -c $(CFLAGS) AssImporter.cpp
