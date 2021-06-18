#include "dataHandling.h"
#include <stdio.h>
#include <stdlib.h>

compressedData_t dataHandling_dataC;

static void dataCompress_Init(uint16_t size){
    dataHandling_dataC.data = calloc( size, sizeof( uint8_t ) );
    dataHandling_dataC.data_len = 0;
    dataHandling_dataC.duplicateCount = calloc( size, sizeof( uint16_t ) );
    dataHandling_dataC.duplicateCount_len = 0;
}

static void dataCompress_deInit(void){
    free(dataHandling_dataC.data);
    free(dataHandling_dataC.duplicateCount);
}

void dataCompress(uint8_t *inputData, uint16_t size){
    uint8_t duplicateFlag = 0;
    dataCompress_Init(size);
    printf("Data compressed.\r\n");
    for(uint32_t i=0;i<size;i++){
        inputData[i] &= 0x7F;
        if(i == 0){
            dataHandling_dataC.data[i] = inputData[i];
            dataHandling_dataC.data_len++;
        }
        else{
            if(inputData[i] == (dataHandling_dataC.data[dataHandling_dataC.data_len-1] & 0x7F)){ // if duplicate
                dataHandling_dataC.data[dataHandling_dataC.data_len-1] |=0x80; // set output data MSB to 1
                dataHandling_dataC.duplicateCount[dataHandling_dataC.duplicateCount_len]++;
                duplicateFlag = 1;
            }
            else{
                dataHandling_dataC.data[dataHandling_dataC.data_len] = inputData[i];
                dataHandling_dataC.data_len++;
                if(duplicateFlag == 1) dataHandling_dataC.duplicateCount_len++;
                duplicateFlag = 0;
            }
        }
    }

    /*******data pressed printout*********/
    printf("data recorded: %d\r\n", dataHandling_dataC.data_len);
    for(int i=0;i<dataHandling_dataC.data_len;i++) printf("0x%X ", dataHandling_dataC.data[i]);
    //printf("\r\ncompressed data: %d\r\n", dataHandling_dataC.duplicateCount_len);
    //for(int i =0;i<dataHandling_dataC.duplicateCount_len;i++) printf("0x%X ", dataHandling_dataC.duplicateCount[i]);

}

void dataRestore(uint16_t size){
    printf("\r\nRegenerate data.\r\n");
    uint8_t *dataRestored = calloc( size, sizeof( uint8_t ) );
    int outputCount = 0;
    int inputCount = 0;
    int outputDuplicateCount = 0;
    while(outputCount<size){
        dataRestored[outputCount] = dataHandling_dataC.data[inputCount];
        outputCount++;
        if((dataRestored[outputCount-1] &0x80) == 0x80){ // duplicate happened
            dataRestored[outputCount-1] &= 0x7F;
            int count = dataHandling_dataC.duplicateCount[outputDuplicateCount];
            for(int j=0;j<count;j++){
                dataRestored[outputCount] = dataHandling_dataC.data[inputCount]&0x7F;
                outputCount++;
            }
            outputDuplicateCount++;
        }
        inputCount++;

    }
    /******data restored printout*****/
    for(int i=0;i<size;i++) printf("0x%X ",dataRestored[i]);
    free(dataRestored);
    dataCompress_deInit();
}
