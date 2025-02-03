#define NUM_FEATURES 16   // not including animal name and class label
#define NUM_SAMPLES 100      // total number of samples / rows in the given zoo dataset
#define NUM_CLASSES 7        // total number of class labels in zoo dataset
#define NUM_TEST_DATA 20     // total number of samples / rows in the test dataset - you need this for task 5
#define MAX_LENGTH_ANIMAL_NAME 50

typedef struct Distance {
    float distance;
    int index;
} distanceIndex;

float euclidianDistanceFunc (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]);

int hammingDistanceFunc (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]);

float jaccardDistanceFunc (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]);

void sortAnArray(distanceIndex array[], int whichDistanceFunc);

int readCSV(char fname[30], struct Animal testData[NUM_TEST_DATA]);