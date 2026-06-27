#include "../../../include/window/theme/theme.h"
#include <ncurses.h>

static void apply_gruvbox(void) {
  init_color(30, RGB_CONVERT(254), RGB_CONVERT(128), RGB_CONVERT(25));
  init_color(31, RGB_CONVERT(40), RGB_CONVERT(40), RGB_CONVERT(40));
  init_color(32, RGB_CONVERT(146), RGB_CONVERT(131), RGB_CONVERT(116));
  init_color(33, RGB_CONVERT(235), RGB_CONVERT(219), RGB_CONVERT(211));
  init_color(34, RGB_CONVERT(29), RGB_CONVERT(32), RGB_CONVERT(33));

  init_pair(1, 31, 30);
  init_pair(2, 33, 31);
  init_pair(3, 30, 31);
  init_pair(4, 32, 31);
  init_pair(5, 33, 34);
}

static void apply_nord(void) {
  init_color(30, RGB_CONVERT(136), RGB_CONVERT(192), RGB_CONVERT(208));
  init_color(31, RGB_CONVERT(46), RGB_CONVERT(52), RGB_CONVERT(64));
  init_color(32, RGB_CONVERT(76), RGB_CONVERT(86), RGB_CONVERT(106));
  init_color(33, RGB_CONVERT(216), RGB_CONVERT(222), RGB_CONVERT(233));
  init_color(34, RGB_CONVERT(36), RGB_CONVERT(41), RGB_CONVERT(51));

  init_pair(1, 34, 30);
  init_pair(2, 33, 31);
  init_pair(3, 30, 31);
  init_pair(4, 32, 31);
  init_pair(5, 33, 34);
}

static void apply_everforest(void) {
  init_color(30, RGB_CONVERT(167), RGB_CONVERT(192), RGB_CONVERT(128));
  init_color(31, RGB_CONVERT(43), RGB_CONVERT(51), RGB_CONVERT(57));
  init_color(32, RGB_CONVERT(122), RGB_CONVERT(132), RGB_CONVERT(120));
  init_color(33, RGB_CONVERT(211), RGB_CONVERT(198), RGB_CONVERT(170));
  init_color(34, RGB_CONVERT(35), RGB_CONVERT(42), RGB_CONVERT(46));

  init_pair(1, 34, 30);
  init_pair(2, 33, 31);
  init_pair(3, 30, 31);
  init_pair(4, 32, 31);
  init_pair(5, 33, 34);
}
static void apply_myth(void) {
  init_color(30, RGB_CONVERT(222), RGB_CONVERT(222), RGB_CONVERT(222));
  init_color(31, RGB_CONVERT(171), RGB_CONVERT(166), RGB_CONVERT(197));
  init_color(32, RGB_CONVERT(119), RGB_CONVERT(118), RGB_CONVERT(150));
  init_color(33, RGB_CONVERT(41), RGB_CONVERT(88), RGB_CONVERT(174));
  init_color(34, RGB_CONVERT(20), RGB_CONVERT(49), RGB_CONVERT(97));

  init_pair(1, 34, 30);
  init_pair(2, 33, 31);
  init_pair(3, 30, 31);
  init_pair(4, 32, 31);
  init_pair(5, 33, 34);
}
static void apply_woods(void) {
  init_color(30, RGB_CONVERT(221), RGB_CONVERT(226), RGB_CONVERT(227));
  init_color(31, RGB_CONVERT(154), RGB_CONVERT(172), RGB_CONVERT(184));
  init_color(32, RGB_CONVERT(179), RGB_CONVERT(124), RGB_CONVERT(87));
  init_color(33, RGB_CONVERT(60), RGB_CONVERT(69), RGB_CONVERT(92));
  init_color(34, RGB_CONVERT(96), RGB_CONVERT(65), RGB_CONVERT(43));

  init_pair(1, 34, 30);
  init_pair(2, 33, 31);
  init_pair(3, 30, 31);
  init_pair(4, 32, 31);
  init_pair(5, 33, 34);
}
static void apply_dreamy(void) {
  init_color(30, RGB_CONVERT(25), RGB_CONVERT(38), RGB_CONVERT(82));
  init_color(31, RGB_CONVERT(50), RGB_CONVERT(65), RGB_CONVERT(118));
  init_color(32, RGB_CONVERT(66), RGB_CONVERT(85), RGB_CONVERT(152));
  init_color(33, RGB_CONVERT(84), RGB_CONVERT(106), RGB_CONVERT(184));
  init_color(34, RGB_CONVERT(96), RGB_CONVERT(120), RGB_CONVERT(205));

  init_pair(1, 34, 30);
  init_pair(2, 33, 31);
  init_pair(3, 30, 31);
  init_pair(4, 32, 31);
  init_pair(5, 33, 34);
}
static void apply_race_red(void) {
  init_color(30, RGB_CONVERT(103), RGB_CONVERT(9), RGB_CONVERT(22));
  init_color(31, RGB_CONVERT(207), RGB_CONVERT(4), RGB_CONVERT(44));
  init_color(32, RGB_CONVERT(240), RGB_CONVERT(120), RGB_CONVERT(28));
  init_color(33, RGB_CONVERT(247), RGB_CONVERT(188), RGB_CONVERT(83));
  init_color(34, RGB_CONVERT(233), RGB_CONVERT(225), RGB_CONVERT(185));

  init_pair(1, 34, 30);
  init_pair(2, 33, 31);
  init_pair(3, 30, 31);
  init_pair(4, 32, 31);
  init_pair(5, 33, 34);
}
void theme_init() {
  start_color();
  use_default_colors();

  if (can_change_color()) {

    theme_manager(0);
  }
}

void theme_manager(Theme select) {
  if (can_change_color()) {
    if (select == GRUVBOX) {
      apply_gruvbox();
    } else if (select == EVERFOREST) {
      apply_everforest();
    } else if (select == NORD) {
      apply_nord();
    } else if (select == MYTH) {
      apply_myth();
    } else if (select == WOODS) {
      apply_woods();
    } else if (select == DREAMY) {
      apply_dreamy();
    } else if (select == RACE_RED) {
      apply_race_red();
    }
  }
}
/// In menu this look like 3 seperate boxes with colors init to preview the
/// which colors
