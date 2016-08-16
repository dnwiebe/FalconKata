
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

static const char* POWERS_OF_TEN = "MCXI";
static const char* MULTIPLES_OF_FIVE = "DLV";
static const char* REVERSE_SORT_ORDER = "IVXLCDM";

int isButOneOptimized (char digit) {
	// TEST: bad digit
	// TEST: digit M
	return (strchr (POWERS_OF_TEN, digit) == NULL) ? 0 : 1;
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
	// TEST: bad digit
	// TEST: digit M
	if (strchr (POWERS_OF_TEN, digit) == NULL) {
		return 2;
	}
	return 5;
}

char nextHigherDigitThan (char digit) {
	// TEST: bad digit
	if (digit == 'M') {return 1;}
	char* p = strchr (REVERSE_SORT_ORDER, digit);
	char next = *(p + 1);
	return next;
}

int countLimitFor (char digit) {
	if (strchr (POWERS_OF_TEN, digit) == NULL) {
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
		op = strchr (REVERSE_SORT_ORDER, *p);
		// TEST: op == NULL
		for (q = p + 1; *q != 0; q++) {
			oq = strchr (REVERSE_SORT_ORDER, *q);
			// TEST: oq == NULL
			if (op < oq) {
				t = *p;
				*p = *q;
				*q = t;
			}
		}
	}
	return 0;
}

int toExpandedForm (const char* unexpandedForm, char* expandedForm, int len) {
	const char* in = unexpandedForm;
	char* out = expandedForm;
	char next;

	// TEST: (out - expandedForm) >= len
	while (*in != 0) {
		next = *(in + 1);
		if ((next != 0) && (next == nextHigherDigitThan (*in))) {
			*out++ = *in; *out++ = *in; *out++ = *in; *out++ = *in;
			in += 2;
		}
		else {
			*out++ = *in++;
		}
	}
	*out = 0;
	return 0;
}

/********************/
/* PUBLIC INTERFACE */
/********************/

int addNative (const char* augend, const char* addend, char* sum, int len) {
	char buf1[80];
	char buf2[80];
	char buf3[80];

	toExpandedForm (augend, buf1, sizeof (buf1));
	toExpandedForm (addend, buf2, sizeof (buf2));
	strncpy (buf3, buf1, len);
	strncat (buf3, buf2, len - strlen (buf2));
	sortDigits (buf3, buf1, sizeof (buf1));
	toDisplayForm (buf1, sum, len);
	return 0;
}

int subtractNative (const char* minuend, const char* subtrahend, char* difference, int len) {
	return 1;
}
