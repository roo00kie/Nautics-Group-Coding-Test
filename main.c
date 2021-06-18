#include <stdio.h>
#include <stdlib.h>
#include "dataHandling.h"
#include "fileIO.h"

//#define GENERATE_DATA // generate random data, comment out for create user defined data
#define GENERATE_DATA_SIZE 17

int main()
{
#ifdef GENERATE_DATA
    uint8_t *inputData = calloc( GENERATE_DATA_SIZE, sizeof( uint8_t ) );
    createInputFile(GENERATE_DATA_SIZE, inputData);
#else
    uint8_t inputData[GENERATE_DATA_SIZE] = {0x70,0x71,0x34,0x34,0x34,0x20,0x67,0x15,0x15,0x15,0x15,0x15,0x42,0x53,0x68,0x68,0x68};
#endif // GENERATE_DATA
    dataCompress(inputData, GENERATE_DATA_SIZE);
    dataRestore(GENERATE_DATA_SIZE);

#ifdef GENERATE_DATA
    free(inputData);
#endif // GENERATE_DATA
    printf("\r\n test done.\r\n");
    return 0;
}
