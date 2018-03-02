CPP= g++
CPPFLAGS= -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat
LINKS= -lncurses -ljsoncpp
OBJ= ncurses.o node.o
CHARACTER_SHIT= character.o bag.o feet.o hand.o

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $<

character: $(CHARACTER_SHIT)
	$(CPP) $(CPPFLAGS) $^ -o $@

boneyard: $(OBJ)
	$(CPP) -o $@ $^ $(LINKS)

clean:
	rm boneyard *.o
