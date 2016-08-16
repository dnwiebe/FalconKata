
#include <stddef.h>
#include <string.h>
#include "native_arithmetic.h"

#define NA_UNCHANGED 0
#define NA_CHANGED 1
#define NA_ERROR 2

typedef struct {
	char currentDigit;
	int countSoFar;
	char* output;
	int lenRemaining;
	int status;
} DisplayFormState;

int isButOneOptimized (char digit) {
	return (strchr ("IXC", digit) == NULL) ? 0 : 1;
}

void outputMultiple (DisplayFormState* state) {
	int i;

	// TEST: lenRemaining -> 0
	for (i = 0; i < state->countSoFar; i++) {
		*(state->output++) = state->currentDigit;
		state->lenRemaining--;
	}
}

int nextHigherDigitMultiplier (char digit) {
	if (strchr ("MCXI", digit) == NULL) {
		return 2;
	}
	return 5;
}

char nextHigherDigitThan (char digit) {
	// TEST: bad digit
	// TEST: digit M
	char* p = strchr ("IVXLCDM", digit);
	return *(p + 1);
}

int countLimitFor (char digit) {
	if (strchr ("MCXI", digit) == NULL) {
		return 1;
	}
	return 3;
}

void handleCharacterChange (DisplayFormState* state, const char c) {
	int countLimit = countLimitFor (state->currentDigit);
	int nextHigherDigit = nextHigherDigitThan (state->currentDigit);

	if (state->countSoFar <= countLimit) {
		outputMultiple (state);
	}
	else if ((state->countSoFar - countLimit == 1) && isButOneOptimized (state->currentDigit)) {
		*(state->output++) = state->currentDigit;
		// TEST: lenRemaining -> 0
		state->lenRemaining--;
		*(state->output++) = nextHigherDigit;
		// TEST: lenRemaining -> 0
		state->lenRemaining--;
		state->status = NA_CHANGED;
	}
	else {
		*(state->output++) = nextHigherDigit;
		// TEST: lenRemaining -> 0
		state->lenRemaining--;
		state->status = NA_CHANGED;
	}

	*(state->output) = 0;
	state->currentDigit = c;
	state->countSoFar = 1;
}

void handleCharacter (DisplayFormState* state, const char c) {
	if ((c == state->currentDigit) && (state->countSoFar < nextHigherDigitMultiplier (c))) {
		state->countSoFar++;
	}
	else {
		handleCharacterChange (state, c);
	}
}

int toDisplayForm (const char* expandedForm, char* displayForm, int len) {
	DisplayFormState state = {0, 0, displayForm, len, NA_UNCHANGED};
	const char* in = expandedForm;

	while (*in != 0) {
		handleCharacter (&state, *in++);
	}
	handleCharacter (&state, 0);
	if (state.status == NA_CHANGED) {
		char result[80];
		strncpy (result, displayForm, sizeof (result));
		return toDisplayForm (result, displayForm, len);
	}
	return 0;
}

static const char* SORT_ORDER = "MDCLXVI";
int sortDigits (const char* unsorted, char* sorted, int len) {
	char t;
	char* p;
	char* op;
	char* q;
	char* oq;

	// TEST: strlen (unsorted) > len
	strncpy (sorted, unsorted, len);
	// TEST: strlen (unsorted) == 0
	for (p = sorted; *p != 0; p++) {
		op = strchr (SORT_ORDER, *p);
		// TEST: *op == 0
		for (q = p + 1; *q != 0; q++) {
			oq = strchr (SORT_ORDER, *q);
			// TEST: *oq == 0
			if (op > oq) {
				t = *p;
				*p = *q;
				*q = t;
			}
		}
	}
	return 0;
}

/********************/
/* PUBLIC INTERFACE */
/********************/

int addNative (const char* augend, const char* addend, char* sum, int len) {
	char expandedForm[80];
	char sorted[80];

	strncpy (expandedForm, augend, len);
	strncat (expandedForm, addend, len - strlen (augend));
	sortDigits (expandedForm, sorted, sizeof (sorted));
	toDisplayForm (sorted, sum, len);
	return 0;
}

int subtractNative (const char* minuend, const char* subtrahend, char* difference, int len) {
	return 1;
}
