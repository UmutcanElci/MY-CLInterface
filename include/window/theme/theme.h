#ifndef THEME_H
#define THEME_H

#define PAIR_TOPBAR 1
#define PAIR_WINDOW 2
#define PAIR_DESKTOP 3
#define PAIR_WINDOW_BORDER 4 // generic window border
#define PAIR_INACTIVE_WINDOW_BORDER 6
#define PAIR_ACTIVE_WINDOW_BORDER 7
#define PAIR_TEXT_PRIMARY 8
#define PAIR_TEXT_MUTED 9

#define RGB_CONVERT(val) ((val) * 1000 / 255)

typedef enum {
  GRUVBOX,
  NORD,
  EVERFOREST,
  MYTH,
  WOODS,
  DREAMY,
  RACE_RED,
  THEME_COUNT
} Theme;

void theme_init();

void theme_manager(Theme select);

const char *theme_name(Theme select);

Theme theme_current(void);

#endif // !THEME_H
