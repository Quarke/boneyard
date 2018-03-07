CPP= g++
CPPFLAGS= -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat
LINKS= -lncurses -ljsoncpp
OBJ= ncurses.o node.o gamestate.o
GAMESTATE_SHIT= gamestate.o

GAMESTATE_SHIT= gamestate_test.o gamestate.o
BAG_SHIT= bag_test.o bag.o
ENEMY_SHIT= enemy_test.o enemy.o

all: boneyard

gamestate: $(GAMESTATE_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

bag: $(BAG_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

enemy: $(ENEMY_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

boneyard: $(OBJ)
	$(CPP) -o $@ $^ $(LINKS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $<

clean:
	rm GAMESTATE boneyard bag enemy *.o
