#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define FILE_PATH_BUFFER_SIZE 255

void getFullPath(char* filename, char* fullPath) {
    /* Ensure filename doesn't exceed set buffer - length of fullPath */
    char* path = "data/";
    strcpy(fullPath, path);
    strcat(fullPath, filename);
}

int getNumGradesInDataFile(FILE* dataFile) {
    char line[10];
    fgets(line, 10, dataFile);
    int numGrades = atoi(line);
    return numGrades;
}

void populateGradeArray(double grades[], FILE* dataFile) {
    double value; // temp holder for each space-separated value in file
    int i = 0;
    while (fscanf(dataFile, "%lf", &value) == 1) {
        grades[i] = value;
        i++;
    }
}

void calculateStatistics(double grades[], int numGrades, double* min, double* max, double* average, double* stdDev) {
    double numerator = 0.0;
    for (int i = 0; i < numGrades; i++) {
        if (grades[i] < *min) *min = grades[i];
        if (grades[i] > *max) *max = grades[i];
        *average += grades[i];
    }
    *average /= (float)numGrades;
    for (int i = 0; i < numGrades; i++) {
        numerator += pow((grades[i] - *average), 2);
    }
    *stdDev = sqrt(numerator / (float)numGrades);
}

void printOutput(int numGrades, double outputs[]) {
    printf("\nThere are %d students in the class.\n\n", numGrades);
    printf("stats:\n%s\n", "-------------------------------------");
    printf("average%30.2f\n", outputs[0]);
    printf("min%34.2f\n", outputs[1]);
    printf("max%34.2f\n", outputs[2]);
    printf("std. dev.%28.2f\n", outputs[3]);
    printf("%s\n\n", "-------------------------------------");
}

void missingArgumentException() {
    printf("You're missing a command line argument.\n");
    printf("Specify a filename in the data/ directory containing grades.\n");
}

void badFileException() {
    printf("There was an error with your file!\n");
    exit(1);
}

void processStudentData(char* filename) {
    char fullPath[FILE_PATH_BUFFER_SIZE];
    getFullPath(filename, fullPath);
    FILE* dataFile = fopen(fullPath, "r");
    if (dataFile == NULL) badFileException();
    int numGrades = getNumGradesInDataFile(dataFile);
    double classMin = 1000.0;
    double classMax = -1.0;
    double classAverage = 0.0;
    double classStdDev = 0.0;
    double *grades = (double *) malloc(numGrades * sizeof(double));
    populateGradeArray(grades, dataFile);
    calculateStatistics(grades, numGrades, &classMin, &classMax, &classAverage, &classStdDev);
    double outputArray[4] = {classAverage, classMin, classMax, classStdDev};
    printOutput(numGrades, outputArray);
    free(grades); // no mem leaks :)
}

int main(int argc, char* argv[]) {
    if (argc < 2) missingArgumentException();
    else processStudentData(argv[1]);
    return 0;
}