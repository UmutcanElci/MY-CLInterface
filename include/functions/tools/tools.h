#ifndef TOOLS_H
#define TOOLS_H
#include "../../../include/app.h"
#include <stddef.h>

typedef struct AppState AppState;

typedef struct {
  const char *name;
  const int tool_index;
  void (*action)(AppState *app, int selected_window);
  int is_active;
  void (*handle_input)(AppState *app, int ch, int selected_window);
} ToolItem;

void tool_template_run(AppState *app, int selected_window);
void draw_tool_template(AppState *app, int selected_window);

extern ToolItem tools[];

#define TOOLS_COUNT 1

#endif // !TOOLS_H
       // place holder
