#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "binary_parser.h"

int isSpace (char c) {
  return (c == ' ') || (c == '\t') || (c == '\n');
}

int findSubstring (char* fromHere, char** begin, char** end, int canEnd) {
  char *p = fromHere;
  while (isSpace (*p) && (*p != 0)) {p++;}
  if (*p == 0) {return 1;}
  *begin = p;
  while (!isSpace (*p) && (*p != 0)) {p++;}
  if ((*p == 0) && !canEnd) {return 1;}
  *end = p;
  return 0;
}

int parseLine (char* line, char** leftOperand, char** operator, char** rightOperand) {
  char* begins[] = {NULL, NULL, NULL};
  char* ends[] = {NULL, NULL, NULL};
  char* fromHere = line;
  int foundProblem = 0;
  int i;

  for (i = 0; i < 3; i++) {
    foundProblem = findSubstring (fromHere, &begins[i], &ends[i], i == 2);
    if (foundProblem) {return 1;}
    fromHere = ends[i] + 1;
  }

  *leftOperand = begins[0]; *ends[0] = 0;
  *operator = begins[1]; *ends[1] = 0;
  *rightOperand = begins[2]; *ends[2] = 0;
  return 0;
}

const BinaryOperation* selectOperation (const BinaryOperation* operations, int count, const char* operator) {
  int i;

  for (i = 0; i < count; i++) {
    const BinaryOperation* operation = &operations[i];
    if (!strcmp (operator, operation->operator)) {
      return operation;
    }
  }
  return NULL;
}

int wrap (const char* line, char* answer, int len, int returnValue) {
  strncpy (answer, line, len);
  return returnValue;
}

int processLine (const BinaryOperation* operations, int count, const char* line, char* result, int len) {
  char lineCopy[80];
  char* leftOperand;
  char* operator;
  char* rightOperand;
  const BinaryOperation* operation;
  char answer[80];
  int returnValue = 0;

  do {
    strncpy (lineCopy, line, sizeof (lineCopy));
    if (parseLine (lineCopy, &leftOperand, &operator, &rightOperand) != 0) {
      returnValue = wrap (line, answer, sizeof (answer), PBO_INVALID_INPUT); break;
    }

    operation = selectOperation (operations, count, operator);
    if (operation == NULL) {
      returnValue = wrap (line, answer, sizeof (answer), PBO_UNKNOWN_OPERATOR); break;
    }

    if (operation->operation (leftOperand, rightOperand, answer, sizeof (answer)) != 0) {
      returnValue = wrap (line, answer, sizeof (answer), PBO_OPERATOR_FAILED); break;
    }
  } while (0);

  strncpy (result, answer, len - 1);
  if (strlen (answer) > len - 1) {
    returnValue = PBO_OUTPUT_TRUNCATED;
  }
  return returnValue;
}

int PBO_INVALID_INPUT = 1;
int PBO_UNKNOWN_OPERATOR = 2;
int PBO_OPERATOR_FAILED = 3;
int PBO_OUTPUT_TRUNCATED = 4;

/********************/
/* PUBLIC INTERFACE */
/********************/

int performBinaryOperations (const BinaryOperation* operations, int count, const char* input, char* result, int len) {
  *result = 0;

  if (*input == 0) {return 0;}

  return processLine (operations, count, input, result, len);
}
