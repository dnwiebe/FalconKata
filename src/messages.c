
#include "messages.h"
#include "binary_parser.h"
#include "converters.h"

typedef struct {
  const int status;
  const char* message;
} MessageEntry;

MessageEntry messageEntries[] = {
  {PBO_INVALID_INPUT, "Can't parse into binary-op problem"},
  {PBO_UNKNOWN_OPERATOR, "Unrecognized binary operator"},
  {PBO_OPERATOR_FAILED, "Operation failure"},
  {PBO_OUTPUT_TRUNCATED, "Operation output truncated"},
  {RC_INVALID_ROMAN_NUMERAL, "Invalid Roman numeral"},
  {RC_NUMBER_OUT_OF_RANGE, "Roman numeral out of range"},
  {RC_OUTPUT_OVERRUN, "Conversion output overrun"}
};

/********************/
/* PUBLIC INTERFACE */
/********************/

const char* messageFor (int status) {
	int count;
	int i;

	if (status == 0) {return "Success";}
	count = sizeof (messageEntries) / sizeof (*messageEntries);
	for (i = 0; i < count; i++) {
		if (messageEntries[i].status == status) {
			return messageEntries[i].message;
		}
	}
	return "Unrecognized status";
}
