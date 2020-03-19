#ifndef MEM
#include <stdio.h>
#include <stdlib.h>

size_t __SIZE = 0;
void **__TAB_MEM = NULL;

#define ACHECK(op) do { if ((op) == NULL) fprintf(stderr, "%s\n", #op); } while (0)

#define _calloc(a,b) \
({ \
        __SIZE+=1;\
	ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*))); \
        ACHECK(__TAB_MEM[__SIZE-1] = calloc(a,b)); \
	printf("%p\n", __TAB_MEM[__SIZE-1]); \
        __TAB_MEM[__SIZE-1]; \
})


#define _malloc(a) \
({ \
        __SIZE+=1; \
        ACHECK(__TAB_MEM = realloc(__TAB_MEM, __SIZE * sizeof(void*))); \
        ACHECK(__TAB_MEM[__SIZE-1] = malloc(a)); \
	printf("%p\n", __TAB_MEM[__SIZE-1]);\
        __TAB_MEM[__SIZE-1]; \
})

#define _free() \
({ \
        for (unsigned long long i = 0; i < __SIZE; i++) \
        { \
                free(__TAB_MEM[i]); \
        } \
        free (__TAB_MEM); \
})

#endif
