#include <stdio.h>
#include "25001002_mymalloc.h"

void printBlocks(void);

int main(){
    //allocations
    char*a = MyMalloc(50);
    char*b = MyMalloc(300);
    
    printf("\n======Memory=====\n");
    printBlocks();

    printf("\nfreeing a block\n");
    MyFree(b);

    printf("\n======Memory=====\n");
    printBlocks();

    return 0;
}