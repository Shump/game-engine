
CXX = clang++
CFLAGS = -Wall -std=c++11 -stdlib=libc++ -Wno-extra-tokens -O0 -g

ODIR = obj

LIBS = 	-lglfw \
				-lboost_filesystem \
				-lboost_system \
				-lassimp \
				-framework Cocoa \
				-framework OpenGL

DEPS = GraphicsEngine.hpp \
			 Scene.hpp \
			 Shader.hpp \
			 ShaderProgram.hpp \
			 Model.hpp \
			 Face.hpp \
			 AssImporter.hpp \
			 Importer.hpp

_OBJ = GraphicsEngine.o \
 			 Scene.o \
 			 Shader.o \
 			 ShaderProgram.o \
 			 Model.o \
 			 AssImporter.o \
 			 main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

dark: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

#all:
	#$(CXX) $(CFLAGS) $(LIBS) GraphicsEngine.cpp Scene.cpp Shader.cpp ShaderProgram.cpp Model.cpp AssImporter.cpp main.cpp

#all:
	#$(CXX) $(CFLAGS) -c Scene.cpp

#gcc:
	#g++ -Wall -lglfw -framework Cocoa -framework OpenGL main.cpp




