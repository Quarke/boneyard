CPP= g++
CPPFLAGS= -std=c++11 -stdlib=libc++ -Wall -Wno-c++98-compat
LINKS= -lncurses -ljsoncpp
OBJ= ncurses.o node.o  enemy.o gamestate.o
GAMESTATE_SHIT= gamestate.o
ENEMY_SHIT= enemy_test.o enemy.o

all: boneyard

gamestate: $(GAMESTATE_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

enemy: $(ENEMY_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

boneyard: $(OBJ)
	$(CPP) -o $@ $^ $(LINKS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $<

clean:
	rm gamestate boneyard bag enemy *.o
