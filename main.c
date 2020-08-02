#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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
    DEBUG && printf("LINE: %s", line);
    int numGrades = atoi(line);
    DEBUG && printf("numGrades: %d\n", numGrades);
    return numGrades;
}

void populateGradeArray(double grades[], FILE* dataFile) {
    double value; // temp holder for each space-separated value in file
    int i = 0;
    while (fscanf(dataFile, "%lf", &value) == 1) {
        grades[i] = value;
        DEBUG && printf("VALUE: %f\n", value);
        i++;
    }
}

double calculateClassAverage(double grades[], int numGrades){
    double average = 0.0;
    for (int i = 0; i < numGrades; i++) {
        // printf("ADDING: %.5f\n",grades[i]);
        average += grades[i];
    }
    average /= (float)numGrades;
    return average;
}

double calculateClassMinimum(double grades[], int numGrades) {
    double min = 1000.0; // it is impossible to obtain, so this is effectively +inf
    for (int i = 0; i < numGrades; i++) {
        if (grades[i] < min) {
            min = grades[i];
        }
    }
    return min;
}

double calculateClassMaximum(double grades[], int numGrades) {
    double max = -1.0; // it is impossible to obtain, so this is effectively -inf
    for (int i = 0; i < numGrades; i++) {
        if (grades[i] > max) {
            max = grades[i];
        }
    }
    return max;
}

double calculateClassStdDev(double grades[], int numGrades, double average) {
    double numerator = 0.0;
    for (int i = 0; i < numGrades; i++) {
        numerator += pow((grades[i] - average), 2);
    }
    return sqrt(numerator / (float)numGrades); // use them maths skills boi
}

void printOutput(int numGrades, double outputs[]) {
    // printf("\n");
    printf("\nThere are %d students in the class.\n\n", numGrades);
    printf("stats:\n%s\n", "-------------------------------------");
    printf("average%30.2f\n", outputs[0]);
    printf("min%34.2f\n", outputs[1]);
    printf("max%34.2f\n", outputs[2]);
    printf("std. dev.%28.2f\n", outputs[3]);
    printf("%s\n\n", "-------------------------------------");
}

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
        int numGrades = getNumGradesInDataFile(dataFile);
        double grades[numGrades];
        // double * grades;
        // grades = (double *) malloc(numGrades);
        populateGradeArray(grades, dataFile);
        double classAverage = calculateClassAverage(grades, numGrades);
        DEBUG && printf("classAverage: %.2f\n", classAverage);
        double classMin = calculateClassMinimum(grades, numGrades);
        DEBUG && printf("classMin: %.2f\n", classMin);
        double classMax = calculateClassMaximum(grades, numGrades);
        DEBUG && printf("classMax: %.2f\n", classMax);
        double classStdDev = calculateClassStdDev(grades, numGrades, classAverage);
        DEBUG && printf("classStdDev: %.2f\n", classStdDev);
        double outputArray[4] = {classAverage, classMin, classMax, classStdDev};
        printOutput(numGrades, outputArray);
        // free(grades);
    }

    return 0;
}