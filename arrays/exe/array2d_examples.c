#include "arrays/array.h"
#include <stdio.h>
#include <stdlib.h>

void Exercise_3_1() {
  /* Sample problem taken from "Data Structures in C - Chapter 3 #1 */
  /* Given 20 students, and the marks for the students 5 classes, find different statistics */
  int marks[20][5];
  /* First initialize the marks to random numbers between 0 and 100 */
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 5; j++) {
      /* Make the  */
      marks[i][j] = rand() % 100;
    }
  }

  Array2D_Print(marks, 20, 5, "Students");

}


int main() {
  Exercise_3_1();
}