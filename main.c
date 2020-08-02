#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_PATH_BUFFER_SIZE 255
#define DEBUG false // set to true to see stdout print statements.
// #define DEBUG 0 -> this is equally valid since bool is just {0,1}

void getFullPath(char* filename, char* fullPath, bool debug) {
    /* 
    the passed filename must be less than 
    FILE_PATH_BUFFER_SIZE - len('data/').
    and we're setting the buffer for fullPath 
    to 255 max.
    */
    char* path = "data/";
    strcpy(fullPath, path);
    strcat(fullPath, filename);
    if (debug) {
        printf("path: %s\n", path);
        printf("filename: %s\n", filename);
        printf("full file path: %s\n", fullPath);
    }
}

int getNumGradesInDataFile(FILE* dataFile) {
    /* We know the first line of the file tells us the number of grades. Leverage this.*/
    char line[10];
    fgets(line, 10, dataFile);
    DEBUG && printf("LINE: <%s>", line);
    int numGrades = atoi(line);
    DEBUG && printf("numGrades<%d>\n", numGrades);
    return numGrades;
}

void populateGradeArray(float grades[]) {
    float value; // temp holder for each space-separated value in file
    while (fscanf(dataFile, "%f", &value) == 1) {
        DEBUG && printf("VALUE: %f\n", value);
        
    }
}

float 

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("You're missing a command line argument.\n");
        printf("Specify a filename in the data/ directory containing grades.\n");
    } else {

        char fullPath[FILE_PATH_BUFFER_SIZE];
        getFullPath(argv[1], fullPath, DEBUG);
        FILE* dataFile = fopen(fullPath, "r");
        
        if (dataFile == NULL) {
            printf("There was an error with your file!\n");
            exit(1);
        }

        // create an array only as big as you need.
        float grades[getNumGradesInDataFile(dataFile)]; 
        populateGradeArray(grades);

    }

    return 0;
}