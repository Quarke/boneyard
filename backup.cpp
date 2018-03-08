
std::string combat_suggest(std::string input) {
  std::vector<string> rc = {};

  if(std::string("equip").find(input) != std::string::npos){
    rc.push_back("equip");
  }
  if(std::string("attack").find(input) != std::string::npos){
    rc.push_back("attack");
  }
  if(std::string("run").find(input) != std::string::npos){
    rc.push_back("run");
  }

  std::ostringstream oss;

  if ( !rc.empty() ) {
    // Convert all but the last element to avoid a trailing ","
    std::copy(rc.begin(), rc.end() - 1, std::ostream_iterator<string>(oss, ", ") );

    // Now add the last element with no delimiter
    oss << rc.back();
  }

  return oss.str();
}

std::string combat_input() {
  char c = 0;
  std::string input = "";
  int x, y;
  std::string rc = "";
  while (c != '\n') {
      c = static_cast<char>(getch());
      switch (c)
      {
          case '\t':
              rc = combat_suggest(input);
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

  return input;
}

//needs enemy
void combat( GameState gameState) {
  //Enemy enemy = getEnemy();
  std::string e_name = "zombie";
  int e_hp = 7;
  int e_dmg = 2;

  clear();

  mvprintw_center(LINES/2, COLS/2, "You encountered a monster");
  refresh();
  sleep(3);

  bool combat = true;

  while(combat) {
    clear();

    // echo previous input to user
    mvprintw(1, COLS/2, "%d\n", e_hp);
    mvprintw(2, COLS/2, e_name.c_str() );
    mvprintw(3, COLS/2, "%d\n", e_dmg);

    mvprintw(LINES / 2 + 1, 5, "%d\n", gameState.getHp() );
    mvprintw(LINES / 2 + 2, 5, gameState.getName().c_str() );

    int damage = 0;
    //reference the weapons dict and if it has it, set damage to its value

    mvprintw(LINES / 2 + 3, 5, "%d\n", damage );

    mvprintw_center(LINES / 2 + 4, 10, "options for murder");

    move(LINES / 2 + 1, COLS / 2 - 18);
    clrtoeol();

    std::string input = combat_input();

    if(input.compare("run") == 0) {
      combat = false;
      //you are leaving combat
      clear();
      mvprintw_center(LINES / 2 + 4, COLS/2, "run condition");
      refresh();
      sleep(1);
    }
    else if(input.compare("attack") == 0) {
      e_hp -= damage;

      if(e_hp <= 0) {
        combat = false;
      }

      //you are leaving combat
      clear();
      mvprintw_center(LINES / 2 + 4, COLS/2, "attack condition");
      refresh();
      sleep(1);
    }
    else if(input.compare("equip") == 0) {
      //you are leaving combat
      clear();
      mvprintw_center(LINES / 2 + 4, COLS/2, "equip condition");
      refresh();
      sleep(1);
    }
    else {
      clear();
      mvprintw_center(LINES / 2 + 4, COLS/2, "illegal command");
      refresh();
      sleep(1);
    }

    //sleep(6);
  }
}
