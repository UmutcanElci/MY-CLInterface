#ifndef MENU_H
#define MENU_H
#include <ncurses.h>
#include <panel.h>

typedef struct AppState AppState;

typedef enum { SELECT_ITEM, SELECT_WINDOW } MenuPhase;

typedef struct MenuList {
  char title[32];
  int item_count;
  int selected_index;
} MenuList;

typedef struct MenuConfig {
  int x, y;
  int width, height;
  int is_active;
} MenuConfig;

typedef struct AppMenu {
  MenuConfig config;

  WINDOW *menu_window;
  PANEL *menu_panel;
  int phase;
  int pending_selection;
} AppMenu;

void init_app_menu(AppState *app);
void draw_app_menu(AppState *app);
void show_app_menu(AppState *app);
void hide_app_menu(AppState *app);
void resize_app_menu(AppState *app);
void menu_handle_input(AppState *app, int ch);

#endif // !MENU_H
