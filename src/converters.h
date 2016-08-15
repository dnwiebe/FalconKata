
#ifndef CONVERTERS_H_
#define CONVERTERS_H_

int convertRtoA (const char* roman, int* arabic);
int convertAtoR (int arabic, char* roman, int len);

#define RC_INVALID_ROMAN_NUMERAL 5
#define RC_NUMBER_OUT_OF_RANGE 6
#define RC_OUTPUT_OVERRUN 7

#endif /* CONVERTERS_H_ */
