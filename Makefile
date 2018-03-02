CPP= g++
CPPFLAGS= -std=c++11 -stdlib=libc++ -lstdc++ -Weverything -Wno-c++98-compat -Wno-padded
LINKS= -lncurses
OBJ= ncurses.o

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

	%.o: %.cpp
		$(CPP) -c $(CPPFLAGS) -o $@ $<

clean:
	rm character boneyard bag *.o
