#ifndef BINARY_PARSER_H_
#define BINARY_PARSER_H_

typedef struct {
  char* operator;
  char* (*operation) (char* leftOperand, char* rightOperand);
} BinaryOperation;

char* performBinaryOperations (BinaryOperation* operations, char* input);

#endif /* BINARY_PARSER_H_ */
