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

/* calculate 2 ^ n */
int two_exp(int n);

char hex_lookup[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

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

  /* For every character past the 0b (hence starting at 2) we need to check
   * if the bit is enabled, compute the exponent (2^N) if it is, and accumulate
   * into the final integer value */
  for (size_t i = 2; i < buf_len; i++) {
    size_t exp = buf_len - i - 1;
    /* If the bit is 1, we need to compute 2^exp */
    if (buf[i] == '1') {
      uint64_t sum = 1;
      for (size_t j = 0; j < exp; j++) {
        sum = sum * 2;
      }
      uint += sum;
    }
  }

  /* Hexadecimal
   * 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
   * Each 4 bits is one hexadecimal character
   * So probably need to start at the back/end of the binary string
   * and work to the front (right to left)
   * A potential implementation is store all bits to hex in a table
   * and compare them
   * 4 bits == nibbles
   */
  char hex_str[128];
  size_t hex_idx = 0;

  int nibble_cnt = 1;
  int s = 0;
  for (size_t i = buf_len-1; i >= 2; i--) {
    char bit = buf[i];
    if (bit == '1') {
      s += two_exp(nibble_cnt - 1);
    }
    /* Processed 4 bits, need to add the hex character and go to the next 4 bits */
    if (nibble_cnt >= 4) {
      hex_str[hex_idx] = hex_lookup[s];
      hex_idx += 1;
      nibble_cnt = 1;
      s = 0;
    }
    else {
      nibble_cnt += 1;
    }
  }
  /* We may have had <4 bits to process so need to handle that corner case */
  if (nibble_cnt > 1) {
    hex_str[hex_idx] = hex_lookup[s];
    hex_idx += 1;
  }
  printf("Binary %s is:\n", buf);
  printf("\tDec: %lld\n", uint);
  printf("\tHex: 0x");
  for (size_t i = hex_idx - 1; i < hex_idx; i--) {
    printf("%c", hex_str[i]);
  }
  printf("\n");
  printf("Using printf hex 0x%X\n", uint);
}

int two_exp(int n) {
  /*
   * If n == 0
   * 2 ^ 0 == 1 so this will work
   *
   * if n == 2
   * s == 1
   * s = s * 2 == 2
   * s = s * 2 == 4
   */
  int s = 1;
  for (int i = 0; i < n; i++) {
    s = s * 2;
  }
  return s;
}