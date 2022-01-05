#include "arrays/array.h"
#include <stdio.h>
#include <stdlib.h>

void Exercise_3_1() {
  static const int num_students = 20;
  static const int num_classes = 5;
  /* Sample problem taken from "Data Structures in C - Chapter 3 #1 */
  /* Given 20 students, and the marks for the students 5 classes, find different statistics */
  /* We are not actually going to do a 2D array [][], but a 1D array to make life simpler */
  int marks[num_students * num_classes];
  /* First initialize the marks to random numbers between 0 and 100 */
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 5; j++) {
      /* Make the  */
      marks[i * num_classes + j] = rand() % 100;
    }
  }

  Array2D_Print(marks, 20, 5, "Students");
  Array2D_AverageCols(marks, 20, 5);
}


int main() {
  Exercise_3_1();
}