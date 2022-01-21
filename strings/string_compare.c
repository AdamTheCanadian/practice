/*
 * Program exercise 4.3 from Data Structures using C
 */
#include <stdbool.h>
#include <stdio.h>

/* Compare the N characters of s1 with s2
 * Will return true if [0, n] is the same for both strings */
bool string_compare(const char* s1,
                    const char* s2,
                    size_t n) {
  bool ret_val = true;
  for (size_t i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      ret_val = false;
      break;
    }
  }
  return ret_val;
}

int main() {
  /* Compare the Hello of both strings */
  if (string_compare("Hello World", "HelloWorld", 5)) {
    printf("Yep\n");
  }
  /* Compare the Hello (with space) and HelloW */
  if (!string_compare("Hello World", "HelloWorld", 6)) {
    printf("Nope\n");
  }
}