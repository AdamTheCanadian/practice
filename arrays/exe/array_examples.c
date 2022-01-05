#include "arrays/array.h"
#include <stdio.h>
#include <stdlib.h>

void Exercise_3_1() {
  static const int num_students = 20;
  static const int num_classes = 5;
  /* Given 20 students, and the marks for the students 5 classes, find different statistics */
  /* We are not actually going to do a 2D array [][], but a 1D array to make life simpler */
  int marks[num_students * num_classes];
  /* First initialize the marks to random numbers between 0 and 100 */
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 5; j++) {
      /* Make the numbers between 0 and 100 */
      marks[i * num_classes + j] = rand() % 100;
    }
  }

  Array2D_Print(marks, 20, 5, "Students");
  for (int i = 0; i < num_classes; i++) {
    printf("Average for class %d: %.3f\n", i,
           Array2D_AverageCol(marks, num_students, num_classes, i));
  }

  for (int i = 0; i < num_students; i++) {
    printf("Average for student %d: %.3f\n", i,
           Array2D_AverageRow(marks, num_students, num_classes, i));
  }

}

void Exercise_3_2() {
  /* Given an array of 100 integers, find pairs that sum to 50 */
  static const int n = 101;
  int arr[n];
  for (int i = 0; i < n; i++) {
    /* Keep elements between 0 and 50 */
    arr[i] = rand() % 50;
    printf("arr[%d]: %d\n", i, arr[i]);
  }


  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      int sum = arr[i] + arr[j];
      if (sum == 50) {
        printf("%d and %d sum to 50\n", arr[i], arr[j]);
      }
    }
  }

}
int main() {
  /* Sample problems taken from "Data Structures in C - Chapter 3*/
  Exercise_3_1();
  Exercise_3_2();
}