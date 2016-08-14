
#ifndef CONVERTERS_H_
#define CONVERTERS_H_

int convertRtoA (const char* roman, int* arabic);
int convertAtoR (int arabic, char* roman, int len);

int RC_INVALID_ROMAN_NUMERAL;
int RC_NUMBER_OUT_OF_RANGE;
int RC_OUTPUT_OVERRUN;

#endif /* CONVERTERS_H_ */
