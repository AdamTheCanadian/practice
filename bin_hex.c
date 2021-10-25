#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Buffer for holding input */
char buf[256];
size_t buf_len = 0;

char hex_str[256];
size_t hex_len = 0;

/* Binary strings take up more space (8 characters extra) so make sure to account for that */
char bin_str[256 * 8];
size_t bin_len = 0;

uint64_t unsigned_value = 0;
int64_t signed_value = 0;

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
void convert_hexadecimal();

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
    /* Dont copy the '0b' */
    strncpy(bin_str, &buf[2], buf_len-2);
    convert_binary();
  }
  else if (input_type == Hexadecimal) {
    if (validate_hexadecimal_input() == 0) {
      return 1;
    }
    convert_hexadecimal();
  }
  else if (input_type == Integer) {
    if (validate_integer_input() == 0) {
      return 1;
    }
  }
  else {
    return 0;
  }

  /* Print the converted values */
  printf("Input:       %s\n", buf);
  printf("Binary:      0b%s\n", bin_str);
  printf("Hexadecimal: 0x%s\n", hex_str);
  printf("Unsigned:    %lld\n", unsigned_value);
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
  if (buf[0] != '0' && buf[1] != 'x') {
    return 0;
  }
  for (size_t i = 2; i < buf_len; i++) {
    /* Valid hex ASCII characters are '0' to '9', 'a' to 'f', and 'A' to 'F' */
    if (buf[i] >= '0' && buf[i] <= '9' ||
        buf[i] >= 'a' && buf[i] <= 'f' ||
        buf[i] >= 'A' && buf[i] <= 'F') {
      continue;
    }
    printf("Invalid hexadecimal character %c in %s\n", buf[i], buf);
    return 0;
  }
  return 1;
}

int validate_integer_input() {

}

void convert_binary() {
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
      unsigned_value += sum;
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
  /* We know how many bits there are (the input minus the '0b') */
  size_t num_bits = buf_len - 2;
  /* We can determine the number of hex characters (remember each character is 4 bits)
   * by dividing by 4. However, since integer division will round down (7 / 4 == 1), we will
   * add 3 to make sure we round to the correct number of characters: For example:
   * 7 / 4 == 1 but we need at least 2 characters (1 to hold four bits, 1 to hold 3 bits)
   * so
   * (7 + 3) / 4 -> 10 / 4 == 2
   * We do +3 for the case that the input is already a perfect multiple of 4. For example:
   * If num_bits == 8
   * (8 + 3) / 4 -> 11 / 4 == 2 which is correct.
   * If we did + 4 we would get (8 + 4) / 4 which is 12/4 == 3, which is not correct.
   * We need/want the number of hex characters to put the hex string in correct order
   * For example:
   * 0b0001111 == 0x0F in hex, but if we process the last 4 bits (1111) first,
   * then the front 3 (000) we would get a string of 0xF0
   */
  size_t num_hex_chars = (num_bits + 3) / 4;
  printf("Num hex bytes %d\n", num_hex_chars);

  int nibble_cnt = 1;
  int s = 0;
  for (size_t i = buf_len-1; i >= 2; i--) {
    char bit = buf[i];
    if (bit == '1') {
      s += two_exp(nibble_cnt - 1);
    }
    /* Processed 4 bits, need to add the hex character and go to the next 4 bits */
    if (nibble_cnt >= 4) {
      /* Remember we want to put the string in reverse order, so if there
       * are 2 hex characters required (5 to 8 bit input) we want to place the first
       * character at index 1, then index 0, so we need to minus 1*/
      hex_str[num_hex_chars - hex_len - 1] = hex_lookup[s];
      hex_len += 1;
      nibble_cnt = 1;
      s = 0;
    }
    else {
      nibble_cnt += 1;
    }
  }
  /* We may have had <4 bits to process so need to handle that corner case */
  if (nibble_cnt > 1) {
    hex_str[num_hex_chars - hex_len - 1] = hex_lookup[s];
    hex_len += 1;
  }
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

void convert_hexadecimal() {

}