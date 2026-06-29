#include "../../include/functions/function_manager.h"
#include "../../include/functions/games/games.h"
#include "../../include/functions/tools/tools.h"

static MenuType active_menu = MENU_MAIN;

const FunctionItem *get_main_menu(int *count) {
  static FunctionItem items[] = {{"Games", MENU_GAMES, NULL},
                                 {"Tools", MENU_TOOLS, NULL},
                                 {"Exit", MENU_MAIN, NULL}};
  *count = 3;
  return items;
}

const FunctionItem *get_games_menu(int *count) {
  static FunctionItem items[GAMES_COUNT];
  for (int i = 0; i < GAMES_COUNT; i++) {
    items[i].name = games[i].name;
    items[i].sub_menu = MENU_MAIN;
    items[i].action = games[i].action;
  }
  *count = GAMES_COUNT;
  return items;
}

const FunctionItem *get_tools_menu(int *count) {
  static FunctionItem items[TOOLS_COUNT];
  for (int i = 0; i < TOOLS_COUNT; i++) {
    items[i].name = tools[i].name;
    items[i].sub_menu = MENU_MAIN;
    items[i].action = tools[i].action;
  }
  *count = TOOLS_COUNT;
  return items;
}
const FunctionItem *get_menu_items(MenuType type, int *count) {
  if (type == MENU_MAIN)
    return get_main_menu(count);
  if (type == MENU_GAMES)
    return get_games_menu(count);
  if (type == MENU_TOOLS)
    return get_tools_menu(count);
  return NULL;
}

void set_active_menu(MenuType menu) { active_menu = menu; }

MenuType get_active_menu() { return active_menu; }
