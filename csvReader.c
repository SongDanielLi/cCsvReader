#include "csvReader.h"
#include <string.h>
#include <unistd.h>

static double csvGetField(struct CsvFileMems *csvFile, const char *field){
    int i = 0;
    double val = 0;
    for(i = 0; i < csvFile->colSize; i++){
        if(strcmp(field, csvFile->headers[i]) == 0){
            val = csvFile->dataRow[i];
            break;
        }
    }
    return val;
}

static bool scanHeader(CSVFILE *csvFile){
    char line[512];
    const char *tok;
    if(fgets(line, 512, csvFile->file) != NULL){
        // split(buf, ",", csvFile->headers, &csvFile->colSize);
        csvFile->colSize = 0;
        for (tok = strtok(line, ","); tok && *tok; csvFile->colSize++, tok = strtok(NULL, ",\n\r")){
            csvFile->headers[csvFile->colSize] = strdup(tok);
        }

        csvFile->dataRow = (double *)calloc(csvFile->colSize, sizeof(double));
        return true;
    }
    return false;
}

static bool readOneLine(CSVFILE *csvFile){
    char line[512];
    if(fgets(line, 512, csvFile->file) == NULL) return false;

    const char *tok;
    int i = 0;
    for (tok = strtok(line, ","); tok && *tok; i++, tok = strtok(NULL, ",\n")){
        csvFile->dataRow[i] = strtod(tok, NULL);
    }
    return true;
}

bool csvOpen(CSVFILE *csvFile, const char *filename){
    // check exist
    if(access(filename, F_OK) != 0) return false;

    memset(csvFile, 0x00, sizeof(CSVFILE));
    csvFile->GetField = csvGetField;
    csvFile->file = fopen(filename, "r");

    return scanHeader(csvFile);
}

bool csvReadLine(CSVFILE *csvFile){
    if(readOneLine(csvFile)){
        return true;
    }

    fclose(csvFile->file);
    return false;
}

void csvReadCallback(const char *filename, CsvRowUpdate callback){
    CSVFILE csvFile;
    if(csvOpen(&csvFile, filename)){
        while(csvReadLine(&csvFile)){
            callback(&csvFile);
        }
    }
}