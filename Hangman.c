/*
Program for Hangman Game
Author: Vatsal Jaiswal
Description: A command-line version of the classic Hangman game where the user guesses a hidden word, one letter at a time, within 7 attempts.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Function to print ASCII art of hangman based on current stage
void print_hangman(int stage)
{
    char *hangman[] = {
        " +---+\n"
        " |   |\n"
        "     |\n"
        "     |\n"
        "     |\n"
        "     |\n"
        "=========\n",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "     |\n"
        "     |\n"
        "     |\n"
        "=========\n",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        " |   |\n"
        "     |\n"
        "     |\n"
        "=========\n",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|   |\n"
        "     |\n"
        "     |\n"
        "=========\n",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|\\  |\n"
        "     |\n"
        "     |\n"
        "=========\n",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|\\  |\n"
        "/    |\n"
        "     |\n"
        "=========\n",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|\\  |\n"
        "/ \\  |\n"
        "     |\n"
        "=========\n"};
    printf("%s", hangman[stage]);
}

// Function to select a random english word from 'Words.txt' file
void word_finder(char *word)
{
    srand(time(0));
    int actual_word = (rand() % 508) + 1;

    FILE *wordbook;
    wordbook = fopen("words.txt", "r");

    int current_word = 1;
    while (1)
    {
        fgets(word, 40, wordbook);
        if (current_word == actual_word)
            break;
        current_word++;
    }
    fclose(wordbook);
}

// Function to display the game introduction and rules to the player
void intro()
{
    printf("Welcome to Hangman!\n");
    printf("Guess the hidden word, one letter at a time.\n\n");
    printf("Rules:\n");
    printf("1. You have 7 attempts to guess the word.\n");
    printf("2. For every wrong guess, the hangman gets closer to being completed.\n");
    printf("3. Guess all the letters before the hangman is fully drawn to win!\n\n");
    printf("Tip: Use your guesses wisely and avoid repeated letters!\n");
    printf("Good luck and have fun!\n\n");
}

// Function to handle the player's guess and update the game state
void move(char *word, char *blank, int *found, int *wrong)
{
    char c;
    int check = 0;
    printf("Guess the character: ");
    scanf(" %c", &c);

    // Check if the guessed character is in the word
    for (int i = 0; blank[i] != '\0'; i++)
    {
        if (word[i] == c)
        {
            blank[i] = c; // Reveal the character in the blank word
            check++;
        }
    }

    // If the character is not found in the word
    if (!check)
    {
        print_hangman(*wrong);
        (*wrong)++;
        (*found)++;
        printf("Not found\n");

        // Check if all attempts are used
        if ((*wrong) == 7)
        {
            printf("!! GAME OVER !!\n");
            printf("The word was %s", word);
        }
    }
}

// Function to check if the player has won by guessing all letters
bool won(char *final)
{
    int review = 0;
    for (int i = 0; final[i] != '\0'; i++)
    {
        if (final[i] == 95) // If any underscore remains, the game is not won
            return false;
    }
    return true;
}

// Function to run the game loop
void game()
{
    char word[40], nword[40];
    int confirm = 0, chances = 0, again = 0;

    word_finder(word); // Get a random word

    // Initialize the blank version of the word with underscores
    for (int p = 0; p < strlen(word) - 1; p++)
    {
        nword[p] = 95;
    }
    nword[strlen(word) - 1] = '\0'; // Null-terminate the blank word

    intro(); // Display the intro

    while (1)
    {
        if (chances >= 7)
            break;
        if (!confirm)
            puts(nword);
        confirm = 0;
        if (won(nword))
        {
            printf("Congratulations! You won");
            break;
        }
        move(word, nword, &confirm, &chances);
    }
}

int main()
{
    game();
    return 0;
}
