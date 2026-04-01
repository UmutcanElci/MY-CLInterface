#include "../../include/command/command_manager.h"
#include "../../include/app.h"
#include "../../include/helper/string_helper.h"
#include <string.h>

void command_manager(AppState *app) {
  remove_spaces(app->command_buffer);

  if (strncmp(app->command_buffer, "w1", 128) == 0 ||
      strncmp(app->command_buffer, "window1", 128) == 0) {
    app->current_mode = WINDOW_MODE;
    app->active_index = 0;
  } else if (strncmp(app->command_buffer, "w2", 128) == 0 ||
             strncmp(app->command_buffer, "window2", 128) == 0) {
    app->current_mode = WINDOW_MODE;
    app->active_index = 1;
  } else if (strncmp(app->command_buffer, "w3", 128) == 0 ||
             strncmp(app->command_buffer, "window3", 128) == 0) {
    app->current_mode = WINDOW_MODE;
    app->active_index = 2;
  } else if (strncmp(app->command_buffer, "w4", 128) == 0 ||
             strncmp(app->command_buffer, "window4", 128) == 0) {
    app->current_mode = WINDOW_MODE;
    app->active_index = 3;
  } else if (strncmp(app->command_buffer, "q", 128) == 0 ||
             strncmp(app->command_buffer, "quit", 128) == 0 ||
             strncmp(app->command_buffer, "exit", 128) == 0) {
    app->is_running = 0;
  } else {
    // Wrong
  }

  app->command_buffer[0] = '\0';
}
