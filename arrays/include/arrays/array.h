#ifndef CSAPP_ARRAYS_ARRAY_H_
#define CSAPP_ARRAYS_ARRAY_H_

void Array2D_Print(int arr[][], int rows, int cols, const char* prefix);

/**
 * Calculate the average of a 2D array (arr)
 * \param arr pointer to 2D array [][]
 * \param rows number of rows in the array
 * \param cols number of cols in the array
 */
void Array2D_AverageRows(int** arr, int rows, int cols);

#endif
