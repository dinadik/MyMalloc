#ifndef MYMALLOC_H // checks if macro "MYMALLOC_H" is defined. 
#define MYMALLOC_H // Only includes if not defined in prgram, preventing double inclusion

#include <stddef.h> // standard lightweight library that has definitions (eg: size_t, NULL). it doesn't have functions 

//Prototypes of our functions
void* MyMalloc(size_t size);
void MyFree(void *ptr);


#endif