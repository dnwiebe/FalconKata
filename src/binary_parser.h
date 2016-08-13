#ifndef BINARY_PARSER_H_
#define BINARY_PARSER_H_

typedef struct {
  const char* operator;
  int (*operation) (const char* leftOperand, const char* rightOperand, char* result, int len);
} BinaryOperation;

int performBinaryOperations (const BinaryOperation* operations, int count, const char* input, char* result, int len);

#endif /* BINARY_PARSER_H_ */
