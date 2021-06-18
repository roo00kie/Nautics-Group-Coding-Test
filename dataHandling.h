#ifndef DATAHANDLING_H
#define DATAHANDLING_H
#include <stdint.h>

typedef struct{
    uint8_t *data;
    uint16_t data_len;
    uint16_t *duplicateCount;
    uint16_t duplicateCount_len;
}compressedData_t;

void dataCompress(uint8_t *inputData, uint16_t size);

void dataRestore(uint16_t size);

#endif // DATAHANDLING_H
