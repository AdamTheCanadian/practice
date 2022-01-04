#include "arrays/array.h"
#include <stdio.h>

void Array2D_Print(int arr[][], int rows, int cols, const char* prefix) {
  for (int i = 0; i < rows; i++) {
    if (prefix) {
      printf("%s[%d]", prefix, i);
    }
    for (int j = 0; j < cols; j++) {
      printf("%3d ", arr[i][j]);
    }
    printf("\n");
  }
}

void Array2D_AverageRows(int** arr, int rows, int cols) {
//  for (int i = 0; i < )
}