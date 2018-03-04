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
#include <unistd.h>
#include <locale>
#include <sstream>

#include "node.h"

using namespace std;

struct coordinate {int row; int col; };

static struct coordinate north_exit;
static struct coordinate south_exit;
static struct coordinate east_exit;
static struct coordinate west_exit;

static unsigned long MAX_WIDTH = 150;

//solely so the compiler shuts the fuck up
void print_current_room(Node * n);
void mvprintw_center(int row, int col, std::string msg);
std::string suggest(std::string, Node * n);

void print_current_room(Node * n) {
  //print the title at top center
  mvprintw_center(3, COLS/2, n->title);

  //print the description just below it
  mvprintw_center(5, COLS/2, n->enterDescription);

  //print the exit
  std::vector<string> locations = {"exitNorth", "exitSouth", "exitEast", "exitWest"};

  for(std::string location : locations) {
    //seek and iterator to the location

    if(strcmp(location.c_str(), "exitNorth") == 0) {
      if(!n->exitNorth.empty()) {
        mvprintw_center(north_exit.row, north_exit.col, n->exitNorth);
      }
      else {
          mvprintw(north_exit.row, north_exit.col, "X");
      }
    }
    else if(strcmp(location.c_str(), "exitSouth") == 0) {
      if(!n->exitSouth.empty()) {
        mvprintw_center(south_exit.row, south_exit.col, n->exitSouth);
      }
      else {
          mvprintw(south_exit.row, south_exit.col, "X");
      }
    }
    else if(strcmp(location.c_str(), "exitWest") == 0) {
      if(!n->exitWest.empty()) {
        mvprintw_center(west_exit.row, west_exit.col, n->exitWest);
      }
      else {
          mvprintw(west_exit.row, west_exit.col, "X");
      }
    }
    else {
      // East exit is also a special case since we dont want text to wrap from right side to left.
      // We need a clean print to end of screen here
      // shift the COL location to have enough room for the string, so it doesn't wrap a line
      if(!n->exitEast.empty()) {
        int calc_cols = COLS - static_cast<int>(n->exitEast.size()) - 1;
        mvprintw_center(east_exit.row, calc_cols, n->exitEast);
      }
      else {
          mvprintw(east_exit.row, east_exit.col, "X");
      }
    }
  }
}

void mvprintw_center(int row, int col, std::string msg) {
  // row and col denote the top-center location of the printout
  // the maximum width of any print in defined globally
  // we can use these facts to print centered strings downward


  // TODO: Rewrite to break on words for easy reading

  unsigned long pos = 0;
  int row_actual = row;
  int col_actual = col;

  while(pos < msg.size()) {
    std::string sub_string = msg.substr(pos, MAX_WIDTH);

    unsigned long ss_size = sub_string.size();
    col_actual = col -  static_cast<int>(ss_size/2);

    if(col_actual < 0) {
      col_actual = 0;
    }

    mvprintw(row_actual, col_actual, sub_string.c_str());
    row_actual += 1;
    pos += MAX_WIDTH;
  }
}

std::string suggest(std::string input, Node * n) {
  std::vector<string> rc = {};

  if(!n->exitNorth.empty() && n->exitNorth.find(input) != std::string::npos){
    rc.push_back(n->exitNorth);
  }
  if(!n->exitSouth.empty() && n->exitSouth.find(input) != std::string::npos){
    rc.push_back(n->exitSouth);
  }
  if(!n->exitEast.empty() && n->exitEast.find(input) != std::string::npos){
    rc.push_back(n->exitEast);
  }
  if(!n->exitWest.empty() && n->exitWest.find(input) != std::string::npos){
    rc.push_back(n->exitWest);
  }

  std::ostringstream oss;

  if (!rc.empty())
  {
    // Convert all but the last element to avoid a trailing ","
    std::copy(rc.begin(), rc.end()-1,
        std::ostream_iterator<string>(oss, ", "));

    // Now add the last element with no delimiter
    oss << rc.back();
  }

  return oss.str();

}

