CPP= g++
CPPFLAGS= -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat
LINKS= -lncurses -ljsoncpp
OBJ= ncurses.o node.o
CHARACTER_SHIT= character.o bag.o feet.o hand.o

CHARACTER_SHIT= character_test.o character.o bag.o
BAG_SHIT= bag_test.o bag.o
ENEMY_SHIT= enemy_test.o enemy.o

character: $(CHARACTER_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

bag: $(BAG_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

enemy: $(ENEMY_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

boneyard: $(OBJ)
	$(CPP) -o $@ $^ $(LINKS)

#	%.o: %.cpp
#		$(CPP) -c $(CPPFLAGS) -o $@ $<

clean:
	rm character boneyard bag *.o
