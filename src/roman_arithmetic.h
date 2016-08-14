
#ifndef ROMAN_ARITHMETIC_H_
#define ROMAN_ARITHMETIC_H_

typedef struct {
  int (*romanToArabic) (const char* roman, int* arabic);
  int (*arabicToRoman) (int arabic, char* roman, int len);
} ConversionPair;

int addRoman (ConversionPair *pair, const char* augend, const char* addend, char* sum, int len);
int subtractRoman (ConversionPair *pair, const char* minuend, const char* subtrahend, char* sum, int len);

#endif /* ROMAN_ARITHMETIC_H_ */
