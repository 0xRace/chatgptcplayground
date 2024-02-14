#include <iostream>

void initializeBoard(char board[3][3]) {
    char currentChar = '1';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = currentChar++;
        }
    }
}

void printBoard(const char board[3][3]) {
    std::cout << "\nTic-Tac-Toe Board:\n\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j];
            if (j < 2) std::cout << " | ";
        }
        if (i < 2) std::cout << "\n---------\n";
    }
    std::cout << "\n";
}

bool updateBoard(char board[3][3], int move, char symbol) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = symbol;
        return true;
    }
    return false;
}

bool checkWin(const char board[3][3]) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true; // Row
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true; // Column
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true; // Diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true; // Anti-diagonal
    return false;
}

bool checkDraw(const char board[3][3], int movesPlayed) {
    // If all moves are played and no win, it's a draw
    return movesPlayed >= 9;
}

void getPlayerMove(char board[3][3], char playerSymbol) {
    int move;
    do {
        std::cout << "Player " << playerSymbol << ", enter your move (1-9): ";
        while (!(std::cin >> move) || move < 1 || move > 9) {
            std::cout << "Invalid input. Please enter a number between 1 and 9: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    } while (!updateBoard(board, move, playerSymbol));
}

int main() {
    char board[3][3];
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        initializeBoard(board);
        int currentMove = 0;
        bool gameEnded = false;

        while (!gameEnded) {
            printBoard(board);
            char playerSymbol = (currentMove % 2 == 0) ? 'X' : 'O';
            getPlayerMove(board, playerSymbol);
            currentMove++;
            if (checkWin(board)) {
                printBoard(board);
                std::cout << "Player " << playerSymbol << " wins!\n";
                gameEnded = true;
            } else if (checkDraw(board, currentMove)) {
                printBoard(board);
                std::cout << "The game is a draw.\n";
                gameEnded = true;
            }
        }

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
        std::cin.ignore(10000, '\n'); // Clear the newline character from the input buffer
    }

    return 0;
}
