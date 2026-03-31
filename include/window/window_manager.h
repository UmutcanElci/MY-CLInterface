#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <ncurses.h>
typedef struct AppState AppState;

typedef struct AppWindow {
  WINDOW *app_win;

  void (*handle_input)(struct AppState *app, int ch);
  void (*draw)(struct AppState *app);
} AppWindow;

#endif // !WINDOW_MANAGER_H
