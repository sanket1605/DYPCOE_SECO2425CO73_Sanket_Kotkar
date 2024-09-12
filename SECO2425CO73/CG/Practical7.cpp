#include <iostream>
#include <graphics.h>  // Graphics library for drawing
#include <conio.h>     // For getch() to wait for user input

using namespace std;

// Abstract class representing a Player
class Player {
public:
    // Virtual function to get the player's move
    virtual pair<int, int> getMove() = 0;

    // Function to get the player's symbol (X or O)
    virtual char getSymbol() = 0;
};

// Derived class for Human Player
class HumanPlayer : public Player {
    char symbol;

public:
    // Constructor to initialize player symbol
    HumanPlayer(char sym) : symbol(sym) {}

    // Implementation of getMove for Human player
    pair<int, int> getMove() override {
        int row, col;
        cout << "Enter row and column (0-2) for player " << symbol << ": ";
        cin >> row >> col;
        return {row, col};
    }

    // Return player's symbol
    char getSymbol() override {
        return symbol;
    }
};

// Derived class for Computer Player
class ComputerPlayer : public Player {
    char symbol;

public:
    // Constructor to initialize player symbol
    ComputerPlayer(char sym) : symbol(sym) {}

    // Implementation of getMove for Computer player (random move)
    pair<int, int> getMove() override {
        int row = rand() % 3;
        int col = rand() % 3;
        cout << "Computer chooses row " << row << " and column " << col << endl;
        return {row, col};
    }

    // Return player's symbol
    char getSymbol() override {
        return symbol;
    }
};

// Class for Tic Tac Toe game
class TicTacToe {
    char board[3][3]; // 3x3 board
    Player* player1;
    Player* player2;
    int moves;

public:
    // Constructor to initialize the board and players
    TicTacToe(Player* p1, Player* p2) : player1(p1), player2(p2), moves(0) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }

    // Draw the Tic Tac Toe board using graphics
    void drawBoard() {
        cleardevice();  // Clear the graphics window
        // Draw the grid lines
        line(100, 200, 400, 200); // Horizontal line 1
        line(100, 300, 400, 300); // Horizontal line 2
        line(200, 100, 200, 400); // Vertical line 1
        line(300, 100, 300, 400); // Vertical line 2

        // Draw the players' symbols (X or O) on the board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = 150 + 100 * j; // X position
                int y = 150 + 100 * i; // Y position

                if (board[i][j] == 'X') {
                    outtextxy(x - 20, y - 20, "X");
                } else if (board[i][j] == 'O') {
                    outtextxy(x - 20, y - 20, "O");
                }
            }
        }
    }

    // Check if there is a winner
    bool checkWin(char symbol) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
        }
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
        return false;
    }

    // Play the game
    void playGame() {
        Player* currentPlayer = player1;

        while (moves < 9) {
            drawBoard();
            pair<int, int> move = currentPlayer->getMove();
            int row = move.first;
            int col = move.second;

            if (board[row][col] == ' ') {
                board[row][col] = currentPlayer->getSymbol();
                moves++;

                if (checkWin(currentPlayer->getSymbol())) {
                    drawBoard();
                    cout << "Player " << currentPlayer->getSymbol() << " wins!" << endl;
                    return;
                }

                currentPlayer = (currentPlayer == player1) ? player2 : player1;
            } else {
                cout << "Invalid move! Try again." << endl;
            }
        }

        drawBoard();
        cout << "It's a draw!" << endl;
    }
};

// Main function
int main() {
    // Initialize the graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Create players (Human vs Computer)
    Player* player1 = new HumanPlayer('X');
    Player* player2 = new ComputerPlayer('O');

    // Create a TicTacToe game instance and start playing
    TicTacToe game(player1, player2);
    game.playGame();

    getch();  // Wait for user input to close the window
    closegraph();  // Close the graphics window

    // Clean up
    delete player1;
    delete player2;

    return 0;
}

