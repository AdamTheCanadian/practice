#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Buffer for holding input */
char buf[256];
size_t buf_len = 0;


typedef enum {
  Binary,
  Hexadecimal,
  Integer
} InputType;

/* Test the buffer and try to determine the type of input. At this point
 * its more a starting point/guess */
InputType determine_input_type();

int validate_binary_input();
int validate_hexadecimal_input();
int validate_integer_input();

void convert_binary();

int main(int argc, char* argv []) {
  /*
   * Want the ability to:
   * 1. take a user input string
   * 2. Check if its
   *  a) in binary form 0b01010 for example
   *  b) hex form 0xFFEE for example
   *  c) integer form
   * 3. Convert between the different forms and print the results
   */
  if (argc < 2) {
    /* print usage */
    printf("Not enough input arguments\n");
    return 1;
  }
  /* Copy the input argument into the buffer */
  strncpy(buf, argv[1], 256);
  buf_len = strlen(buf);

  InputType input_type = determine_input_type();
  if (input_type == Binary) {
    if (validate_binary_input() == 0) {
      return 1;
    }
    convert_binary();
  }
  else if (input_type == Hexadecimal) {
    if (validate_hexadecimal_input() == 0) {
      return 1;
    }
  }
  else if (input_type == Integer) {
    if (validate_integer_input() == 0) {
      return 1;
    }
  }
  else {

  }
}

InputType determine_input_type() {
  /* Both binary and hex require 3 or more characters (0b##, or 0x##) */
  if (buf_len < 3) {
    return Integer;
  }
  if (buf[1] == 'b') {
    return Binary;
  }
  else if (buf[1] == 'x') {
    return Hexadecimal;
  }
  else {
    return Integer;
  }
}

int validate_binary_input() {
  if (buf[0] != '0') {
    return 0;
  }
  if (buf[1] != 'b') {
    return 0;
  }
  /* All other characters should be 1 or 0 */
  for (size_t i = 2; i < buf_len; i++) {
    if (buf[i] != '0' && buf[i] != '1') {
      printf("Invalid binary character %c in %s\n", buf[i], buf);
      return 0;
    }
  }
  return 1;
}

int validate_hexadecimal_input() {

}

int validate_integer_input() {

}

void convert_binary() {
  /* Convert binary to signed an unsigned integers */
  uint64_t uint = 0;
  int64_t sint = 0;

  for (size_t i = 2; i < buf_len; i++) {
    size_t exp = buf_len - i - 1;
    uint64_t s = 0;
    /* If the bit is 1, we need to compute 2^exp */
    if (buf[i] == '1') {
      s = 1;
      for (size_t j = 0; j < exp; j++) {
        s = s * 2;
      }
    }
    uint += s;
  }
  printf("Uint %lld\n", uint);
}