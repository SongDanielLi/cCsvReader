# CSV Reader
read csv file with header in c.

* csv file format:
    - delimeter: ","
    - first row is header text, and the remaining rows are all digit.

## Usage
### read line-by-line
```C
CSVFILE file;
if(csvOpen(&file, "./sample.csv")){
    while(csvReadLine(&file)){
        printf("field c: %lf\n", file.GetField(&file, "c"));
    }
}
```

### read with callback
```C
void onCsvUpdate(CSVFILE *file){
    printf("field m: %lf\n", file->GetField(file, "m"));
}

csvReadCallback("./sample.csv", onCsvUpdate);
```
