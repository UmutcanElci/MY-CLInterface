#include "../../include/window/top_bar_manager.h"
#include "../../include/app.h"
#include <ncurses.h>
#include <string.h>

static void draw_top_bar_left(AppState *app) {
  if (app->current_mode == NORMAL_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ NORMAL ]");
  } else if (app->current_mode == COMMAND_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ COMMAND ]");
  } else if (app->current_mode == WINDOW_MODE) {
    mvwprintw(app->top_bar_win.top_bar_win, 1, 2, "[ WINDOW ]");
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
  char *status_text = "|status bar|";

  int status_text_len = strlen(status_text);

  int right_x = COLS - status_text_len - 2;

  mvwprintw(app->top_bar_win.top_bar_win, 1, right_x, "%s", status_text);
}

void draw_top_bar_win(AppState *app) {
  // init_pair(1, COLOR_BLACK, COLOR_WHITE); // Might add color manager...

  // wbkgd(app->top_bar_win.top_bar_win, COLOR_PAIR(1) | ' ');
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
void top_bar_win_init(AppState *app) {
  app->top_bar_win = (AppTopWindow){0};
  app->top_bar_win.top_bar_win = newwin(3, COLS - 2, 1, 0);

  app->top_bar_win.draw = draw_top_bar_win;
}

void top_bar_resize(AppState *app) {
  wresize(app->top_bar_win.top_bar_win, 3, COLS);
  mvwin(app->top_bar_win.top_bar_win, 0, 0);

  app->top_bar_win.draw(app);
}
