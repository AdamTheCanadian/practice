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

double Array2D_AverageCol(int* arr, int rows, int cols, int colNum) {
  double sum = 0.0;
  for (int i = 0; i < rows; i++) {
    sum += arr[i* cols + colNum];
  }
  sum /= rows;
  return sum;
}

double Array2D_AverageRow(int* arr, int rows, int cols, int rowNum) {
  double sum = 0.0;
  for (int i = 0; i < cols; i++) {
    sum += arr[rowNum * cols + i];
  }
  sum /= cols;
  return sum;
}