#ifndef CSAPP_ARRAYS_ARRAY_H_
#define CSAPP_ARRAYS_ARRAY_H_

void Array2D_Print(int* arr, int rows, int cols, const char* prefix);

/**
 * Calculate the average of a single column
 * \param arr pointer to an array that holds 2d data
 * \param rows number of rows in the array
 * \param cols number of cols in the array
 */
void Array2D_AverageCols(int* arr, int rows, int cols);

#endif
