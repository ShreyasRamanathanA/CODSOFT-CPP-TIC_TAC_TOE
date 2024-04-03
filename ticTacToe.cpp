#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

//Function to print the board
void printBoard(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

//Function to check whether a player won or not
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        //Check rows
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        //Check columns
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    return false;
}

//Function to check if the game is draw
bool checkDraw(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false; // Empty cell found, game is not a draw
            }
        }
    }
    return true; // All cells are filled, game is a draw
}

//Function to get the player's move
int getPlayerMove(const std::vector<std::vector<char>>& board) {
    int position;
    while (true) {
        std::cout << "Enter your move (position 0-8): ";
        if (std::cin >> position && position >= 0 && position < 9 && board[position / 3][position % 3] == ' ') {
            break; // Valid move entered, exit the loop
        } else {
            std::cout << "Invalid move. Please enter a valid position.\n";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return position;
}

//Function to generate computer's move
int getComputerMove(const std::vector<std::vector<char>>& board) {
    // Generate a random move
    return rand() % 9;
}

int main() {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));
    char currentPlayer = 'X';
    bool gameEnded = false;
    int gameMode;
    int playAgain;

    std::cout << "Welcome to Tic Tac Toe!" << std::endl;
    std::cout << "These are the board positions. Keep track of them and use them to play the game!\n" << std::endl;

    do {
        std::cout << "Choose a game mode:" << std::endl;
        std::cout << "1. 2 Players" << std::endl;
        std::cout << "2. Player vs Computer" << std::endl;
        std::cout << "Enter the game mode(1 or 2): ";
        std::cin >> gameMode;

        while (gameMode != 1 && gameMode != 2) {
            std::cout << "Enter a valid game mode(1 for 2 Players or 2 for Player vs Computer)!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> gameMode;
        }

        while (!gameEnded) {
            // Display board
            printBoard(board);

            // Get player's move
            int move;
            if (gameMode == 1 || currentPlayer == 'X') {
                move = getPlayerMove(board);
            } else {
                move = getComputerMove(board);
                std::cout << "Computer chose position " << move << std::endl;
            }

            // Update board
            if (move >= 0 && move < 9 && board[move / 3][move % 3] == ' ') {
                board[move / 3][move % 3] = currentPlayer;
            } else {
                std::cout << "Invalid move. Try again.\n" << std::endl;
                continue;
            }

            // Check for win
            if (checkWin(board, currentPlayer)) {
                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                gameEnded = true;
            }

            // Check for draw
            if (checkDraw(board)) {
                std::cout << "It's a draw!\n" << std::endl;
                gameEnded = true;
            }

            // Switch players
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        // Display final board
        printBoard(board);

        // Ask if the players want to play again
        std::cout << "Do you want to play again? (1 for Yes, 0 for No): ";
        std::cin >> playAgain;

        // Reset the board and game state
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        currentPlayer = 'X';
        gameEnded = false;

    } while (playAgain == 1);

    std::cout << "\nThanks for playing! Goodbye\n\n";

    return 0;
}
