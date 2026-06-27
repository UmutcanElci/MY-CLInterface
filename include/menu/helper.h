#ifndef HELPER_H
#define HELPER_H
#include <ncurses.h>
#include <panel.h>

typedef struct AppState AppState;

typedef struct {
  int x, y;
  int width, height;
  int is_active;
} HelpConfig;

typedef struct {
  HelpConfig config;
  WINDOW *help_win;
  PANEL *help_panel;
} HelpMenu;

void init_help_panel(AppState *app);
void draw_help_window(AppState *app);
void show_help_panel(AppState *app);
void hide_help_panel(AppState *app);
void resize_help_panel(AppState *app);

#endif
