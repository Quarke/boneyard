/*

CURHELL2.C
==========
(c) Copyright Paul Griffiths 1999
Email: mail@paulgriffiths.net

"Hello, world!", ncurses style (now in colour!)

*/
#include <json/json.h>
#include <curses.h>

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <locale>

#include "node.h"

void clearScreen(){
    for(int i = 2; i < LINES; i++){
        move(i, 1);          // move to begining of line
        clrtoeol();
    }
}

int main(void) {
    std::ifstream ifs("script.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    // Create an empty unordered_map
    std::unordered_map<std::string, Node> nodeMap;
    Node n;
    for(Json::Value::iterator i = obj.begin(); i !=obj.end(); ++i){
        Json::Value key = i.key();
        Json::Value value = (*i);
        std::cout <<"Key: " << key.toStyledString();
        n.enterDescription = value["enterDescription"].asString();
        n.title = value["title"].asString();
        n.enemy = value["enemy"].asString();
        n.exitNorth = value["exitNorth"].asString();
        n.exitSouth = value["exitSouth"].asString();
        n.exitEast = value["exitEast"].asString();
        n.exitWest  =value["exitWest"].asString();
        n.onEnter = value["onEnter"].asString();
        n.onLeave = value["onLeave"].asString();
        n.extra1 = value["extra1"].asString();
        n.extra2 = value["extra2"].asString();
        n.extra3 = value["extra3"].asString();



        printf("title: %s\n", n.title.c_str());
        printf("enterDescription: %s\n", n.enterDescription.c_str());
        printf("enemy: %s\n", n.enemy.c_str());
        printf("exitNorth: %s\n", n.exitNorth.c_str());
        printf("exitSouth: %s\n", n.exitSouth.c_str());
        printf("exitEast: %s\n", n.exitEast.c_str());
        printf("exitWest: %s\n", n.exitWest.c_str());
        printf("onEnter: %s\n", n.onEnter.c_str());
        printf("oneLeave: %s\n", n.onLeave.c_str());
        printf("extra1: %s\n", n.extra1.c_str());
        printf("extra2: %s\n", n.extra2.c_str());
        printf("extra3: %s\n", n.extra3.c_str());
        printf("objects: \n");
        for(auto itr: value["object"]){
            printf("%s, ", itr.toStyledString().c_str());
            n.objects.push_back(itr.asString());
        }
        //std::string stringKey = key.asString();
        //nodeMap[stringKey] = n;
    }

  WINDOW * mainwin;
  /*  Initialize ncurses  */

  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }

  start_color();                    /*  Initialize colours  */
  /*  Print message  */


  /*  Make sure we are able to do what we want. If
  has_colors() returns FALSE, we cannot use colours.
  COLOR_PAIRS is the maximum number of colour pairs
  we can use. We use 13 in this program, so we check
  to make sure we have enough available.               */

  if ( has_colors() && COLOR_PAIRS >= 13 ) {

    int x = 1;

    /*  Initialize a bunch of colour pairs, where:
      init_pair(pair number, foreground, background);
      specifies the pair.
    */

    init_pair(1,  COLOR_RED,     COLOR_BLACK);
    init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
    init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
    init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
    init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
    init_pair(8,  COLOR_WHITE,   COLOR_RED);
    init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
    init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
    init_pair(11, COLOR_WHITE,   COLOR_BLUE);
    init_pair(12, COLOR_WHITE,   COLOR_MAGENTA);
    init_pair(13, COLOR_BLACK,   COLOR_CYAN);

    /*  Use them to print of bunch of "Hello, world!"s

    while ( x <= 13 ) {
      color_set(x, NULL);
      mvaddstr(6 + x, 32, " Hello, world! ");
      x++;
    } */
  }

  /*  Refresh the screen and sleep for a
  while to get the full screen effect  */

    //sleep(10);
    color_set(13, NULL);
    refresh();

    char mesg[]="> ";      /* message to be appeared on the screen */
    char input[20];
    do{
        //clearScreen();
        initscr();                /* start the curses mode */
        mvprintw(LINES - 2, 0, mesg);
        move(LINES -2, 1);          // move to begining of line
        clrtoeol();
        getstr(input);
        //clear();
    } while(strcmp(input, "quit") != 0);

  /*  Clean up after ourselves  */
  delwin(mainwin);
  endwin();
  refresh();

  return EXIT_SUCCESS;
}