int main(void) {
    std::ifstream ifs("script.json");

    // Reader is deprecated, we are supposed to use a CharReaderBuilder and streams instead
    // Which is newer better practice, but it works so fuck it
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    // Create an empty unordered_map and
    std::unordered_map<std::string, Node> nodeMap;
    Node n;

    for(Json::Value::iterator i = obj.begin(); i !=obj.end(); ++i){
        Json::Value key = i.key();
        Json::Value value = (*i);

        n.enterDescription = value["enterDescription"].asString();
        n.title = value["title"].asString();
        n.enemy = value["enemy"].asString();
        n.exitNorth = value["exitNorth"].asString();
        n.exitSouth = value["exitSouth"].asString();
        n.exitEast = value["exitEast"].asString();
        n.exitWest = value["exitWest"].asString();
        n.onEnter = value["onEnter"].asString();
        n.onLeave = value["onLeave"].asString();
        n.extra1 = value["extra1"].asString();
        n.extra2 = value["extra2"].asString();
        n.extra3 = value["extra3"].asString();

        std::string stringKey = key.asString();
        nodeMap[stringKey] = n;
    }

  WINDOW * mainwin;
  /*  Initialize ncurses  */

  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }

  //disable automatic echoing of user input, needed for main control loop
  noecho();

  //Set maximum width for output string using the centering function
  MAX_WIDTH = static_cast<int>(MAX_WIDTH) < 3 * COLS/ 4 ? MAX_WIDTH : static_cast<unsigned long>(3 * COLS/ 4);

  if( LINES < 50) {
    fprintf(stderr, "Need a taller window. ");
    fprintf(stderr, "Current: %d, Needed: 50.\n", LINES);
    delwin(mainwin);
    endwin();
    refresh();
    exit(1);
  }

  else if( COLS < 100) {
    fprintf(stderr, "Need a wider window. ");
    fprintf(stderr, "Current: %d, Needed: 100.\n", COLS);
    delwin(mainwin);
    endwin();
    refresh();
    exit(1);
  }

  else {
    //Set the exit message locations
    north_exit.row = 1;
    north_exit.col = COLS / 2;

    south_exit.row = LINES - 2;
    south_exit.col = COLS / 2;

    east_exit.row = LINES / 2 - 1;
    east_exit.col =  COLS - 5;

    west_exit.row = LINES / 2 - 1;
    west_exit.col = 1;
  }

  start_color();

  if ( has_colors() && COLOR_PAIRS >= 13 ) {
    //overwrite colors with new rgb codes
    init_color(COLOR_BLACK, 570, 620, 700);
    init_color(COLOR_BLUE, 0, 173, 181);

    //set new pair: id, foreground, background
    init_pair(1,  COLOR_BLUE, COLOR_BLACK);

    color_set(1, NULL);
    wbkgd(mainwin, COLOR_PAIR(1));
  }

    refresh();

    char mesg[]="> ";
    std::string input = "";

    auto it = nodeMap.find("insideChurch");

    if(it == nodeMap.end()) {
      printf("%s\n", "Error reading nodeMap, no starting point 'insideChurch' found");
      exit(1);
    }

    // re-use Node n from above
    // set starting node using above method
    n = it->second;

    bool new_location = true;

    // Here is the main loopiness, clear -> print current info -> expose prompt -> interpret action -> move|stay -> loop
    do{
        clear();
        if(new_location){
          new_location = false;
          //Call the onEnter() function, whatever that does
          //onEnter();
        }

        // echo previous input to user
        mvprintw(LINES/2 + 5, COLS/2 - 20, input.c_str());

        //print information about current room
        print_current_room(&n);

        mvprintw(LINES / 2 + 1, COLS / 2 - 20, mesg);
        move(LINES / 2 + 1, COLS / 2 - 18);
        clrtoeol();

        cout << input << endl;

        char c = 0;
        input = "";
        int x, y;
        std::string rc = "";
        while (c != '\n') {
            c = static_cast<char>(getch());
            switch (c)
            {
                case '\t':
                    rc = suggest(input, &n);
                    if(!rc.empty() && rc.find(",") != std::string::npos) {
                      getyx(stdscr, y, x);
                      move(LINES / 2 + 5, COLS / 2 - 20);
                      clrtoeol();
                      printw(rc.c_str());
                      move(y, x);
                    }
                    else {
                      input = rc;
                      move(LINES / 2 + 1, COLS / 2 - 18);
                      clrtoeol();
                      printw(input.c_str());
                    }

                    break;
                case '\b':
                case 127:
                    input.pop_back();
                    move(LINES / 2 + 1, COLS / 2 - 18);
                    clrtoeol();
                    printw(input.c_str());
                    break;
                default:
                    addch(c);
                    input += c;
                    break;
            }
        }
        //trim all the new lines that somehow get added
        input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());

        it = nodeMap.find(input);

        if(it != nodeMap.end()){
          // valid location entered, call onLeave() function
          // onLeave();
          n = it->second;
          new_location = true;
        }

    } while( input.compare("quit") != 0 );

  /*  Clean up after ourselves  */
  delwin(mainwin);
  endwin();
  refresh();

  return EXIT_SUCCESS;
}
