#include "../../include/helper/string_helper.h"
#include <ctype.h>

void remove_spaces(char *string) {
  int i = 0;
  int j = 0;

  while (string[i] != '\0') {
    if (string[i] != ' ') {
      string[j] = tolower(string[i]);
      j++;
    }
    i++;
  }
  string[j] = '\0';
}
