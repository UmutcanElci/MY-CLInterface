#include "../../include/window/top_bar_manager.h"
#include "../../include/app.h"
#include <ncurses.h>

void top_bar_win_init(AppState *app) {
  app->top_bar_win.top_bar_win = newwin(3, COLS - 2, 1, 0);
}

void draw_top_bar_win(AppState *app) {
  init_pair(1, COLOR_BLACK, COLOR_WHITE); // Might add color manager...

  wbkgd(app->top_bar_win.top_bar_win, COLOR_PAIR(1) | ' ');
  box(app->top_bar_win.top_bar_win, 0, 0);

  if (app->current_mode == NORMAL_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "NORMAL MODE");
  } else if (app->current_mode == COMMAND_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "COMMAND MODE");
  } else if (app->current_mode == WINDOW_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "WINDOW MODE");
  }

  wrefresh(app->top_bar_win.top_bar_win);
}
