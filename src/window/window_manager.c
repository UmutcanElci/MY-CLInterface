#include "../../include/window/window_manager.h"
#include "../../include/app.h"
#include <ncurses.h>
#include <sys/types.h>

/*
 * First window is the main window
 * that created when the program runs
 * the other windows can be created and deleted
 * M  W1
 * W2 W3
 * M never changes
 *
 * M  |
 * -- |
 */

void calculate_layout(AppState *app) {
  int start_y = 5;
  int start_x = 2;

  int normal_height = LINES - start_y;
  int normal_widht = COLS - (start_x * 2);

  int half_height = normal_height / 2;
  int half_width = normal_widht / 2;

  // First window also MAIN window
  app->windows[0].config.y = start_y;
  app->windows[0].config.x = start_x;

  app->windows[0].config.width = normal_widht;

  // Second and Fourth window check
  int right_column_is_active =
      (app->windows[1].config.active || app->windows[3].config.active);

  // Third Window - bottom of first
  if (app->windows[2].config.active) {
    app->windows[0].config.height = half_height;

    app->windows[2].config.y = half_height + start_y;
    app->windows[2].config.x = start_x;

    app->windows[2].config.height = normal_height - half_height;
    app->windows[2].config.width = half_width;

    if (!right_column_is_active) {
      app->windows[2].config.width = normal_widht;
    }
  } else {
    app->windows[0].config.height = normal_height;
  }

  if (right_column_is_active) {
    if (app->windows[1].config.active && app->windows[3].config.active) {
      app->windows[0].config.width = half_width;

      app->windows[1].config.y = start_y;
      app->windows[1].config.x = start_x + half_width;

      app->windows[1].config.height = half_height;
      app->windows[1].config.width = normal_widht - half_width;

      app->windows[3].config.y = half_height + start_y;
      app->windows[3].config.x = start_x + half_width;

      app->windows[3].config.height = normal_height - half_height;
      app->windows[3].config.width = normal_widht - half_width;
    } else if (app->windows[1].config.active) {
      app->windows[0].config.width = half_width;

      app->windows[1].config.y = start_y;
      app->windows[1].config.x = start_x + half_width;

      app->windows[1].config.height = normal_height;
      app->windows[1].config.width = normal_widht - half_width;
    } else if (app->windows[3].config.active) {
      app->windows[0].config.width = half_width;

      app->windows[3].config.y = start_y;
      app->windows[3].config.x = start_x + half_width;

      app->windows[3].config.width = normal_widht - half_width;
      app->windows[3].config.height = normal_height;
    }
  }
}
void apply_layout(AppState *app) {
  calculate_layout(app);
  for (int i = 0; i < 4; i++) {
    if (app->windows[i].config.active == 1) {
      WindowConfig *cfg = &app->windows[i].config;

      if (app->windows[i].app_win == NULL) {
        app->windows[i].app_win =
            newwin(cfg->height, cfg->width, cfg->y, cfg->x);
      } else {
        refresh();
        werase(app->windows[i].app_win);
        wresize(app->windows[i].app_win, cfg->height, cfg->width);
        mvwin(app->windows[i].app_win, cfg->y, cfg->x);
        wrefresh(app->windows[i].app_win);
      }
      // wbkgd(app->windows[i].app_win, COLOR_PAIR(PAIR_WINDOW));

      if (app->windows[i].draw != NULL) {
        app->windows[i].draw(app, i);
      }
    } else {
      if (app->windows[i].app_win != NULL) {
        delwin(app->windows[i].app_win);
        app->windows[i].app_win = NULL;
      }
    }
  }
}

void first_window_init(AppState *app) {
  app->windows[0].draw = draw_window;
  app->windows[0].config.occupied = 0;
}

void second_window_init(AppState *app) {
  app->windows[1].draw = draw_window;
  app->windows[1].config.occupied = 0;
}

void third_window_init(AppState *app) {
  app->windows[2].draw = draw_window;
  app->windows[2].config.occupied = 0;
}
void fourth_window_init(AppState *app) {
  app->windows[3].draw = draw_window;
  app->windows[3].config.occupied = 0;
}

void draw_window(AppState *app, int win_index) {
  WINDOW *win = app->windows[win_index].app_win;
  int border_pair = (win_index == app->active_index)
                        ? PAIR_ACTIVE_WINDOW_BORDER
                        : PAIR_INACTIVE_WINDOW_BORDER;

  wbkgd(win, COLOR_PAIR(PAIR_WINDOW));
  werase(win);

  wattron(win, COLOR_PAIR(border_pair));
  box(win, 0, 0);
  wattroff(win, COLOR_PAIR(border_pair));

  wrefresh(win);
}
