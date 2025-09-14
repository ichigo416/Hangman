#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <cctype>

// Function to display the hangman figure based on the number of incorrect guesses
void display_hangman(int incorrect_guesses) {
    if (incorrect_guesses >= 1) std::cout << "  O" << std::endl;
    if (incorrect_guesses >= 2) std::cout << " /|\\" << std::endl;
    if (incorrect_guesses >= 3) std::cout << "  |" << std::endl;
    if (incorrect_guesses >= 4) std::cout << " / \\" << std::endl;
    if (incorrect_guesses >= 5) std::cout << "=======" << std::endl;
    if (incorrect_guesses >= 6) std::cout << "|     |" << std::endl;
    std::cout << std::endl;
}

// Function to check if a character is a valid guess (a-z)
bool is_valid_guess(char guess) {
    return std::isalpha(static_cast<unsigned char>(guess));
}

int main() {
    // List of words for the game
    std::vector<std::string> words = {
        "programming", "computer", "keyboard", "algorithm", 
        "developer", "language", "hardware", "software"
    };

    // Use a random number generator to pick a word
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, words.size() - 1);
    std::string secret_word = words[distribution(generator)];
    
    // Initialize game variables
    std::string hidden_word(secret_word.length(), '_');
    std::vector<char> guessed_letters;
    int incorrect_guesses = 0;
    // --- THIS LINE HAS BEEN UPDATED ---
    const int max_incorrect_guesses = 6;
    // -----------------------------------

    std::cout << "Welcome to Hangman!" << std::endl;

    // Main game loop
    while (incorrect_guesses < max_incorrect_guesses && hidden_word != secret_word) {
        std::cout << "---------------------------------------" << std::endl;
        display_hangman(incorrect_guesses);
        std::cout << "Word: " << hidden_word << std::endl;
        std::cout << "Incorrect guesses: " << incorrect_guesses << " / " << max_incorrect_guesses << std::endl;
        
        std::cout << "Guessed letters: ";
        for (char letter : guessed_letters) {
            std::cout << letter << " ";
        }
        std::cout << std::endl;

        char guess;
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        guess = std::tolower(static_cast<unsigned char>(guess));

        // Input validation and guess checking
        if (!is_valid_guess(guess)) {
            std::cout << "Invalid guess. Please enter a letter from a-z." << std::endl;
            continue;
        }

        // Check if the letter has already been guessed
        if (std::find(guessed_letters.begin(), guessed_letters.end(), guess) != guessed_letters.end()) {
            std::cout << "You already guessed that letter. Try again." << std::endl;
            continue;
        }

        guessed_letters.push_back(guess);

        // Check if the guess is in the secret word
        bool found = false;
        for (size_t i = 0; i < secret_word.length(); ++i) {
            if (secret_word[i] == guess) {
                hidden_word[i] = guess;
                found = true;
            }
        }

        if (found) {
            std::cout << "Good guess!" << std::endl;
        } else {
            std::cout << "Sorry, that letter is not in the word." << std::endl;
            incorrect_guesses++;
        }
    }

    std::cout << "---------------------------------------" << std::endl;
    display_hangman(incorrect_guesses);

    // End of game messages
    if (hidden_word == secret_word) {
        std::cout << "Congratulations! You guessed the word: " << secret_word << std::endl;
    } else {
        std::cout << "Game over! The word was: " << secret_word << std::endl;
    }

    return 0;
}