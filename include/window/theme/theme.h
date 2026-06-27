#ifndef THEME_H
#define THEME_H
#define PAIR_TOPBAR 1
#define PAIR_WINDOW 2
#define PAIR_DESKTOP 3
#define PAIR_WINDOW_BORDER 4 // will change with active inactive
#define PAIR_INACTIVE_WINDOW_BORDER
#define PAIR_ACTIVE_WINDOW_BORDER
#define PAIR_TEXT_PRIMARY
#define PAIR_TEXT_MUTED // Not sure

#define RGB_CONVERT(val) ((val) * 1000 / 255)

typedef enum { GRUVBOX, NORD, EVERFOREST, MYTH, WOODS, DREAMY, RACE_RED } Theme;

void theme_init();

void theme_manager(Theme select);

#endif // !THEME_H
