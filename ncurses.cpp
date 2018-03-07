#include <curses.h>

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <locale>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "gamestate.h"

using namespace std;

struct coordinate {int row; int col; };

static struct coordinate north_exit;
static struct coordinate south_exit;
static struct coordinate east_exit;
static struct coordinate west_exit;

static unsigned long MAX_WIDTH = 150;

//static std::string directions[4] = {"go north", "go south", "go east", "go west"};

//solely so the compiler shuts the fuck up
void print_current_room(Node * n);
void mvprintw_center(int row, int col, std::string msg);
std::string suggest(std::string, Node * n);


void print_current_room(Node * n) {
  //print the title at top center
  mvprintw_center(3, COLS/2, n->title);

  //print the description just below it
  mvprintw_center(5, COLS/2, n->enterDescription);
  fprintf(stderr, "hi there\n");
  fprintf(stderr, "%s\n", n->enterDescription.c_str());

  //print the exit
  std::vector<string> locations = {"exitNorth", "exitSouth", "exitEast", "exitWest"};

  for(std::string location : locations) {
    //seek and iterator to the location

    if(strcmp(location.c_str(), "exitNorth") == 0) {
      if(!n->exitNorth.empty()) {
        mvprintw_center(north_exit.row, north_exit.col, "North");
      }
    }
    else if(strcmp(location.c_str(), "exitSouth") == 0) {
      if(!n->exitSouth.empty()) {
        mvprintw_center(south_exit.row, south_exit.col, "South");
      }
    }
    else if(strcmp(location.c_str(), "exitWest") == 0) {
      if(!n->exitWest.empty()) {
        mvprintw_center(west_exit.row, west_exit.col, "West");
      }
    }
    else {
      // East exit is also a special case since we dont want text to wrap from right side to left.
      // We need a clean print to end of screen here
      // shift the COL location to have enough room for the string, so it doesn't wrap a line
      if(!n->exitEast.empty()) {
        int calc_cols = COLS - static_cast<int>(n->exitEast.size()) - 1;
        mvprintw_center(east_exit.row, calc_cols, "East");
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

// NOTE: change this to (string input, vector<string> stringsToCheck)
std::string suggest(std::string input, Node * n) {
  std::vector<string> rc = {};

  std::string nt = "Go North";
  std::string st = "Go South";
  std::string et = "Go East";
  std::string wt = "Go West";
  if(!n->exitNorth.empty() &&  nt.find(input) != std::string::npos){
    rc.push_back("Go North");
  }
  if(!n->exitSouth.empty() &&  st.find(input) != std::string::npos){
    rc.push_back("Go South");
  }
  if(!n->exitEast.empty() &&  et.find(input) != std::string::npos){
    rc.push_back("Go East");
  }
  if(!n->exitWest.empty() && wt.find(input) != std::string::npos){
    rc.push_back("Go West");
  }

  std::ostringstream oss;

  if (!rc.empty())
  {
    // Convert all but the last element to avoid a trailing ","
    std::copy(rc.begin(), rc.end()-1, std::ostream_iterator<string>(oss, ", "));

    // Now add the last element with no delimiter
    oss << rc.back();
  }

  return oss.str();

}

int main(void) {
  GameState gameState;
  gameState.createNodeMap();
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
    init_color(COLOR_CYAN, 0, 173, 181);

    //set new pair: id, foreground, background
    init_pair(1,  COLOR_CYAN, COLOR_BLACK);

    color_set(1, NULL);
    wbkgd(mainwin, COLOR_PAIR(1));
  }

    refresh();

    char mesg[]="> ";
    std::string input = "";

    auto it = gameState.getNodeMap().find("insideChurch");

    if(it == gameState.getNodeMap().end()) {
      printf("%s\n", "Error reading gameState.getNodeMap(), no starting point 'insideChurch' found");
      exit(1);
    }

    Node n;
    n = it->second;

    std::string newInfo;
    // Here is the main loopiness, clear -> print current info -> expose prompt -> interpret action -> move|stay -> loop
    do{
        clear();
        mvprintw(LINES/2 + 5, COLS/2 - 20, newInfo.c_str());

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
        // trigger for invalid command
        int fail_flag = -1;
        //trim all the new lines that somehow get added
        input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
        size_t spacePos = input.find(' ');
        if(spacePos != std::string::npos){
            auto first_token = input.substr(0, spacePos);
            auto second_token = input.substr(spacePos+1, std::string::npos);

            std::transform(first_token.begin(), first_token.end(), first_token.begin(), ::tolower);
            std::transform(second_token.begin(), second_token.end(), second_token.begin(), ::tolower);
            if(first_token.compare("go") == 0){
                std::string next =  gameState.getNextNode(second_token, &n);
                if(!(next.compare("invalid") == 0 || next.compare("") == 0)){
                    it = gameState.getNodeMap().find(next);
                    fail_flag = 0;
                    n = it->second;
                    newInfo = input;
                } else {
                    newInfo = "You can't go "+second_token;
                }
            }
            else if(first_token.compare("take") == 0){
                int objectFound = n.objectExists(second_token);
                if(objectFound == 0){
                    gameState.addItem(second_token);
                    fail_flag = 0;
                    newInfo = "You took "+second_token;
                } else {
                    newInfo = "You can't take "+second_token;
                }
            }
            else if(first_token.compare("drop") == 0){
                int itemFound = gameState.removeItem(second_token);
                if(itemFound == 0){
                    n.addObject(second_token);
                    fail_flag = 0;
                    newInfo = "You dropped "+second_token;
                }else {
                    newInfo = "You can't drop "+second_token;
                }
            }
            else if(first_token.compare("use") == 0){
                std::string itemToEquip = gameState.getItem(second_token);
                if(itemToEquip.compare("invalid") != 0){    // This just sets Equipped, it doesn't do anything with it
                    gameState.setEquipped(second_token);
                    fail_flag = 0;
                    newInfo = "You used "+second_token;
                } else {
                    newInfo = "You can't use "+second_token;
                }
            }
            else if(first_token.compare("search") == 0){
                int loc = n.searchableExists(second_token);
                newInfo = std::to_string(loc);
                if(loc != -1){
                    if(n.findables.size() > 0) {
                        n.objects.push_back(n.findables[loc]);
                    }
                    newInfo = n.searchText[loc];
                } else {
                    newInfo = "You can't search "+second_token;
                }
            }

        } else if (input.compare("options") == 0) {
            newInfo = "You can say 'Go', 'Take', 'Drop', 'Use', 'Search', 'Inventory', and 'Options'";
        } else if (input.compare("inventory") == 0) {
            std::set<std::string> items = gameState.getItems();
            if(!items.empty()) {
                for(std::string s: items)
                    newInfo = newInfo + s + " ";
            } else {
                newInfo = "You have nothing in your inventory";
            }
        }
    } while( input.compare("quit") != 0 );

  /*  Clean up after ourselves  */
  delwin(mainwin);
  endwin();
  refresh();

  return EXIT_SUCCESS;
}
