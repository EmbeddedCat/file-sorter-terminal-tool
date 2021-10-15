/* mem.h */
#ifndef FILE_SORTER_TERMINAL_TOOL_MEM_H
#define FILE_SORTER_TERMINAL_TOOL_MEM_H

#include <stdlib.h>

#define OUT_OF_MEMORY_ERROR -1

#define ALLOCATE_MEMORY(VAR, SIZE, SIZEOF_TYPE) do {                \
        VAR = calloc(SIZE, SIZEOF_TYPE);                            \
        if (VAR == -1) exit(OUT_OF_MEMORY_ERROR);                   \
    } while(0)

#define REALLOCATE_MEMORY(VAR, NEW_SIZE, SIZEOF_TYPE) do {          \
        VAR = realloc(VAR, NEW_SIZE * SIZEOF_TYPE);                 \
        if (VAR == -1) exit(OUT_OF_MEMORY_ERROR);                   \
    } while(0)

#endif