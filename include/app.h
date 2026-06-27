#ifndef APP_H
#define APP_H
#include "../include/command/command_manager.h"
#include "../include/menu/helper.h"
#include "../include/menu/menu.h"
#include "../include/window/theme/theme.h"
#include "../include/window/top_bar_manager.h"
#include "../include/window/window_manager.h"
#include <ncurses.h>

typedef enum {
  NORMAL_MODE,
  COMMAND_MODE,
  WINDOW_MODE,
  HELP_MODE,
  MENU_MODE
} Mode;

typedef struct AppState {
  Mode current_mode;
  int is_running;

  AppTopWindow top_bar_win;
  AppWindow windows[4];
  AppMenu app_menu;
  HelpMenu help_menu;

  int win_index; // 0 is the main window - which is always
  int active_index;
  int selected_window;

  char command_buffer[128];

} AppState;

void app_init();
void app_run();

#endif // !APP_H
