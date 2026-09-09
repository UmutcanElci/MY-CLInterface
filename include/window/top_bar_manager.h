#ifndef TOP_BAR_MANAGER_H
#define TOP_BAR_MANAGER_H
#include <ncurses.h>

typedef struct AppState AppState;

typedef struct AppTopWindow {
  WINDOW *top_bar_win;
  void (*draw)(struct AppState *app);
} AppTopWindow;

#define TOP_BAR_FULL_WINDOW_LABEL_THRESHOLD 60

void top_bar_win_init(AppState *app);

void draw_top_bar_win(AppState *app);

void top_bar_resize(AppState *app);

void top_bar_cleanup(AppState *app);
#endif // !TOP_BAR_MANAGER_H
