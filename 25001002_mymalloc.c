#include "25001002_mymalloc.h"
#include <stdio.h> // alot of functions printf, file handling, etc

#define MEMORY_SIZE 25000

// char array so, we have 1 byte segments
// static means only visible inside this file 
// _Alignas(8) makes array start on multiples of 8
static _Alignas(8) char memory[MEMORY_SIZE];

struct block{
    size_t size;
    int free;
    struct block* next;
};

#define HEADER_SIZE  sizeof(struct block)

// helper functions should be static 
// keeps every header aligned
static size_t roundUp8(size_t size){
    if(size % 8 != 0){
        size_t mult = (size / 8) + 1;
        return 8 * mult;
    }
    return size;
}
//setting up first big free block
static void initialise(void){
    struct block *first = (struct block*) memory;
    //memory is not set up; arrays are initialized to 0 by default
    if(first->size == 0){
        first->size = MEMORY_SIZE - HEADER_SIZE;
        first->free = 1;
        first->next = NULL;
    }
}

void* MyMalloc(size_t size){
 if(size == 0 || size > (MEMORY_SIZE-HEADER_SIZE)){
    return NULL;
 }
 initialise();
 size = roundUp8(size);
 struct block* curr = (struct block*) memory;
 while(curr != NULL){

    if ((curr->free == 1) && (curr->size >= size)) {

        //pointer to new header only if there leftover space
        if(curr->size >= (size+HEADER_SIZE+8)){
            struct block* new = (struct block*)((char *)curr + HEADER_SIZE + size);
            new->size = curr->size - size - HEADER_SIZE;
            new->free = 1;
            new->next = curr->next;

            curr->size = size;
            curr->next = new;
        }

        //update curr header
        curr->free = 0;
        
        return (char*)curr + HEADER_SIZE;
    }
    curr=curr->next;
 }
return NULL;
}

void MyFree(void* ptr){
    if(ptr == NULL){
        return;
    }
    // check if ptr is valid
    if (((memory + HEADER_SIZE) <= (char*)ptr) && ((char*)ptr < (memory + MEMORY_SIZE))){
        // find header of the requested memory
        struct block* header = (struct block*)((char *)ptr - HEADER_SIZE);
        if(header->free == 1){
            // already free
            return;
        }
        header->free = 1;
        // comparing adjacent segements and merging if necessary (loop doesnt go to last segment)
        struct block* curr = (struct block*) memory;
        while((curr != NULL) && (curr->next != NULL)){
            if(curr->free == 1 && curr->next->free == 1){
                curr->size += HEADER_SIZE + curr->next->size;
                curr->next = curr->next->next;
                //curr doesnt move 
            }
            else{
                //if not merging looping through headers
                curr = curr->next;
            }

        }
        
    }
// if ptr is not in range 
    else{
        return;
    }
}

//print header blocks
void printBlocks(void){
    initialise();
    struct block* curr = (struct block*)memory;
    while(curr != NULL){
        //subtract to get index instead of real, difficult to read memory address
        long headStart = (char*)curr - memory;
        printf("[%ld] size: %zu ", headStart, curr->size);
        if (curr->free == 1){
            printf("free\n");
        }
        else{
            printf("used\n");
        }
        curr = curr->next;
    }
}