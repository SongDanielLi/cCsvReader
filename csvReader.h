#ifndef CSVREADER_H 
#define CSVREADER_H 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CSV_HEADER  50

typedef struct CsvFileMems{
    FILE *file;
    int colSize;
    double *dataRow;
    char *headers[MAX_CSV_HEADER];

    double (*GetField)(struct CsvFileMems *csv, const char *field);
} CSVFILE;


/**
 * @brief open csv file, return true if file exists.
 * @param csvFile: CSVFILE struct.
 * @param filename: filename
 * @retval bool
 */ 
bool csvOpen(CSVFILE *csvFile, const char *filename);

/**
 * @brief read csv line by line.
 * if return true, you can get the whole array or get the data by header.
 * 
 * @sample
 * CSVFILE file;
 * if(csvOpen(&file, filename)){
 *      while(csvReadLine(&file)){
 *          // do something...
 *      }
 * }
 */ 
bool csvReadLine(CSVFILE *csvFile);


typedef void(*CsvRowUpdate)(CSVFILE *csvFile);
/**
 * @brief use a callback function to handle the data update.
 */ 
void csvReadCallback(const char *filename, CsvRowUpdate callback);


#endif	// CSVREADER_H
