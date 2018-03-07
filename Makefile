CPP= g++
CPPFLAGS= -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat
LINKS= -lncurses -ljsoncpp
OBJ= ncurses.o node.o gamestate.o
GAMESTATE_SHIT= gamestate.o

GAMESTATE_SHIT= gamestate.o
BAG_SHIT= bag_test.o bag.o
ENEMY_SHIT= enemy_test.o enemy.o
#GAME_STATE_SHIT= gamestate_test.o game_state.o

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
	rm gamestate boneyard bag enemy *.o
