#include "arrays/array.h"
#include <stdio.h>

void Array2D_Print(int* arr, int rows, int cols, const char* prefix) {
  for (int i = 0; i < rows; i++) {
    if (prefix) {
      printf("%s[%d]", prefix, i);
    }
    for (int j = 0; j < cols; j++) {
      printf("%3d ", arr[i* cols + j]);
    }
    printf("\n");
  }
}

void Array2D_AverageCols(int* arr, int rows, int cols) {
  for (int j = 0; j < cols; j++) {
    double sum = 0;
    for (int i = 0; i < rows; i++) {
      sum += arr[i* cols + j];
    }
    sum /= rows;
    printf("Average of Column [%d]: %.3f\n", j, sum);
  }
}