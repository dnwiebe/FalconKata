#include <stdio.h>
#include <unistd.h>
#include "binary_parser.h"
#include "roman_arithmetic.h"
#include "converters.h"

ConversionPair conversionPair = {convertRtoA, convertAtoR};

int romanAdder (const char* augend, const char* addend, char* sum, int len) {
  return addRoman (&conversionPair, augend, addend, sum, len);
}

int romanSubtracter (const char* minuend, const char* subtrahend, char* difference, int len) {
  return subtractRoman (&conversionPair, minuend, subtrahend, difference, len);
}

BinaryOperation operations[] = {
  {"+", romanAdder},
  {"-", romanSubtracter}
};

int readLine (int hdl, char* line, int len) {
  int c;
  char* p = line;

  while ((read (hdl, &c, 1) > 0) && (p - line < len - 1)) {
    *p++ = c;
    if (*(p - 1) == '\n') {
      *p = 0;
      return 0;
    }
  }
  *p = 0;
  return 1;
}

int main (int argc, char* argv[]) {
  char inputLine[80];
  char outputLine[80];
  int inputStatus;
  int programStatus = 0;
  int status;

  do {
    inputStatus = readLine (STDIN_FILENO, inputLine, sizeof (inputLine));
    status = performBinaryOperations (operations, sizeof (operations) / sizeof (*operations),
            inputLine, outputLine, sizeof (outputLine));
    programStatus = programStatus || status;
    if (status == 0) {
      printf ("%s", outputLine);
    }
    else {
      printf ("# %s", outputLine);
    }
  } while (inputStatus == 0);

  return programStatus;
}
