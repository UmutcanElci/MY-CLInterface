#include "../../include/command/command_manager.h"
#include "../../include/app.h"
#include "../../include/helper/string_helper.h"
#include "../../include/window/theme/theme.h"
#include <string.h>

void command_manager(AppState *app) {
  remove_spaces(app->command_buffer);

  if (strncmp(app->command_buffer, "w1", 128) == 0 ||
      strncmp(app->command_buffer, "window1", 128) == 0) {
    for (int i = 0; i < 4; i++) {
      app->windows[i].config.focused = 0;
    }
    app->current_mode = WINDOW_MODE;
    app->active_index = 0;
    app->windows[0].config.focused = 1;
  } else if (strncmp(app->command_buffer, "w2", 128) == 0 ||
             strncmp(app->command_buffer, "window2", 128) == 0) {
    for (int i = 0; i < 4; i++) {
      app->windows[i].config.focused = 0;
    }
    app->current_mode = WINDOW_MODE;
    app->active_index = 1;
    app->windows[1].config.active = 1;
    app->windows[1].config.focused = 1;
    apply_layout(app);
  } else if (strncmp(app->command_buffer, "w3", 128) == 0 ||
             strncmp(app->command_buffer, "window3", 128) == 0) {
    for (int i = 0; i < 4; i++) {
      app->windows[i].config.focused = 0;
    }
    app->current_mode = WINDOW_MODE;
    app->active_index = 2;
    app->windows[2].config.active = 1;
    app->windows[2].config.focused = 1;
    apply_layout(app);
  } else if (strncmp(app->command_buffer, "w4", 128) == 0 ||
             strncmp(app->command_buffer, "window4", 128) == 0) {
    for (int i = 0; i < 4; i++) {
      app->windows[i].config.focused = 0;
    }
    app->current_mode = WINDOW_MODE;
    app->active_index = 3;
    app->windows[3].config.active = 1;
    app->windows[3].config.focused = 1;
    apply_layout(app);
  } else if (strncmp(app->command_buffer, "c2", 128) == 0 ||
             strncmp(app->command_buffer, "close2", 128) == 0) {
    app->windows[1].config.active = 0;

    if (app->active_index == 1) {
      app->active_index = 0;
    }
    apply_layout(app);
  } else if (strncmp(app->command_buffer, "c3", 128) == 0 ||
             strncmp(app->command_buffer, "close3", 128) == 0) {
    app->windows[2].config.active = 0;

    if (app->active_index == 2) {
      app->active_index = 0;
    }
    apply_layout(app);
  } else if (strncmp(app->command_buffer, "c4", 128) == 0 ||
             strncmp(app->command_buffer, "close4", 128) == 0) {
    app->windows[3].config.active = 0;

    if (app->active_index == 3) {
      app->active_index = 0;
    }
    apply_layout(app);
  } else if (strncmp(app->command_buffer, "q", 128) == 0 ||
             strncmp(app->command_buffer, "quit", 128) == 0 ||
             strncmp(app->command_buffer, "exit", 128) == 0) {
    app->is_running = 0;
  } else if (strncmp(app->command_buffer, "theme1", 128) == 0) {
    theme_manager(0);
  } else if (strncmp(app->command_buffer, "theme2", 128) == 0) {
    theme_manager(1);
  } else if (strncmp(app->command_buffer, "theme3", 128) == 0) {
    theme_manager(2);
  } else if (strncmp(app->command_buffer, "theme4", 128) == 0) {
    theme_manager(3);
  } else if (strncmp(app->command_buffer, "theme5", 128) == 0) {
    theme_manager(4);
  } else if (strncmp(app->command_buffer, "theme6", 128) == 0) {
    theme_manager(5);
  } else if (strncmp(app->command_buffer, "theme7", 128) == 0) {
    theme_manager(6);
  } else {
    // Maybe show error in a panel....
    app->current_mode = NORMAL_MODE;
  }

  app->command_buffer[0] = '\0';
}
