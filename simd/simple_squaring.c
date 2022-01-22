#include <xmmintrin.h>

/* Scalar version of squaring a number */
void mul4_scalar(float* ptr) {
  for( int i = 0; i < 4; i++ ) {
    const float f = ptr[ i ];
    ptr[ i ] = f * f;
  }
}

/* Vectorized version of squaring a number */
void mul4_vectorized(float* ptr) {
  __m128 f = _mm_loadu_ps( ptr );
  f = _mm_mul_ps( f, f );
  _mm_storeu_ps( ptr, f );
}

int main() {
  float arr1[4] = {3.0f, 4.0f, 5.0f, 6.0f};
  float arr2[4] = {3.0f, 4.0f, 5.0f, 6.0f};
  mul4_scalar(arr1);
  mul4_vectorized(arr2);
}