
#include "roman_arithmetic.h"

int romanBinaryArithmetic (ConversionPair *pair, const char* first, const char* second, char* result, int len, int (*compute) (int, int)) {
  int firstA;
  int secondA;
  int resultA;
  int status;

  status = pair->romanToArabic (first, &firstA);
  if (status != 0) {return status;}
  status = pair->romanToArabic (second, &secondA);
  if (status != 0) {return status;}
  resultA = compute (firstA, secondA);
  status = pair->arabicToRoman (resultA, result, sizeof (result));
  return status;
}

int adder (int augend, int addend) {
  return augend + addend;
}

int subtracter (int minuend, int subtrahend) {
  return minuend - subtrahend;
}

/********************/
/* PUBLIC INTERFACE */
/********************/

int addRoman (ConversionPair *pair, const char* augend, const char* addend, char* sum, int len) {
  return romanBinaryArithmetic (pair, augend, addend, sum, len, adder);
}

int subtractRoman (ConversionPair *pair, const char* minuend, const char* subtrahend, char* sum, int len) {
  return romanBinaryArithmetic (pair, minuend, subtrahend, sum, len, subtracter);
}
