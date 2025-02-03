#include "givenA1.h"
#include "helper.h"

int main (int argc, char * argv[]) {

    int choice = 0;
    int fileLoaded = 0;
    struct Animal dataZoo [NUM_SAMPLES];     
    
    do {
        printf("Here is the menu - enter a number between 1 and 5: \n");
        printf("1. Read from file\n");
        printf("2. Calculate distance\n");
        printf("3. Find nearest neighbors\n");
        printf("4. Predict class\n");
        printf("5. Find accuracy\n");
        printf("6 Exit\n"); 
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                char filename[30];
                strcpy(filename, argv[1]);
                int readFile = readFromFile(filename, dataZoo);

                if (readFile == -1) {
                    printf("File not read properly \n");
                }
                else if (readFile == 1){
                    for(int i = 0; i < NUM_SAMPLES; i++) {

                        printf("%s ", dataZoo[i].animalName);
                        for (int j = 0; j < NUM_FEATURES; j++) {
                            printf("%d ", dataZoo[i].features[j]);
                        }
                        printf("%d \n", dataZoo[i].classLabel);
                    }
                    fileLoaded = 1;
                }
                break;
            case 2:
                float euclidianDistance;
                int hammingDistance;
                float jaccardSimilarity;
                int vector1[NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
                int vector2[NUM_FEATURES] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1};

                distanceFunctions(vector1, vector2, &euclidianDistance, &hammingDistance, &jaccardSimilarity);
                printf("Euclidian Distance: %f\n", euclidianDistance);
                printf("Hamming Distance: %d\n", hammingDistance);
                printf("Jaccard Similarity: %f\n", jaccardSimilarity);
                break;
            case 3:
                if (!fileLoaded) {
                    printf("File not read yet. Please read file from beginning\n");
                    break;
                }
                int newSample [NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1}; 
                int k = 5;
                int whichDistanceFunc [3] = {1, 2, 3};
                int kNearestNeighbors [NUM_SAMPLES];

                for (int i = 0; i < 3; i++) {
                    findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunc[i], kNearestNeighbors);

                    if (whichDistanceFunc[i] == 1) {
                        printf("Nearest neighbors for new sample with Euclidean Distance: ");
                    } else if (whichDistanceFunc[i] == 2) {
                        printf("Nearest neighbors for new sample with Hamming Distance: ");
                    } else if (whichDistanceFunc[i] == 3) {
                        printf("Nearest neighbors for new sample with Jaccard Similarity: ");
                    }

                    for (int j = 0; j < k; j++) {
                        printf("%d ", kNearestNeighbors[j]);
                    }
                    printf("\n");
                }
                break;
            case 4:
                if (!fileLoaded) {
                    printf("File not read yet. Please read file from beginning\n");
                    break;
                }
                
                int result = 0;
                for (int i = 0; i < 3; i++) {
                    result = predictClass(dataZoo, newSample, whichDistanceFunc[i], k);
                    printf("The predicted class is: %d \n", result);
                }
                break;
            case 5:
                //printf("here\n");
                if (!fileLoaded) {
                    printf("File not read yet. Please read file from beginning\n");
                    break;
                }
               // printf("Here 2\n");
                float accuracy = 0;
                char fname [30];
                //printf("here 3\n");
                strcpy(fname, argv[2]);
                struct Animal testData[NUM_TEST_DATA];
                //printf("here 4\n");
                int readCSVfile = 0;
	
                readCSVfile = readCSV(fname, testData);
                
                if (readCSVfile == -1) {
                    printf("file not read properly, please try again.");
                }
                
                for (int i = 0; i < 3; i++) {
                    accuracy = findAccuracy(dataZoo, whichDistanceFunc[i], testData, k);
                    printf("Accuracy: %.6f", accuracy);                
                }
                break;
            case 6:
                printf("Goodbye\n");
                break;
            default:
                printf("Error. Please try again.\n");
                break;

        }
    } while (choice != 6);
    
    return 0;
}