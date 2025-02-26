#include <iostream>
#include <string>
#include <limits>
#include <conio.h>

using namespace std;

string secretWord;

// Function to take hidden word input without displaying it
void inputHiddenWord() {
    cout << "Enter the secret word (5 letters in English): ";
    char ch;
    secretWord = "";

    while (secretWord.size() < 5) {
        ch = _getch(); // Read character without displaying
        if (ch == '\r') break; // Stop input on Enter key
        secretWord += ch;
        cout << "*"; // Display * instead of character
    }
    cout << "\nWord has been set!\n\n";
}

// Function to check the guessed word against the secret word
void checkWord(string guess, bool& stopGame) {
    if (guess == "stop") { // Allow exit to menu
        cout << "Returning to game selection...\n";
        stopGame = true;
        return;
    }
    if (guess.size() != secretWord.size()) { // Ensure correct word length
        cout << "Enter a word with " << secretWord.size() << " letters!\n";
        return;
    }

    string result = "";
    for (int i = 0; i < secretWord.size(); i++) {
        if (guess[i] == secretWord[i]) { // Correct letter in correct position
            result += "G";
        }
        else if (secretWord.find(guess[i]) != string::npos) { // Correct letter in wrong position
            result += "Y";
        }
        else { // Incorrect letter
            result += "x";
        }
    }
    cout << "Result: " << result << "\n";

    if (guess == secretWord) { // Check for correct guess
        cout << "You guessed the word: " << secretWord << "!\n";
        stopGame = true;
    }
}

// Function to start Wordle game
void playWordle() {
    inputHiddenWord();
    cout << "Welcome to Wordle! Guess the 5-letter word. Type 'stop' to exit to menu.\n";
    bool stopGame = false;
    while (!stopGame) {
        string guess;
        cout << "Enter your guess: ";
        cin >> guess;
        checkWord(guess, stopGame);
    }
}

const int SIZE = 3;
char board[SIZE][SIZE];

// Reset board before starting a new game
void resetBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

// Print the Tic-Tac-Toe board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << (board[i][j] == ' ' ? ' ' : board[i][j]) << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Check if a player has won
char checkWin() {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return board[0][2];
    return ' ';
}

// Check if there are any moves left
bool movesLeft() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ') return true;
    return false;
}

// AI move for Tic-Tac-Toe
void bestMove() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                if (checkWin() == 'O') return;
                board[i][j] = 'X';
                if (checkWin() == 'X') {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                return;
            }
        }
    }
}

// Function to play Tic-Tac-Toe
void playTicTacToe() {
    resetBoard();
    int turn = 0;
    char winner = ' ';
    while (movesLeft() && winner == ' ') {
        printBoard();
        if (turn % 2 == 0) {
            int choice;
            cout << "Player X, enter cell number (1-bottom left / 9-top right): ";
            cin >> choice;
            int row = 2 - (choice - 1) / SIZE;
            int col = (choice - 1) % SIZE;
            if (board[row][col] != ' ') {
                cout << "Cell occupied! Choose another one.\n";
                continue;
            }
            board[row][col] = 'X';
        }
        else {
            cout << "AI (O) is making a move...\n";
            bestMove();
        }
        turn++;
        winner = checkWin();
    }
    printBoard();
    if (winner == 'X') cout << "Player X wins!\n";
    else if (winner == 'O') cout << "AI (O) wins!\n";
    else cout << "It's a draw!\n";
}

// Main function to select and start games
int main() {
    while (true) {
        int choice;
        cout << "Choose a game:\n1 - Tic-Tac-Toe\n2 - Wordle\n3 - Exit\n> ";
        cin >> choice;
        if (choice == 1) playTicTacToe();
        else if (choice == 2) playWordle();
        else if (choice == 3) break;
        else cout << "Invalid input! Try again.\n";
    }
    return 0;
}
