#include <stddef.h>
#include <string.h>
#include <regex.h>
#include "binary_parser.h"


const char* nextLine (const char* remainingInput, char* line, int len) {
  const char* in = remainingInput;
  char* out = line;
  while ((*in != '\n') && (*in != 0) && ((out - line) < len - 1)) {
    *out++ = *in++;
  }
  *out = 0;
  return (*in == '\n') ? in + 1 : in;
}

regex_t LINE_PARSER;
int LINE_PARSER_COMPILED = 0;
void initializeLINE_PARSERIfNecessary () {
  if (LINE_PARSER_COMPILED) {return;}
  regcomp (&LINE_PARSER, "^\\s*([^ ]+)\\s+([^ ]+)\\s+([^ ]+)\\s*$", REG_EXTENDED);
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

  int result = regexec (&LINE_PARSER, line, 4, matches, 0);
  if (result != 0) {return result;}

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

int strncatWithNewline (char* dest, int len, const char* src) {
  int lenWithTerm = len - 1;
  int resultLeft = lenWithTerm - strlen (dest);
  strncat (dest, src, resultLeft);
  resultLeft = lenWithTerm - strlen (dest);
  if (resultLeft <= 0) {
    return 1;
  }
  resultLeft = lenWithTerm - strlen (dest);
  if (resultLeft <= 0) {
    return 1;
  }
  strncat (dest, "\n", 1);
  return 0;
}

int PBO_INVALID_INPUT = 1;
int PBO_UNKNOWN_OPERATOR = 2;
int PBO_OPERATOR_FAILED = 3;
int PBO_OUTPUT_TRUNCATED = 4;

int performBinaryOperations (const BinaryOperation* operations, int count, const char* input, char* result, int len) {
  const char* remainingInput = input;
  char line[80];
  char lineCopy[80];
  char* leftOperand;
  char* operator;
  char* rightOperand;
  char answer[80];
  int status;
  int returnValue = 0;
  const BinaryOperation* operation;

  while ((*remainingInput != 0) && (strlen (result) < len - 1)) {
    remainingInput = nextLine (remainingInput, line, sizeof (line));

    strncpy (lineCopy, line, sizeof (lineCopy));
    status = parseLine (lineCopy, &leftOperand, &operator, &rightOperand);
    if (status != 0) {
      strncpy (answer, line, sizeof (answer));
      returnValue = PBO_INVALID_INPUT;
    }
    else {
      operation = selectOperation (operations, count, operator);
      if (operation == NULL) {
        strncpy (answer, line, sizeof (answer));
        returnValue = PBO_UNKNOWN_OPERATOR;
      }
      else {
        if (operation->operation (leftOperand, rightOperand, answer, sizeof (answer)) != 0) {
          strncpy (answer, line, sizeof (answer));
          returnValue = PBO_OPERATOR_FAILED;
        }
      }
    }
    status = strncatWithNewline (result, len, answer);
    if (status != 0) {
      returnValue = PBO_OUTPUT_TRUNCATED;
    }
  }
  return returnValue;
}
