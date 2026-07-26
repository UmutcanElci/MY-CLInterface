#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <ncurses.h>
typedef struct AppState AppState;

typedef struct {
  int x, y;
  int width, height;
  int active;
  int occupied;
  int focused;
  int paused;
} WindowConfig;

typedef struct AppWindow {
  WindowConfig config;
  WINDOW *app_win;

  void (*handle_input)(struct AppState *app, int ch);
  void (*draw)(struct AppState *app, int win_index);
} AppWindow;

void first_window_init(AppState *app); // Main window - always live
void second_window_init(AppState *app);
void third_window_init(AppState *app);
void fourth_window_init(AppState *app);

void draw_window(AppState *app, int win_index);

void calculate_layout(AppState *app);
void apply_layout(AppState *app);

#endif // !WINDOW_MANAGER_H
