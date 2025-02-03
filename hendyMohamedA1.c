#include "givenA1.h"
#include "helper.h"

// Helper Functions

float euclidianDistanceFunc (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]) {
    float EDsum = 0.0;
    for (int i = 0; i < NUM_FEATURES; i++) {
       EDsum += pow(vector1[i] - vector2[i], 2);
    }
    return sqrt(EDsum);
}

int hammingDistanceFunc (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]) {
    int numOfDiff = 0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] != vector2[i]) {
            numOfDiff++;
        }
    }
    return numOfDiff;
}

float jaccardDistanceFunc (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]) {
    float numSame0 = 0;
    float numSame1 = 0;
    float jaccardSim = 0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] == 1 && vector2[i] == 1) {
            numSame1++;
        }
        if (vector1[i] == 0 && vector2[i] == 0) {
            numSame0++;
        }
    }
    int denom = (NUM_FEATURES - numSame0);
    if (denom == 0) {
        jaccardSim = 0.0;
    }
    else {
        jaccardSim = numSame1 / denom;
    }
    
    return jaccardSim;
}

void sortAnArray(distanceIndex array[], int whichDistanceFunc) {
    int step, j;
    distanceIndex key;
    for (step = 1; step < NUM_SAMPLES; step++) {
        key = array[step];
        j = step - 1;
        
        if (whichDistanceFunc == 1 || whichDistanceFunc == 2) {
            while (j >= 0 && key.distance < array[j].distance) {
                array[j + 1] = array[j];
                j--;
            }
        }
        else if (whichDistanceFunc == 3) {
            while (j >= 0 && key.distance > array[j].distance) {
                array[j + 1] = array[j];
                j--;
            }
        }
        
        array[j + 1] = key;
    }
}

int readCSV(char fname[30], struct Animal testData[NUM_TEST_DATA]) {
    FILE * fptr;
    fptr = fopen(fname, "r");

    if (fptr == NULL) {
        printf("Could not open file.");
        return -1;
    }

    for (int i = 0; i < NUM_TEST_DATA; i++) {
        fscanf(fptr, "%[^,],", testData[i].animalName);

        for (int j = 0; j < NUM_FEATURES; i++) {
            fscanf(fptr, "%d,", &testData[i].features[j]);
        }

        fscanf(fptr, "%d", &testData[i].classLabel);
    }

    fclose(fptr);
    return 1;
}

// Task 1
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]) {
    // Declare variable of type FILE *
    FILE * fptr;
    // open file using file pointer variable in "r" (read mode)
    fptr = fopen(fName, "r");

    // check if file is null or not and return -1 if unsuccessful operation
    if (fptr == NULL) {
        printf("Could not open file.");
        return -1;
    }

    // use for loop to read through file and populate struct array
    for (int i = 0; i < NUM_SAMPLES; i++) {
        fscanf(fptr, "%49s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
                                                                                dataZoo[i].animalName, 
                                                                                &dataZoo[i].features[0], &dataZoo[i].features[1], 
                                                                                &dataZoo[i].features[2], &dataZoo[i].features[3], 
                                                                                &dataZoo[i].features[4], &dataZoo[i].features[5], 
                                                                                &dataZoo[i].features[6], &dataZoo[i].features[7], 
                                                                                &dataZoo[i].features[8], &dataZoo[i].features[9], 
                                                                                &dataZoo[i].features[10], &dataZoo[i].features[11], 
                                                                                &dataZoo[i].features[12], &dataZoo[i].features[13], 
                                                                                &dataZoo[i].features[14], &dataZoo[i].features[15], 
                                                                                &dataZoo[i].classLabel);
    }

    // close the file and return 1 for successful operation
    fclose(fptr);
    return 1;
}

void distanceFunctions (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES], float * euclideanDistance, int * hammingDistance, float * jaccardSimilarity) {

    // here we calculate Euclidean distance 
    *euclideanDistance = euclidianDistanceFunc(vector1, vector2);
    // here we calculate Hamming distance 
    *hammingDistance =  hammingDistanceFunc(vector1, vector2);
    // here we calculate Jaccard Similarity
    *jaccardSimilarity = jaccardDistanceFunc(vector1, vector2);
}

void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]) {

    distanceIndex distances [NUM_SAMPLES];

    for (int i = 0; i < NUM_SAMPLES; i++) {
        float distance = 0;

        if (whichDistanceFunction == 1) {
            distance = euclidianDistanceFunc(newSample, dataZoo[i].features);
        }
        else if (whichDistanceFunction == 2) {
            distance = hammingDistanceFunc(newSample, dataZoo[i].features);
        }
        else if (whichDistanceFunction == 3) {
            distance = jaccardDistanceFunc(newSample, dataZoo[i].features);
        }

        distances[i].distance = distance;
        distances[i].index = i;
    }

    // DEBUG
    // for (int i = 0; i < NUM_SAMPLES; i++) {
    //     printf("Index: %d, Distance: %.4f\n", distances[i].index, distances[i].distance);
    // }

    sortAnArray(distances, whichDistanceFunction);

    for (int i = 0; i < k; i++) {
        kNearestNeighbors[i] = distances[i].index;
    }
}

int predictClass (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int whichDistanceFunction, int k) {

    int kNearestNeighbors [NUM_SAMPLES];
    int classCount [NUM_CLASSES] = {0, 0, 0, 0, 0, 0, 0};

    findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);

    // for (int i = 0; i < k; i++) {
    //     printf("k-nearest neighbors: %d \n", kNearestNeighbors[i]);
    // }
    // printf("\n");

    // Count occurrences of each class label
    
    for (int i = 0; i < k; i++) {
        int indexNeighbor = kNearestNeighbors[i];
        int classLabel = dataZoo[indexNeighbor].classLabel;
        // printf("Neighbor %d has class %d\n", indexNeighbor, classLabel);
        if (classLabel >= 1 && classLabel <= NUM_CLASSES) {
            classCount[classLabel - 1]++;
        }   
    }

    // Find most frequent class (break ties by choosing smallest class)
    int max = 0, predictedClass = 1;
    for (int i = 0; i < NUM_CLASSES; i++) {
        // printf("Class %d has count %d\n", i, classCount[i]);
        if (classCount[i] > max) {
            max = classCount[i];
            predictedClass = i + 1;
        }
        else if (classCount[i] == max && (i + 1) < predictedClass) {
            predictedClass = i + 1;
        }
    }


    return predictedClass;
}

float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], int whichDistanceFunction, struct Animal testData [NUM_TEST_DATA], int k) {
    int rightPreds = 0;
    float accuracy = 0;

    for (int i = 0; i < NUM_TEST_DATA; i++) {
        int predictedClass = predictClass(dataZoo, testData[i].features, whichDistanceFunction, k);
        if (predictedClass == testData[i].classLabel) {
            rightPreds++;
        }
    }

    accuracy = ((float)rightPreds / NUM_TEST_DATA) * 100.0;
    return accuracy;
}