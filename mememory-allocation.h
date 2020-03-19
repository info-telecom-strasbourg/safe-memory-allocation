#ifndef MEM
#include <stdio.h>
#include <stdlib.h>

size_t __SIZE = 0;
void **__TAB_MEM = NULL;

#define ACHECK(op) do { if ((op) == NULL) fprintf(stderr, "%s\n", #op); } while (0)

#endif
