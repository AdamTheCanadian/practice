#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Casting different types and values to see how it works\n");

  int64_t true_value = 0xAABBCCDDEEFF1122;

  printf("Casting %llX to int8_t Hex: %X\n", true_value, (int8_t)true_value);
  printf("Casting %llX to int8_t value: %d\n", true_value, (int8_t)true_value);

  printf("Casting %llX to uint8_t Hex: %X\n", true_value, (uint8_t)true_value);
  printf("Casting %llX to uint8_t value: %d\n", true_value, (uint8_t)true_value);
}