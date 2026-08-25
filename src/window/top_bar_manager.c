#include "../../include/window/top_bar_manager.h"
#include "../../include/app.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

static void draw_top_bar_left(AppState *app) {
  if (app->current_mode == NORMAL_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ NORMAL ]");
  } else if (app->current_mode == COMMAND_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ COMMAND ]");
  } else if (app->current_mode == WINDOW_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ WINDOW ]");
  } else if (app->current_mode == MENU_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ MENU ]");
  } else if (app->current_mode == HELP_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ HELP ]");
  }
}

static void draw_top_bar_center(AppState *app) {
  if (app->top_bar_win.top_bar_win == NULL) {
    return;
  }

  if (app->current_mode == COMMAND_MODE) {
    int cmd_len = strlen(app->command_buffer);

    int center_x = (COLS / 2) - ((cmd_len + 1) / 2);

    if (center_x < 15) {
      center_x = 15;
    }

    mvwprintw(app->top_bar_win.top_bar_win, 1, center_x, ":%s",
              app->command_buffer);
  }
}
static void draw_top_bar_right(AppState *app) {
  char status_text[32];
  snprintf(status_text, sizeof(status_text), "[ %s ]",
           theme_name(theme_current()));

  int status_text_len = strlen(status_text);

  int win_width = getmaxx(app->top_bar_win.top_bar_win);
  int right_x = win_width - status_text_len - 2;

  if (right_x < 2)
    right_x = 2;

  mvwprintw(app->top_bar_win.top_bar_win, 1, right_x, "%s", status_text);
}

void draw_top_bar_win(AppState *app) {
  WINDOW *top_bar_win = app->top_bar_win.top_bar_win;

  wbkgd(top_bar_win, COLOR_PAIR(PAIR_TOPBAR));
  werase(top_bar_win);

  wattron(top_bar_win, COLOR_PAIR(PAIR_TOPBAR));
  box(top_bar_win, 0, 0);
  wattroff(top_bar_win, COLOR_PAIR(PAIR_TOPBAR));

  draw_top_bar_left(app);
  draw_top_bar_center(app);
  draw_top_bar_right(app);

  wrefresh(top_bar_win);
}
void top_bar_win_init(AppState *app) {
  app->top_bar_win = (AppTopWindow){0};
  app->top_bar_win.top_bar_win = newwin(3, COLS - 4, 1, 2);

  app->top_bar_win.draw = draw_top_bar_win;
}

void top_bar_resize(AppState *app) {
  wresize(app->top_bar_win.top_bar_win, 3, COLS - 4);
  mvwin(app->top_bar_win.top_bar_win, 1, 2);

  app->top_bar_win.draw(app);
}
