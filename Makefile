CPP= clang
CPPFLAGS= -std=c++11 -stdlib=libstdc++ -Weverything -Wno-c++98-compat
LINKS= -lncurses
OBJ= ncurses.o
CHARACTER_SHIT= character.o bag.o feet.o hand.o

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $<

character: $(CHARACTER_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

boneyard: $(OBJ)
	$(CPP) -o $@ $^ $(LINKS)

clean:
	rm boneyard *.o
