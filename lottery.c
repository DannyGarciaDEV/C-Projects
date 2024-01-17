#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to display numbers
void displayNumbers(int numbers[], int size, const char *label) {
    printf("%s: ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}


// Function to check if the user has won
int checkWin(int userNumbers[], int lotteryNumbers[], int size) {
    int matches = 0;
    for (int i = 0; i < size; i++) {
        if (userNumbers[i] == lotteryNumbers[i]) {
            matches++;
        }
    }
    return matches;
}

void generateLotteryNumbers(int lotteryNumbers[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        lotteryNumbers[i] = rand() % 10 + 1; // Generates random numbers between 1 and 10
    }
}



int main() {
    const int lotterySize = 5; // Change this based on your lottery rules
    int lotteryNumbers[lotterySize];
    int userNumbers[lotterySize];

    // Initial message
    printf("Enter 5 random digits to win the lottery, example: 1 2 3 4 5\n");

    // Get user input for chosen numbers
    printf("type here your numbers: ");
    for (int i = 0; i < lotterySize; i++) {
        scanf("%d", &userNumbers[i]);
    }

    // Generate the lottery numbers after user input
    generateLotteryNumbers(lotteryNumbers, lotterySize);

   
  
    while (getchar() != '\n'); // Wait for Enter key

    // Display the user's numbers
    displayNumbers(userNumbers, lotterySize, "Your Choosing Numbers");

    // Display the winning numbers
    displayNumbers(lotteryNumbers, lotterySize, "Winning Numbers");

    // Check if the user has won
    int matches = checkWin(userNumbers, lotteryNumbers, lotterySize);

    // Display the result
    printf("You matched %d numbers.\n", matches);
    if (matches == lotterySize) {
        printf("Congratulations! You won the lottery!\n");
    } else {
        printf("Better luck next time.\n");
    }

    return 0;
}
