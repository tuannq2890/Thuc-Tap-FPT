#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool allocate10Bytes(uint8_t *outPtr);

int main()
{
    uint8_t *outPtr = NULL;
    bool isSuccess;

    isSuccess = allocate10Bytes(outPtr);

    if (isSuccess)
    {
        printf("Allocating memory dynamically SUCCESS!");
        *outPtr = 5;
        printf("\nresult: %u", *outPtr);
    }
    else
        printf("Allocating memory dynamically FAILURE!"); 

	free(outPtr);
	
    return 0;
}

bool allocate10Bytes(uint8_t *outPtr)
{
    outPtr = (uint8_t*)malloc(10*sizeof(uint8_t));
    
    return outPtr == NULL ? false : true;
}
