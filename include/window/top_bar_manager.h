#ifndef TOP_BAR_MANAGER_H
#define TOP_BAR_MANAGER_H
#include <ncurses.h>

typedef struct AppState AppState;

typedef struct AppTopWindow {
  WINDOW *top_bar_win;
} AppTopWindow;

void top_bar_win_init(AppState *app);
void draw_top_bar_win(AppState *app);

#endif // !TOP_BAR_MANAGER_H
