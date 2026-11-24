#include <stdio.h>
#include <stdbool.h>

struct block{
    size_t size;
    int free;
    struct block *next;
};

struct Block{
    unsigned short size;
    bool free;
    struct block *next;
};

// array of char
char buffer[100];

int main(){
//The compiler inserts padding so that every member is aligned to its own size
    size_t headerSize = sizeof(struct block);

// buffer is a char* 
    struct block *p = (struct block*) buffer;
    p->size = 50;
    // rounding to 8 
    if(p->size % 8 != 0){
        size_t mult = (p->size / 8) + 1;
        p->size = 8 * mult;
    }

    p->free = 1;

    struct block *q = (struct block*) (buffer + headerSize + (p->size));
    q->size = 10;
    q->free = 1;

    p->next = q;
    q->next = NULL;


    printf("Block p size: %zu\n", p->size);
    printf("Block q size: %zu\n", q->size);


printf("SIZE OF struct with bool: %zu\n",sizeof(struct Block) );
    return 0;

    
}