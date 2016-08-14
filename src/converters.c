#include <stddef.h>
#include <string.h>
#include "converters.h"

typedef struct {
  const char* element;
  int value;
} ValueElement;

ValueElement valueElements[] = {
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

int RC_INVALID_ROMAN_NUMERAL = 1;

/********************/
/* PUBLIC INTERFACE */
/********************/

int convertRtoA (const char* roman, int* arabic) {
  int valueSoFar = 0;
  const char* p = roman;

  while (*p != 0) {
    const ValueElement* valueElement = findElementWithPrefix (p);
    if (valueElement == NULL) {return RC_INVALID_ROMAN_NUMERAL;}
    valueSoFar += valueElement->value;
    p += strlen (valueElement->element);
  }
  *arabic = valueSoFar;
  return 0;
}

int convertAtoR (int arabic, char* roman, int len) {
  return 1;
}
