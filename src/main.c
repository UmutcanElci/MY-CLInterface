#include "../include/app.h"
#include <ncurses.h>
#include <stdlib.h>

int main() {
  initscr();

  app_run();

  endwin();

  return EXIT_SUCCESS;
}
