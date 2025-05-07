#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EASY_MAX 50
#define MEDIUM_MAX 100
#define HARD_MAX 200

int playGame(int maxNumber, int maxAttempts) {
    int number, guess, attempts = 0;
    int score = 100;
    
    // Generate random number between 1 and maxNumber
    number = rand() % maxNumber + 1;
    
    printf("\nI have chosen a number between 1 and %d.\n", maxNumber);
    printf("You have %d attempts. Start with 100 points.\n", maxAttempts);
    
    do {
        printf("\nAttempts left: %d", maxAttempts - attempts);
        printf("\nEnter your guess (1-%d): ", maxNumber);
        
        // Input validation
        while (scanf("%d", &guess) != 1 || guess < 1 || guess > maxNumber) {
            printf("Invalid input! Enter a number between 1 and %d: ", maxNumber);
            while (getchar() != '\n');
        }
        
        attempts++;
        
        if (guess > number) {
            printf("Too high! ");
            score -= (maxNumber == HARD_MAX) ? 15 : 10;
        }
        else if (guess < number) {
            printf("Too low! ");
            score -= (maxNumber == HARD_MAX) ? 15 : 10;
        }
        else {
            printf("\n🎉 Congratulations! You've guessed the number in %d attempts!\n", attempts);
            // Bonus points for quick guesses
            score += (maxAttempts - attempts) * 5;
            printf("Your final score is: %d points\n", score);
            return score;
        }
        
        if (score <= 0 || attempts >= maxAttempts) {
            printf("\nGame Over! ");
            if (score <= 0) printf("You ran out of points!\n");
            else printf("You ran out of attempts!\n");
            printf("The number was: %d\n", number);
            return 0;
        }
        
    } while (1);
}

int main() {
    int highScore = 0;
    char playAgain;
    int difficulty;
    
    // Seed the random number generator
    srand(time(0));
    
    do {
        printf("\n=== NUMBER GUESSING GAME ===\n");
        printf("Current High Score: %d\n\n", highScore);
        printf("Select Difficulty:\n");
        printf("1. Easy (1-50, 10 attempts)\n");
        printf("2. Medium (1-100, 7 attempts)\n");
        printf("3. Hard (1-200, 5 attempts)\n");
        printf("Choose (1-3): ");
        
        while (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 3) {
            printf("Invalid input! Choose 1-3: ");
            while (getchar() != '\n');
        }
        
        int score;
        switch (difficulty) {
            case 1:
                score = playGame(EASY_MAX, 10);
                break;
            case 2:
                score = playGame(MEDIUM_MAX, 7);
                break;
            case 3:
                score = playGame(HARD_MAX, 5);
                break;
        }
        
        if (score > highScore) {
            printf("\n🏆 NEW HIGH SCORE: %d! 🏆\n", score);
            highScore = score;
        }
        
        printf("\nPlay again? (y/n): ");
        while (getchar() != '\n');
        scanf("%c", &playAgain);
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    printf("\nThanks for playing! Final High Score: %d\n", highScore);
    return 0;
}