#include <stddef.h>
#include <string.h>
#include "converters.h"

typedef struct {
  const char* element;
  int value;
} ValueElement;

const ValueElement valueElements[] = {
  {"M", 1000},
  {"CM", 900},
  {"D", 500},
  {"CD", 400},
  {"C", 100},
  {"XC", 90},
  {"L", 50},
  {"XL", 40},
  {"X", 10},
  {"IX", 9},
  {"V", 5},
  {"IV", 4},
  {"I", 1}
};

int startsWith (const char* string, const char* prefix) {
  const char* stringP = string;
  const char* prefixP = prefix;

  while (*prefixP != 0) {
    if (*stringP != *prefixP) {return 0;}
    stringP++;
    prefixP++;
  }
  return 1;
}

const ValueElement* findElementWithPrefix (const char* p) {
  int elementCount = sizeof (valueElements) / sizeof (ValueElement);
  int i;

  for (i = 0; i < elementCount; i++) {
    if (startsWith (p, valueElements[i].element)) {
      return &valueElements[i];
    }
  }
  return NULL;
}

/********************/
/* PUBLIC INTERFACE */
/********************/

int convertRtoA (const char* roman, int* arabic) {
  int valueSoFar = 0;
  const char* p = roman;
  const ValueElement* valueElement;

  while (*p != 0) {
    valueElement = findElementWithPrefix (p);
    if (valueElement == NULL) {return RC_INVALID_ROMAN_NUMERAL;}
    valueSoFar += valueElement->value;
    p += strlen (valueElement->element);
  }
  if (valueSoFar > 3999) {return RC_NUMBER_OUT_OF_RANGE;}
  *arabic = valueSoFar;
  return 0;
}

int convertAtoR (int arabic, char* roman, int len) {
  int valueRemaining = arabic;
  char romanF[80];
  char* p = romanF;
  int idx = 0;
  const ValueElement* valueElement;

  if ((arabic < 1) || (arabic > 3999)) {return RC_NUMBER_OUT_OF_RANGE;}
  while (valueRemaining > 0) {
    valueElement = &valueElements[idx];
    if (valueRemaining >= valueElement->value) {
      strcpy (p, valueElement->element);
      p += strlen (valueElement->element);
      valueRemaining -= valueElement->value;
    }
    else {
      idx++;
    }
  }
  if (strlen (romanF) > len - 1) {return RC_OUTPUT_OVERRUN;}
  strncpy (roman, romanF, len - 1);
  return 0;
}
