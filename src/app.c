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

void app_run() {
  app_init();

  AppState app = {0};

  int ch;

  top_bar_win_init(&app);

  set_escdelay(25);

  timeout(5);

  app.is_running = 1;

  while (app.is_running) {
    draw_top_bar_win(&app);

    ch = getch();

    if (ch == ERR) {
      continue;
    }
    if (app.current_mode == NORMAL_MODE) {
      if (ch == 58) {
        app.current_mode = COMMAND_MODE;
        continue;
      }
    } else if (app.current_mode == COMMAND_MODE) {
      if (ch == 27) {
        app.current_mode = NORMAL_MODE;
        refresh();
        continue;
      }
    }

    if (ch == 27) {
      app.current_mode = NORMAL_MODE;
      refresh();
      continue;
    }

    if (ch == 'q') {
      break;
    }
  }
}
