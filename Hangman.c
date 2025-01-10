#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *words[] = {"giraffe", "elephant", "narwhal", "aardvark", "ibex", "dolphin", "robot", "airplane", "computer", "automobile", "television", "magnet", "pizza", "hamburger", "lasagna", "bicycle", "kayak", "queue", "onomatopoeia", "jaguar", "rose", "eagle", "penguin", "library", "rollercoaster", "starfish"};
int length = sizeof(words) / sizeof(words[0]);
int wordLength;
char letters[26];  // Track guessed letters

void initiateLettersArray(void) {
    for (int i = 0; i < 26; i++) {
        letters[i] = 0;  // Initialize letters array to 0 (not guessed yet)
    }
}

int randomize(void) {
    srand(time(NULL));
    return rand() % length;
}

char* selectWord(int wordIndex) {
    return words[wordIndex];
}

void hideWord(int word_length, char* blankWord) {
    for (int i = 0; i < word_length; i++) {
        blankWord[i] = '_';  // Hide all letters with underscores
    }
    blankWord[word_length] = '\0';  // Null-terminate the string
}

void displayWord(char* blank_word){
	for (int i = 0; i < strlen(blank_word); i++){
		printf("%c", blank_word[i]);
		printf(" ");
	}
	printf("\n");
}


int updateWord(char letter, char* blank_word, char* selected_word) {
    int correctGuess = 0;
    for (int i = 0; i < wordLength; i++) {
        if (selected_word[i] == letter) {
            blank_word[i] = selected_word[i];  // Correctly update the blank word
            correctGuess++;
        }
    }
    return correctGuess;
}

// Function to check if the letter has already been guessed
int hasGuessedBefore(char letter) {
    return letters[letter - 'a'] == 1;  // Return true if the letter has been guessed
}

// Function to mark the letter as guessed
void markAsGuessed(char letter) {
    letters[letter - 'a'] = 1;  // Mark the letter as guessed
}

// Function to draw the hangman figure based on mistakes
void drawHangman(int mistakes) {
                          printf("\n    +---+\n");
                          printf("    |   | \n");
    if (mistakes > 0)    {printf("    O   | \n");  //Head
    }else                {printf("        | \n") ;}
   
    if(mistakes > 3)     {printf("   /|\\  | \n");} // Body and arms
    else if(mistakes > 2){printf("   /|   | \n");}
    else if(mistakes > 1){printf("    |   | \n");}
    else                 {printf("        | \n");}
    
    if(mistakes > 5)     {printf("   / \\  | \n");}  // legs
    else if(mistakes > 4){printf("   /    | \n");}    
    else                 {printf("        | \n");}
                          printf("        | \n");
                          printf("   =====#\n\n");
}

int main(void) {
    initiateLettersArray();  // Initialize the letters array to track guesses
    int mistakes = 0;
    int correctGuesses = 0;
    int randomWordIndex = randomize();
    char* selectedWord = selectWord(randomWordIndex);
    wordLength = strlen(selectedWord);
    char blankWord[wordLength + 1];  // +1 for null-terminator

    hideWord(wordLength, blankWord);
    printf("\nHere is your word!!\n");
    displayWord(blankWord);

    // main loop
    while (mistakes < 6 && correctGuesses < wordLength) {
        char next_guess;
        printf("\nGuess your next letter!\n");
        
        // Ensure the user doesn't enter a duplicate guess
        while (1) {
            scanf(" %1c", &next_guess); //discard any leading whitespace
            while(getchar() != '\n');
	    if (hasGuessedBefore(next_guess)) {
                printf("You've already guessed that letter. Try a different one.\n");
            } else {
                markAsGuessed(next_guess);
		printf("\nChecking Letter.....\n\n");
                break;  // Exit the loop once a valid guess is entered
            }
        }
        
        int guessEval = updateWord(next_guess, blankWord, selectedWord);
        if (guessEval > 0) {
	    printf("GOOD GUESS!!\n");
            correctGuesses += guessEval;
        } else {
	    printf("Sorry! Looks like that letter didn't work... \n");
            mistakes++;
        }
	displayWord(blankWord);
        drawHangman(mistakes);
    }

    if (mistakes >= 6) {
        printf("GAME OVER! The word was:  %s \n", selectedWord);
    } else {
        printf("CONGRATS!!! YOU WON!!!\n");
    }

    return 0;
}
