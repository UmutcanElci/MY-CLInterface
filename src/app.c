#include "../include/app.h"
#include "../include/window/theme/theme.h"
#include "../include/window/top_bar_manager.h"
#include "../include/window/window_manager.h"
#include <locale.h>
#include <ncurses.h>
#include <panel.h>
#include <string.h>

void app_init() {
  noecho();
  raw();
  keypad(stdscr, TRUE);
  curs_set(0);
  setlocale(LC_ALL, "");
}

void app_run() {
  app_init();
  theme_init();

  AppState app = {0};
  int ch;

  init_app_menu(&app);
  init_help_panel(&app);
  bkgd(COLOR_PAIR(PAIR_DESKTOP));

  top_bar_win_init(&app);

  app.command_buffer[0] = '\0';

  first_window_init(&app);
  second_window_init(&app);
  third_window_init(&app);
  fourth_window_init(&app);

  set_escdelay(25);

  timeout(5);

  app.is_running = 1;

  refresh();

  app.top_bar_win.draw(&app);

  app.windows[0].config.active = 1;
  app.windows[0].config.occupied = 0;

  app.top_bar_win.draw(&app);
  apply_layout(&app);

  while (app.is_running) {
    for (int i = 0; i < 4; i++) {
      if (app.windows[i].config.active) {
        app.windows[i].config.paused =
            (app.current_mode != WINDOW_MODE) || (app.active_index != i);
      }
    }
    ch = getch();

    if (ch == ERR) {
      for (int i = 0; i < 4; i++) {
        if (app.windows[i].config.active && app.windows[i].config.occupied) {
          if (app.current_mode == MENU_MODE || app.current_mode == HELP_MODE) {
            continue;
          }
          if (app.windows[i].draw != NULL) {
            app.windows[i].draw(&app, i);
          }
        }
      }

      continue;
    }

    if (ch == KEY_RESIZE) {
      top_bar_resize(&app);

      resize_app_menu(&app);
      resize_help_panel(&app);

      app.top_bar_win.draw(&app);

      apply_layout(&app);

      update_panels();
      doupdate();
      continue;
    }

    if (app.current_mode == MENU_MODE) {
      menu_handle_input(&app, ch);
      continue;
    } else if (app.current_mode == HELP_MODE) {
      hide_help_panel(&app);
      app.current_mode = NORMAL_MODE;
      app.top_bar_win.draw(&app);
      apply_layout(&app);
      continue;
    } else if (app.current_mode == NORMAL_MODE) {
      if (ch == 58) {
        app.current_mode = COMMAND_MODE;
        app.top_bar_win.draw(&app);
        continue;
      } else if (ch == '?') {
        app.current_mode = HELP_MODE;
        show_help_panel(&app);
        continue;
      } else if (ch == 'm') {
        app.current_mode = MENU_MODE;
        app.app_menu.list.selected_index = 0;
        show_app_menu(&app);
        continue;
      }
    } else if (app.current_mode == COMMAND_MODE) {
      if (ch == 27) {
        app.current_mode = NORMAL_MODE;
        app.command_buffer[0] = '\0';
        app.top_bar_win.draw(&app);
        continue;
      } else if (ch == '\n' || ch == KEY_ENTER) {
        command_manager(&app);
      } else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
        int len = strnlen(app.command_buffer, 128);
        if (len > 0) {
          app.command_buffer[len - 1] = '\0';
        }
      } else {
        int len = strnlen(app.command_buffer, 128);
        if (len < sizeof(app.command_buffer) - 1) {
          app.command_buffer[len] = (char)ch;
          app.command_buffer[len + 1] = '\0';
        }
      }
      app.top_bar_win.draw(&app);
    } else if (app.current_mode == WINDOW_MODE) {
      if (ch == 27) {
        app.current_mode = NORMAL_MODE;
        app.active_index = 0;
        app.top_bar_win.draw(&app);
      } else {
        if (app.windows[app.active_index].handle_input != NULL) {
          app.windows[app.active_index].handle_input(&app, ch);
        }
      }
    }

    if (app.is_running == 0) {
      break;
    }
  }
}
