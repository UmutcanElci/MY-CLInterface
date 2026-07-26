#include "../../include/app.h"
#include "../../include/functions/function_manager.h"
#include "../../include/functions/games/games.h" // Games and tools can have own menu...not sure yet
#include "../../include/functions/tools/tools.h"
#include "../../include/menu/menu.h"
#include <ncurses.h>
#include <panel.h>
#include <string.h>

void init_app_menu(AppState *app) {
  MenuConfig *cfg = &app->app_menu.config;

  cfg->height = 15;
  cfg->width = 45;

  cfg->y = (LINES - cfg->height) / 2;
  cfg->x = (COLS - cfg->width) / 2;
  if (cfg->y < 0)
    cfg->y = 0;
  if (cfg->x < 0)
    cfg->x = 0;

  app->app_menu.menu_window = newwin(cfg->height, cfg->width, cfg->y, cfg->x);
  app->app_menu.menu_panel = new_panel(app->app_menu.menu_window);

  hide_panel(app->app_menu.menu_panel);
  cfg->is_active = 0;

  app->app_menu.phase = SELECT_ITEM;
  app->app_menu.pending_selection = 0;
}

void draw_app_menu(AppState *app) {
  MenuConfig *cfg = &app->app_menu.config;
  WINDOW *win = app->app_menu.menu_window;

  werase(win);

  MenuType active = get_active_menu();
  int count = 0;
  const FunctionItem *items = NULL;

  if (LINES < cfg->height || COLS < cfg->width) {
    wattron(win, A_BOLD);
    mvwprintw(win, 1, 1, "Terminal too small!");
    wattroff(win, A_BOLD);
  } else {
    if (active == MENU_MAIN) {
      items = get_main_menu(&count);
    } else if (active == MENU_GAMES) {
      items = get_games_menu(&count);
    } else if (active == MENU_TOOLS) {
      items = get_tools_menu(&count);
    }

    const char *title = "=== MAIN MENU ===";
    if (active == MENU_GAMES)
      title = "=== GAMES ===";
    else if (active == MENU_TOOLS)
      title = "=== TOOLS ===";

    box(win, 0, 0);
    wattron(win, A_BOLD);
    mvwprintw(win, 2, (cfg->width - strlen(title)) / 2, "%s", title);
    wattroff(win, A_BOLD);

    if (app->app_menu.phase == SELECT_WINDOW) {
      // window selection after a game or tool selected....
      const char *title = "=== SELECT WINDOW ===";
      box(win, 0, 0);
      wattron(win, A_BOLD);
      mvwprintw(win, 2, (cfg->width - strlen(title)) / 2, "%s", title);
      wattroff(win, A_BOLD);

      int start_y = 5;
      for (int i = 0; i < 4; i++) {
        int is_selected = (i == app->app_menu.list.selected_index);
        int is_occupied = app->windows[i].config.occupied;
        int is_active = app->windows[i].config.active;

        char label[32];
        if (!is_active) {
          snprintf(label, sizeof(label), "[w%d: inactive]", i + 1);
        } else if (is_occupied) {
          snprintf(label, sizeof(label), "[w%d: occupied]", i + 1);
        } else {
          snprintf(label, sizeof(label), "[w%d: free]", i + 1);
        }

        if (is_selected) {
          wattron(win, A_REVERSE);
          mvwprintw(win, start_y + (i), 4, "%s", label);
          wattroff(win, A_REVERSE);
        } else {
          if (is_occupied) {
            wattron(win, A_DIM);
            mvwprintw(win, start_y + (i), 4, "%s", label);
            wattroff(win, A_DIM);
          } else {
            mvwprintw(win, start_y + (i), 4, "%s", label);
          }
        }
      }

      mvwprintw(win, cfg->height - 2, 4, "[ESC] Back");
      update_panels();
      doupdate();
      return;
    }
    for (int i = 0; i < count; i++) {
      if (i == app->app_menu.list.selected_index) {
        wattron(win, A_REVERSE);
        mvwprintw(win, 5 + i, 4, "%s", items[i].name);
        wattroff(win, A_REVERSE);
      } else {
        mvwprintw(win, 5 + i, 4, "%s", items[i].name);
      }
    }

    if (active != MENU_MAIN) {
      mvwprintw(win, cfg->height - 2, 4, "[ESC] Back");
    } else {
      mvwprintw(win, cfg->height - 2, 4, "[ESC] Close");
    }
  }
  update_panels();
  doupdate();
}

