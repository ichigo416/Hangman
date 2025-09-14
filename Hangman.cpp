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

    // --- NEW: Score variables declared outside the loop to persist across games ---
    int wins = 0;
    int losses = 0;
    bool play_again = true;
    // -----------------------------------------------------------------------------

    std::cout << "Welcome to Hangman!" << std::endl;

    // --- NEW: Outer loop to allow playing multiple games ---
    while (play_again) {
        // Use a random number generator to pick a word
        unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(0, words.size() - 1);
        std::string secret_word = words[distribution(generator)];
        
        // Initialize game variables for each new game
        std::string hidden_word(secret_word.length(), '_');
        std::vector<char> guessed_letters;
        int incorrect_guesses = 0;
        const int max_incorrect_guesses = 6;

        std::cout << "\nStarting a new game!" << std::endl;

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

        // --- NEW: Update score based on the outcome of the game ---
        if (hidden_word == secret_word) {
            std::cout << "Congratulations! You guessed the word: " << secret_word << std::endl;
            wins++;
        } else {
            std::cout << "Game over! The word was: " << secret_word << std::endl;
            losses++;
        }
        // -------------------------------------------------------------

        // --- NEW: Ask the player if they want to play again ---
        char response;
        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> response;
        response = std::tolower(static_cast<unsigned char>(response));

        if (response != 'y') {
            play_again = false;
        }
        // -------------------------------------------------------------
    }

    std::cout << "\nFinal Score: Wins = " << wins << ", Losses = " << losses << std::endl;
    std::cout << "Thanks for playing!" << std::endl;

    return 0;
}