#ifndef MEM
#define MEM
#include <stdio.h>
#include <stdlib.h>

unsigned long long __SIZE = 1;
void **__TAB_MEM = NULL;
char FREE_ALL = 0;

#define ACHECK(op) do { if ((op) == NULL) fprintf(stderr, "%s\n", #op); } while (0)

#define calloc(a,b)\
({\
	if (__SIZE == 1)\
	{\
		ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*)));\
		__TAB_MEM[0] = __TAB_MEM;\
	}\
        __SIZE+=1;\
	ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*)));\
        ACHECK(__TAB_MEM[__SIZE-1] = calloc(a,b));\
        __TAB_MEM[__SIZE-1];\
})


#define malloc(a)\
({\
	if (__SIZE == 1)\
	{\
		ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*)));\
		__TAB_MEM[0] = __TAB_MEM;\
	}\
        __SIZE+=1;\
        ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*)));\
        ACHECK(__TAB_MEM[__SIZE-1] = malloc(a));\
        __TAB_MEM[__SIZE-1];\
})


#define realloc(a,b)\
({\
	unsigned long long pos = 0;\
	if ( a == NULL || a == __TAB_MEM[0] )\
	{\
		ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*)));\
		__TAB_MEM[0] = __TAB_MEM;\
	}\
	else\
	{\
		unsigned long long i = 0;\
		for (i = 0; i < __SIZE; i++)\
			if (__TAB_MEM[i] == a)\
			break;\
		if ( i == __SIZE)\
		{\
			__SIZE+=1;\
			ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*)));\
			pos = __SIZE-1;\
		}\
		else\
			pos = i;\
		ACHECK(__TAB_MEM[pos] = realloc(a, b));\
	}\
	__TAB_MEM[pos];\
})

#define free_all()\
({\
        for (unsigned long long i = 1; i < __SIZE; i++)\
                if (__TAB_MEM[i] != NULL)\
                { \
                        FREE_ALL = 1;\
                	free(__TAB_MEM[i]); \
                }\
        free (__TAB_MEM[0]); \
        FREE_ALL = 0; \
})

#define free(a)\
({\
        if (FREE_ALL == 1)\
                free(a);\
        else\
        {\
                for (unsigned long long i = 1; i < __SIZE; i++) \
                if (__TAB_MEM[i] == a) \
                {\
                        free(__TAB_MEM[i]); \
                        __TAB_MEM[i] = NULL; \
                }\
        }\
})

#endif
