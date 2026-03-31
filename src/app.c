#include "../include/app.h"
#include "../include/window/top_bar_manager.h"
#include "../include/window/window_manager.h"
#include <locale.h>
#include <ncurses.h>

void app_init() {
  noecho();
  raw();
  cbreak();
  curs_set(0);
  setlocale(LC_ALL, "");
  start_color();
}

void app_run() {}
