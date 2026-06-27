#ifndef GAMES_H
#define GAMES_H
#include "../../../include/app.h"
#include <stddef.h>

typedef struct AppState AppState;

typedef struct {
  const char *name;
  const int game_index;
  void (*action)(AppState *app, int selected_window);
  int is_active;
  void (*handle_input)(AppState *app, int ch, int selected_window);
} GameItem;

void game_template_run(AppState *app, int selected_window);
void draw_game_template(AppState *app, int selected_window);

static GameItem games[] = {{"Template Game", 0, game_template_run}};

#define GAMES_COUNT (sizeof(games) / sizeof(games[0]))

#endif // !GAMES_H
       // place holder
