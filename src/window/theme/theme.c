#include "../../../include/window/theme/theme.h"
#include <ncurses.h>

static Theme current_theme = GRUVBOX;

/*
 * Each theme is described by 5 colors (RGB 0-255):
 *   [0] accent      -> used for active borders / highlights
 *   [1] background  -> base dark background
 *   [2] border     -> muted border / muted text
 *   [3] primary    -> primary (light) text
 *   [4] surface    -> secondary background (panels)
 */
static void theme_apply(const short pal[5][3]) {
  for (int i = 0; i < 5; i++) {
    init_color(30 + i, RGB_CONVERT(pal[i][0]), RGB_CONVERT(pal[i][1]),
               RGB_CONVERT(pal[i][2]));
  }

  init_pair(PAIR_TOPBAR, 33, 31);
  init_pair(PAIR_WINDOW, 33, 31);
  init_pair(PAIR_DESKTOP, 33, 31);
  init_pair(PAIR_WINDOW_BORDER, 32, 31);
  init_pair(PAIR_INACTIVE_WINDOW_BORDER, 32, 31);
  init_pair(PAIR_ACTIVE_WINDOW_BORDER, 30, 31);
  init_pair(PAIR_TEXT_PRIMARY, 33, 31);
  init_pair(PAIR_TEXT_MUTED, 32, 31);
}

static void apply_gruvbox(void) {
  static const short pal[5][3] = {
      {254, 128, 25},  // accent
      {40, 40, 40},    // background
      {146, 131, 116}, // border / muted
      {235, 219, 211}, // primary text
      {29, 32, 33},    // surface
  };
  theme_apply(pal);
}

static void apply_nord(void) {
  static const short pal[5][3] = {
      {136, 192, 208}, // accent
      {46, 52, 64},    // background
      {76, 86, 106},   // border / muted
      {216, 222, 233}, // primary text
      {36, 41, 51},    // surface
  };
  theme_apply(pal);
}

static void apply_everforest(void) {
  static const short pal[5][3] = {
      {167, 192, 128}, // accent
      {43, 51, 57},    // background
      {122, 132, 120}, // border / muted
      {211, 198, 170}, // primary text
      {35, 42, 46},    // surface
  };
  theme_apply(pal);
}

static void apply_myth(void) {
  static const short pal[5][3] = {
      {222, 222, 222}, // accent
      {171, 166, 197}, // background
      {119, 118, 150}, // border / muted
      {41, 88, 174},   // primary text
      {20, 49, 97},    // surface
  };
  theme_apply(pal);
}

static void apply_woods(void) {
  static const short pal[5][3] = {
      {221, 226, 227}, // accent
      {154, 172, 184}, // background
      {179, 124, 87},  // border / muted
      {60, 69, 92},    // primary text
      {96, 65, 43},    // surface
  };
  theme_apply(pal);
}

static void apply_dreamy(void) {
  static const short pal[5][3] = {
      {25, 38, 82},    // accent
      {50, 65, 118},   // background
      {66, 85, 152},   // border / muted
      {84, 106, 184},  // primary text
      {96, 120, 205},  // surface
  };
  theme_apply(pal);
}

static void apply_race_red(void) {
  static const short pal[5][3] = {
      {240, 120, 28},  // accent
      {103, 9, 22},    // background
      {247, 188, 83},  // border / muted
      {233, 225, 185}, // primary text
      {207, 4, 44},    // surface
  };
  theme_apply(pal);
}

static void (*const theme_appliers[])(void) = {
    apply_gruvbox,   // 0  GRUVBOX
    apply_nord,      // 1  NORD
    apply_everforest,// 2  EVERFOREST
    apply_myth,      // 3  MYTH
    apply_woods,     // 4  WOODS
    apply_dreamy,    // 5  DREAMY
    apply_race_red,  // 6  RACE_RED
};

void theme_init() {
  start_color();
  use_default_colors();

  if (can_change_color()) {
    theme_manager(GRUVBOX);
  }
}

void theme_manager(Theme select) {
  if (!can_change_color())
    return;

  int n = (int)(sizeof(theme_appliers) / sizeof(theme_appliers[0]));
  if (select < 0 || select >= n)
    return;

  theme_appliers[select]();
  current_theme = select;
}

Theme theme_current(void) { return current_theme; }

const char *theme_name(Theme select) {
  switch (select) {
  case GRUVBOX:
    return "Gruvbox";
  case NORD:
    return "Nord";
  case EVERFOREST:
    return "Everforest";
  case MYTH:
    return "Myth";
  case WOODS:
    return "Woods";
  case DREAMY:
    return "Dreamy";
  case RACE_RED:
    return "Race Red";
  default:
    return "Unknown";
  }
}
/// In menu this look like 3 seperate boxes with colors init to preview the
/// which colors
