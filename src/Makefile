#compiler variable
CC = g++
INCL = -Isfml/include
LIBS = -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system
#optimization variable
OPT = -O0

#add cpp files here
CPPFILES = main.cpp Game.cpp State.cpp GameState.cpp MainMenuState.cpp Component.cpp Entity.cpp EntityManager.cpp Button.cpp
#define .o files to be created here
OBJECTS = main.o Game.o State.o GameState.o MainMenuState.o Component.o Entity.o EntityManager.o Button.o

BINARY = app

all: $(BINARY)

#executable var is dependant on the existence of our object files
$(BINARY):$(OBJECTS)
#g++ -o app main.o -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
	$(CC) -o $@ $^ $(LIBS)

#regex that states that any object file, to be created, must be created from %(anything).cpp file
%.o:%.cpp
	$(CC) -c -o $@ $< $(INCL)
# $@ = %.o
# $^ = %.cpp

# all .o files possess a dependency on Game.hpp
$(OBJECTS): Game.hpp ComponentsUtil.hpp ResourceManager.hpp

clean: 
	rm -rf $(BINARY) $(OBJECTS)
