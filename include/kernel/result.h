#ifndef EDOS_RESULT_H
#define EDOS_RESULT_H

enum result {
	RES_OK = 0,
	RES_INVALID_ARG,
	RES_TRUNCATED,

	__RES_COUNT /* KEEP THIS AS THE LAST ELEMENT */
};

typedef enum result result_t;

const char *result_string(result_t res);
#endif
