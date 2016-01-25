#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

enum DPAD_DIRECTIONS {
	DUP,
	DDOWN,
	DLEFT,
	DRIGHT,

	MAX_DPAD
};

struct classic_input {
	int dpad[MAX_DPAD];
	int select;
	int start;
	int b;
	int a;
};

bool classic_input_handler(void *input);

#endif /* INPUT_H */