void show_app_menu(AppState *app) {
  app->app_menu.phase = SELECT_ITEM;
  app->app_menu.pending_selection = 0;

  MenuConfig *cfg = &app->app_menu.config;

  show_panel(app->app_menu.menu_panel);
  top_panel(app->app_menu.menu_panel);
  cfg->is_active = 1;

  draw_app_menu(app);
}

void hide_app_menu(AppState *app) {
  MenuConfig *cfg = &app->app_menu.config;

  hide_panel(app->app_menu.menu_panel);
  cfg->is_active = 0;

  set_active_menu(MENU_MAIN);
  app->app_menu.list.selected_index = 0;
  app->app_menu.phase = SELECT_ITEM;

  update_panels();
  doupdate();
}

void resize_app_menu(AppState *app) {
  MenuConfig *cfg = &app->app_menu.config;
  int was_active = cfg->is_active;

  if (app->app_menu.menu_panel) {
    del_panel(app->app_menu.menu_panel);
  }
  if (app->app_menu.menu_window) {
    delwin(app->app_menu.menu_window);
  }

  init_app_menu(app);

  if (was_active) {
    show_app_menu(app);
  }
}

void menu_handle_input(AppState *app, int ch) {
  MenuType active = get_active_menu();
  int count;
  const FunctionItem *items = get_menu_items(active, &count);

  int actual_count = count;
  if (app->app_menu.phase == SELECT_WINDOW) {
    actual_count = 4;
  }

  if (ch == KEY_UP) {
    app->app_menu.list.selected_index--;
    if (app->app_menu.list.selected_index < 0)
      app->app_menu.list.selected_index = actual_count - 1;
  } else if (ch == KEY_DOWN) {
    app->app_menu.list.selected_index++;
    if (app->app_menu.list.selected_index >= actual_count)
      app->app_menu.list.selected_index = 0;
  } else if (ch == '\n' || ch == KEY_ENTER) {

    if (app->app_menu.phase == SELECT_WINDOW) {
      int selected_window = app->app_menu.list.selected_index;

      if (!app->windows[selected_window].config.active) {
        app->windows[selected_window].config.active = 1;
        apply_layout(app);
      }

      if (active == MENU_GAMES) {
        games[app->app_menu.pending_selection].action(app, selected_window);
      } else if (active == MENU_TOOLS) {
        tools[app->app_menu.pending_selection].action(app, selected_window);
      }

      hide_app_menu(app);
      app->current_mode = WINDOW_MODE;
      app->active_index = selected_window;
      app->top_bar_win.draw(app);
      apply_layout(app);
      return;
    }
    FunctionItem selected = items[app->app_menu.list.selected_index];
    if (active == MENU_MAIN) {
      if (selected.sub_menu == MENU_GAMES) {
        set_active_menu(MENU_GAMES);
        app->app_menu.list.selected_index = 0;
      } else if (selected.sub_menu == MENU_TOOLS) {
        set_active_menu(MENU_TOOLS);
        app->app_menu.list.selected_index = 0;
      } else if (strcmp(selected.name, "Exit") == 0) {
        app->is_running = 0;
      }
    } else {
      if (selected.action != NULL) {
        app->app_menu.pending_selection = app->app_menu.list.selected_index;
        app->app_menu.phase = SELECT_WINDOW;
        app->app_menu.list.selected_index = 0;
      }
    }
  } else if (ch == 27) {
    if (app->app_menu.phase == SELECT_WINDOW) {
      app->app_menu.phase = SELECT_ITEM;
      app->app_menu.list.selected_index = 0;
    } else if (active != MENU_MAIN) {
      set_active_menu(MENU_MAIN);
      app->app_menu.list.selected_index = 0;
    } else {
      hide_app_menu(app);
      app->current_mode = NORMAL_MODE;
      app->top_bar_win.draw(app);
      apply_layout(app);
    }
  }

  draw_app_menu(app);
}
