#include <stddef.h>
#include <string.h>
#include <regex.h>
#include "binary_parser.h"


const char* nextLine (const char* remainingInput, char* line, int len) {
  const char* p = remainingInput;
  char* q = line;
  while ((*p != '\n') && (*p != 0) && ((q - line) < len)) {
    *q++ = *p++;
  }
  *q = 0;
  return (*p == '\n') ? p + 1 : p;
}

regex_t LINE_PARSER;
int LINE_PARSER_COMPILED = 0;
void initializeLINE_PARSERIfNecessary () {
  if (LINE_PARSER_COMPILED) {return;}
  int result = regcomp (&LINE_PARSER, "^\\s*([^ ]+)\\s+([^ ]+)\\s+([^ ]+)\\s*$", REG_EXTENDED);
  LINE_PARSER_COMPILED = 1;
}

char* matchedSubstring (const regmatch_t* match, char* line) {
  char* result = line + match->rm_so;
  *(line + match->rm_eo) = 0;
  return result;
}

int parseLine (char* line, char** leftOperand, char** operator, char** rightOperand) {
  regmatch_t matches[4];
  initializeLINE_PARSERIfNecessary ();

  // Test for non-matching regex
  int result = regexec (&LINE_PARSER, line, 4, matches, 0);
  char msg[240];
  regerror (result, &LINE_PARSER, msg, sizeof (msg));

  *leftOperand = matchedSubstring (&matches[1], line);
  *operator = matchedSubstring (&matches[2], line);
  *rightOperand = matchedSubstring (&matches[3], line);

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

int performBinaryOperations (const BinaryOperation* operations, int count, const char* input, char* result, int len) {
  const char* remainingInput = input;
  char* output = result;
  char line[80];
  char* leftOperand;
  char* operator;
  char* rightOperand;

  // add test for input overrun
  // add test for output overrun
  while (*remainingInput != 0) {
    // Need test for input ending with \n
    // Need test for input ending with other than \n
    remainingInput = nextLine (remainingInput, line, sizeof (line));

    // Need lots of tests for invalid input
    parseLine (line, &leftOperand, &operator, &rightOperand);

    // Need test for unknown operator
    const BinaryOperation* operation = selectOperation (operations, count, operator);

    // Need test for operation failure
    operation->operation (leftOperand, rightOperand, output, len - (output - result));
    output = result + strlen(result);
    // Need test for output overrunning result
    *output++ = '\n';
  }
  return 0;
}
