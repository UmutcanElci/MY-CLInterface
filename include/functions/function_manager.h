#ifndef FUNCTION_MANAGER_H
#define FUNCTION_MANAGER_H

typedef struct AppState AppState;

typedef enum { MENU_MAIN, MENU_GAMES, MENU_TOOLS } MenuType;

typedef struct FunctionItem {
  const char *name;
  MenuType sub_menu;

  void (*action)(AppState *app, int selected_window);
  void (*handle_input)(AppState *app, int ch, int selected_window);
} FunctionItem;

const FunctionItem *get_main_menu(int *count);
const FunctionItem *get_games_menu(int *count);
const FunctionItem *get_tools_menu(int *count);

const FunctionItem *get_menu_items(MenuType, int *count);

void set_active_menu(MenuType menu);
void get_active_menu(void);

#endif // !FUNCTION_MANAGER_H
