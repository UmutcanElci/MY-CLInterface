#include "../../../include/functions/games/games.h"
#include <ncurses.h>

GameItem games[] = {{"Template Game", 0, game_template_run, 0, NULL}};

void game_template_handle_input(AppState *app, int ch) {
  int win_idx = app->active_index;
  WINDOW *win = app->windows[win_idx].app_win;
  int y, x, h, w;
  getmaxyx(win, h, w);
  getyx(win, y, x);

  // Template input logic: just echo characters at the current cursor position
  if (ch >= 32 && ch <= 126) {
    if (x < w - 2) {
      waddch(win, ch);
    }
  } else if (ch == '\n' || ch == KEY_ENTER) {
    if (y < h - 3) {
      wmove(win, y + 1, 2);
    }
  } else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
    if (x > 2) {
      wmove(win, y, x - 1);
      wdelch(win);
    } else if (y > 2) {
      wmove(win, y - 1, w - 3); // Very basic wrap-back
    }
  }
  wrefresh(win);
}

void game_template_run(AppState *app, int selected_win) {
  app->windows[selected_win].config.occupied = 1;
  app->windows[selected_win].draw = draw_game_template;
  app->windows[selected_win].handle_input = game_template_handle_input;

  werase(app->windows[selected_win].app_win);
  wmove(app->windows[selected_win].app_win, 2, 2);
  wrefresh(app->windows[selected_win].app_win);
}

void draw_game_template(AppState *app, int selected_window) {
  WINDOW *win = app->windows[selected_window].app_win;
  int h, w, cur_y, cur_x;
  getmaxyx(win, h, w);
  getyx(win, cur_y, cur_x);

  // Enforce padding if cursor is at (0,0) or inside border area
  if (cur_y < 2)
    cur_y = 2;
  if (cur_x < 2)
    cur_x = 2;

  int border_pair = (selected_window == app->active_index)
                        ? PAIR_ACTIVE_WINDOW_BORDER
                        : PAIR_INACTIVE_WINDOW_BORDER;

  wbkgd(win, COLOR_PAIR(PAIR_WINDOW));

  wattron(win, COLOR_PAIR(border_pair));
  box(win, 0, 0);

  mvwprintw(win, 0, 2, "[ Game Template ]");

  const char *status =
      app->windows[selected_window].config.paused ? " PAUSED " : " ACTIVE ";
  mvwprintw(win, h - 1, w - 12, "[%s]", status);
  wattroff(win, COLOR_PAIR(border_pair));

  // Restore cursor for input at protected coordinates
  wmove(win, cur_y, cur_x);
  wrefresh(win);
}
