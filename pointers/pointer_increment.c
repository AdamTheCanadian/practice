#include <stdio.h>

void ptr_double(double* arr, int n) {
  /* Notice how incrementing the array pointer increment goes to the next element in
   * the array, does not increment address 1, increments address by 8 which is the
   * size of the double
   */
  for (int i = 0; i < n; i++) {
    printf("%d: %.3f\n", i, *arr);
    arr++;
  }
}

int main() {
  double arr[10] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 0.0};
  ptr_double(arr, 10);
}