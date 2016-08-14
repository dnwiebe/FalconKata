
#include "roman_arithmetic.h"

/********************/
/* PUBLIC INTERFACE */
/********************/

int addRoman (ConversionPair *pair, const char* augend, const char* addend, char* sum, int len) {
  int augendA;
  int addendA;
  int sumA;

  pair->romanToArabic (augend, &augendA);
  pair->romanToArabic (addend, &addendA);
  sumA = augendA + addendA;
  pair->arabicToRoman (sumA, sum, len);
  return 0;
}

int subtractRoman (ConversionPair *pair, const char* minuend, const char* subtrahend, char* sum, int len) {
  int minuendA;
  int subtrahendA;
  int differenceA;

  pair->romanToArabic (minuend, &minuendA);
  pair->romanToArabic (subtrahend, &subtrahendA);
  differenceA = minuendA - subtrahendA;
  pair->arabicToRoman (differenceA, sum, len);
  return 0;
}
