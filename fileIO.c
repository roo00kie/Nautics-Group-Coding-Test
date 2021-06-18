#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"

void createInputFile(uint16_t size, uint8_t* dataStream){
    FILE *filePtr = fopen("dataSets.txt", "w");
    for(int i=0;i<size;i++){
        dataStream[i] = rand();
        printf("%d ", dataStream[i]);
        fprintf(filePtr, "%d ", dataStream[i]);
    }
    fclose(filePtr);
    printf("\r\ndata generated.\r\n");
}


