/*
 * Program exercise 4.4 from Data Structures using C
 * Remove leading and trailing white space from a string
 */
#include <stdio.h>
#include <string.h>

void string_left_trim(char* s, size_t n) {
  /* If the first character is not whitespace we are done */
  if (s[0] != ' ') {
    return;
  }
  /* Count the white space, keep iterating until we hit a non whitespace character */
  size_t idx = 0;
  while (idx < n) {
    if (s[idx] != ' ') {
      break;
    }
    idx += 1;
  }
  /* Move all the characters to the front */
  size_t i = 0;
  while (idx < n) {
    s[i] = s[idx];
    i++;
    idx++;
  }
}

void string_right_trim(char* s, size_t n) {
  size_t idx = n - 1;
  /* If the last character is not whitespace we are done */
  if (s[idx] != ' ') {
    return;
  }
  /* Count the white space, keep iterating until we hit a non whitespace character */
  while (idx != 0) {
    if (s[idx] != ' ') {
      break;
    }
    idx -= 1;
  }
  /* Place null terminator at the end */
  s[idx+1] = '\0';
}

int main() {
  char s[] = "  Hello World  ";
  printf("S %d\n", sizeof(s));
  string_left_trim(s, strlen(s));
  printf("Left trim: -%s-\n", s);
  string_right_trim(s, strlen(s));
  printf("Right trim: -%s-\n", s);
}