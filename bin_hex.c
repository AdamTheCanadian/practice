#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @program This program simply takes binary, decimal, or hex input and converts
 * to the other forms (decimal to binary and hex for example).
 *
 * There are obviously easier ways to convert, and smarter implementations but this
 * is meant for learning and doing it from fundamentals. For example, if you have
 * a binary to decimal converter. To convert Hex to decimal and binary you could in
 * theory first convert hex to decimal, and then decimal to binary (and skip hex to binary).
 * But where is the fun in that.
 */

/* Buffer for holding input */
char buf[256] = {'\0'};
size_t buf_len = 0;

char hex_str[256] = {'\0'};
size_t hex_len = 0;

/* Binary strings take up more space (8 characters extra) so make sure to account for that */
char bin_str[256 * 8] = {'\0'};
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
void convert_integer();

/* calculate 2 ^ n */
int two_exp(int n);
/* calculate 16 ^ n */
int sixteen_exp(int n);

char hex_lookup[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

/* Lookup for the binary equivalent of a hex character. We assume the 'A' to 'F' values
 * are offset by 0x11 */
const char* hex_to_bin_lookup[16] = {
    "0000", //  0
    "0001", // 1
    "0010", // 2
    "0011", // 3
    "0100", // 4
    "0101", // 5
    "0110", // 6
    "0111", // 7
    "1000", // 8
    "1001", // 9
    "1010", // 10
    "1011", // 11
    "1100", // 12
    "1101", // 13
    "1110", // 14
    "1111", // 15
};

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
    convert_integer();
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
  for (size_t i = 0; i < buf_len; i++) {
    if (buf[i] < '0' || buf[i] > '9') {
      printf("Invalid numeric character %c in input %s\n", buf[i], buf);
      return 0;
    }
  }
  return 1;
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
  /* Copy over the hex (input) string, minus the '0x' */
  hex_len = buf_len - 2;
  strncpy(hex_str, &buf[2], hex_len);
  /* To make life easier, convert all hex lower case characters ('a' to 'f') to
   * the capital form. We can leverage the fact that the hex ascii value for 'a' is 0x61, and
   * for 'A' is 0x41. So if we have any lower case inputs, we can simply subtract 0x20 to convert
   * from lowercase to upper case*/
  for (size_t i = 0; i < hex_len; i++) {
    if (hex_str[i] >= 'a' && hex_str[i] <= 'f') {
      hex_str[i] -= 0x20;
    }
  }
  bin_len = 0;
  /* There is not really any way to convert hex to binary besides a
   * simple look up, since hex is literaly a character representation of 4 bits.
   * So we will use the hex ascii value ('0'-'9', 'A'-'F) as a lookup to its
   * binary equivalent. We need to offset the '0'-'9' characters by 0x30 (since
   * they start at value 0x30 and we want them to start at value 0 to be used
   * as an index), and 'A'-'F' need to be offset by 0x7 so we will artificially have
   * the characters layed out in this order: 0 1 2 3 4 5 6 7 8 9 A B C D E F*/
  for (size_t i = 0; i < hex_len; i++) {
    char val = hex_str[i];
    /* First subtract the  */
    val -= 0x30;
    /* If our value is still greater than 9, we must have started with a 'A'-'F'
     * character, so need to remove the last 7 to bring it in desired range*/
    if (val > 0x09) {
      val -= 0x07;
    }
    const char* b = hex_to_bin_lookup[(int)val];
    for (int j = 0; j < 4; j++) {
      bin_str[bin_len + j] = b[j];
    }
    bin_len += 4;
  }

  /*
   * To convert hex to decimal/integer, its pretty easy so just need to take
   * the numeric representation of each character and times by 16^n and add it up
   * For example:
   * 0x3B = 3 * 16^1 + 11 * 16^0 == 59 (where 'B' is hex for 11)
   */
  /* We are going to process the hex string in order, which means the first
   * character in the string is the highest power (n) of 16, which is equivalent
   * of the total length. Then every other character will be n-1
   * We start with a -1 since the last exponent is 0, not 1. So if there are 3 hex
   * characters we will have exponents 2/1/0 (not 3/2/1)*/
  int n = (int)hex_len - 1;
  unsigned_value = 0;
  for (size_t i = 0; i < hex_len; i++) {
    /* Convert the ascii hex value to its integer representation by leveraging the
     * fact we know '0' to '9' starts at actual hex value 0x30 and 'A'-'9' starts at 0x41 */
    int int_val = (int)hex_str[i];
    int_val -= 0x30;
    if (int_val > 0x09) {
      int_val -= 0x07;
    }
    unsigned_value += (int_val * sixteen_exp(n));
    n -= 1;
  }
}

int sixteen_exp(int n) {
  int s = 1;
  for (int i = 0; i < n; i++) {
    s = s * 16;
  }
  return s;
}

void convert_integer() {
  /* Convert string to integer value, our starting/input value */
  unsigned_value = strtoull(buf, NULL, 10);

  /*
   * Convert to hex first. Just keep dividing by 16 until no remainder
   * is left. This however prints the hex string in reverse order. So
   * going to store the answer in a temporary and then flip it
   */
  uint64_t tmp_val = unsigned_value;
  char tmp_hex_str[256] = {'\0'};
  size_t tmp_hex_len = 0;;
  /* In the case the input is 0 */
  tmp_hex_str[tmp_hex_len] = '0';

  while (tmp_val != 0) {
    uint64_t div = tmp_val / 16;
    uint64_t rem = tmp_val - (div * 16);
    tmp_hex_str[tmp_hex_len] = hex_lookup[rem];
    tmp_hex_len += 1;
    tmp_val = div;
  }
  if (tmp_hex_len == 0) {
    tmp_hex_len += 1;
  }

  for (size_t i = 0; i < tmp_hex_len; i++) {
    hex_str[i] = tmp_hex_str[tmp_hex_len - i - 1];
  }
  hex_len = tmp_hex_len;

}