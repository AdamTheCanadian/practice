#ifndef CSAPP_ARRAYS_ARRAY_H_
#define CSAPP_ARRAYS_ARRAY_H_

void Array2D_Print(int* arr, int rows, int cols, const char* prefix);

/**
 * Calculate the average of a single column
 * \param arr pointer to an array that holds 2d data
 * \param rows number of rows in the array
 * \param cols number of cols in the array
 */
double Array2D_AverageCol(int* arr, int rows, int cols, int colNum);

double Array2D_AverageRow(int* arr, int rows, int cols, int rowNum);

#endif
