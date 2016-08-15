#ifndef BINARY_PARSER_H_
#define BINARY_PARSER_H_

typedef struct {
  const char* operator;
  int (*operation) (const char* leftOperand, const char* rightOperand, char* result, int len);
} BinaryOperation;

int performBinaryOperations (const BinaryOperation* operations, int count, const char* input, char* result, int len);

#define PBO_INVALID_INPUT 1
#define PBO_UNKNOWN_OPERATOR 2
#define PBO_OPERATOR_FAILED 3
#define PBO_OUTPUT_TRUNCATED 4

#endif /* BINARY_PARSER_H_ */
