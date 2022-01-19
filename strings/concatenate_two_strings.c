/*
 * Program exercise 4.2 from Data Structures using C
 */
#include <string.h>
#include <stdio.h>

/*
 * Concatenate s1 and s2, and put it into s3
 * Assumes memory is allocated
 */
void concatenate(const char* s1,
                 const char* s2,
                 char* s3) {
  size_t n1 = strlen(s1);
  size_t n2 = strlen(s2);
  size_t idx = 0;
  for (int i = 0; i < n1; i++) {
    s3[idx] = s1[i];
    idx += 1;
  }
  for (int i = 0; i < n2; i++) {
    s3[idx] = s2[i];
    idx += 1;
  }
  /* Dont forget null terminator */
  s3[idx] = '\0';
  printf("N1 %lu\n", n1);
  printf("N2 %lu\n", n2);
  /* Check to make sure N3 is N1 + N2 */
  printf("N3 %lu\n", strlen(s3));
  printf("S3: %s\n", s3);
}

int main() {
  const char* hello = "Hello ";
  const char* world = "World";
  /* Purposely making the string initialized to something long to test
   * to make sure we include the null terminator */
  char combined[128] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  concatenate(hello, world, combined);
}