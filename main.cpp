#include "C:\Users\suhan\Coding_Projects\Machine_Learning\LinearAlgebraFramework\matrix.h"
#include <stdlib.h>

typedef struct {
    int output;
    float dist;
} knnStruct;

float euclideanDist(float * arr1, float * arr2);
void swap(knnStruct * knn1, knnStruct * knn2);

int main(int argc, char ** argv) {

    int k = 5;
    float * testCase = (float *)malloc(sizeof(float) * 8);

    for (int i = 0; i < 8; i++) {
        testCase[i] = atof(argv[i + 1]);
    }

    Matrix dataSet(769, 8);
    knnStruct * array = (knnStruct *)malloc(sizeof(knnStruct) * 769);
    if (!array) {
        fprintf(stderr, "Memory allocation failed\n");
        free(testCase);
        return 1;
    }

    FILE * file = fopen(R"(C:\Users\suhan\Coding_Projects\Machine_Learning\Models\KNN\diabetes.csv)", "r");

    for (int i = 0; i < 769; i++) {
        fscanf(file,
        "%f,%f,%f,%f,%f,%f,%f,%f,%d\n",
        &dataSet.MatrixData[i][0],
        &dataSet.MatrixData[i][1],
        &dataSet.MatrixData[i][2],
        &dataSet.MatrixData[i][3],
        &dataSet.MatrixData[i][4],
        &dataSet.MatrixData[i][5],
        &dataSet.MatrixData[i][6],
        &dataSet.MatrixData[i][7],
        &array[i].output);
    }

    fclose(file);

    for (int i = 0; i < 769; i++) {
        array[i].dist = euclideanDist(testCase, dataSet.MatrixData[i]);
    }

    for (int i = 0; i < 768; i++) {
        for (int j = 0; j < 769 - i - 1; j++) {
            if (array[j].dist > array[j + 1].dist) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }

    int numTrue = 0;
    int numFalse = 0;


    for (int i = 0; i < 5; i++) {
        if (array[i].output == 1) {
            numTrue++;
        } else if(array[i].output == 0){
            numFalse++;
        }
    }


    (numTrue > numFalse) ? printf("Diabetes.\n") : printf("No Diabetes.\n");

    free(testCase);
    free(array);

    return 0;
}

float euclideanDist(float * arr1, float * arr2) {
    float dist = 0;
    for (int i = 0; i < 8; i++) {
        dist += pow(arr1[i] - arr2[i], 2);
    }
    return sqrt(dist);
}

void swap(knnStruct * knn1, knnStruct * knn2) {
    knnStruct temp = *knn1;
    *knn1 = *knn2;
    *knn2 = temp;
}
