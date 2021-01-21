#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "csvReader.h"


void onCsvUpdate(CSVFILE *file){
    printf("field m: %lf\n", file->GetField(file, "m"));
}

int main(void){
    CSVFILE file;

    // not exist file
    printf("Demo1: open file which is not exist.\n");
    if(!csvOpen(&file, "test_not_exist.csv")){
        printf("File not exist\n\n");
    }

    // 
    int i;
    printf("Demo2: use csvOpen and csvReadLine.\n");
    if(csvOpen(&file, "./sample.csv")){
        printf("colSize: %d\n", file.colSize);
        printf("Header: ");
        for(i = 0; i < file.colSize; i++){
            printf("%s, ", file.headers[i]);
        }
        printf("\n");

        while(csvReadLine(&file)){
            printf("field c: %lf\n", file.GetField(&file, "c"));
        }
        printf("\n\n");
    }

    // test with callback
    printf("Demo3: use csvReadCallback.\n");
    csvReadCallback("./sample.csv", onCsvUpdate);

    return 0;
}