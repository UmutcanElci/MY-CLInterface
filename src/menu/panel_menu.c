#include "../../include/app.h"
#include "../../include/menu/helper.h"
#include <ncurses.h>
#include <panel.h>

void init_help_panel(AppState *app) {
  HelpConfig *cfg = &app->help_menu.config;

  cfg->height = 10;
  cfg->width = 45;
  cfg->y = (LINES - cfg->height) / 2;
  cfg->x = (COLS - cfg->width) / 2;
  if (cfg->y < 0)
    cfg->y = 0;
  if (cfg->x < 0)
    cfg->x = 0;

  app->help_menu.help_win = newwin(cfg->height, cfg->width, cfg->y, cfg->x);
  app->help_menu.help_panel = new_panel(app->help_menu.help_win);
  hide_panel(app->help_menu.help_panel);

  app->help_menu.config.is_active = 0;
}

void draw_help_window(AppState *app) {
  HelpConfig *cfg = &app->help_menu.config;
  WINDOW *win = app->help_menu.help_win;

  werase(win);

  if (LINES < cfg->height || COLS < cfg->width) {
    wattron(win, A_BOLD);
    mvwprintw(win, 1, 1, "Terminal too small!");
    wattroff(win, A_BOLD);
  } else {
    box(win, 0, 0);

    wattron(win, A_BOLD);
    mvwprintw(win, 1, (cfg->width - 17) / 2, "=== SHORTCUTS ===");
    wattroff(win, A_BOLD);

    mvwprintw(win, 4, 4, "[?]     : Toggle this help panel");
    mvwprintw(win, 5, 4, "[m]     : Open General Menu");
    mvwprintw(win, 6, 4, "[TAB]   : Cycle window focus");
    mvwprintw(win, 7, 4, "[:q]    : Quit");
  }

  update_panels();
  doupdate();
}

void show_help_panel(AppState *app) {
  HelpConfig *cfg = &app->help_menu.config;

  show_panel(app->help_menu.help_panel);
  top_panel(app->help_menu.help_panel);
  cfg->is_active = 1;

  draw_help_window(app);
}

void hide_help_panel(AppState *app) {
  HelpConfig *cfg = &app->help_menu.config;

  hide_panel(app->help_menu.help_panel);
  cfg->is_active = 0;
  update_panels();
  doupdate();
}

void resize_help_panel(AppState *app) {
  HelpConfig *cfg = &app->help_menu.config;
  int was_active = cfg->is_active;

  if (app->help_menu.help_panel) {
    del_panel(app->help_menu.help_panel);
  }
  if (app->help_menu.help_win) {
    delwin(app->help_menu.help_win);
  }

  init_help_panel(app);

  if (was_active) {
    show_help_panel(app);
  }
}
