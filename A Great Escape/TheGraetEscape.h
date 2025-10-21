#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>

using namespace std;

class Table {
private:
    int size;                          // Size of the board
    vector<vector<int>> board;         // 2D vector to hold the board numbers
    vector<int> history;               // Vector to track the knight's visited squares
    int position{ 1 };                  // Current position of the knight 

public:
    // Constructor that initializes the board size and fills the board in a spiral pattern
    Table(int size) : size(size) {
        board.resize(size, vector<int>(size, 0));  // Resize the board with zeros
        fSpiral();  // Call function to fill the board in a spiral pattern
    }

    // Function to fill the board in a spiral pattern
    void fSpiral() {
        int area = size * size;  // Total number of cells on the board
        int top = 0,
        bottom = size - 1;
        int left = 0, 
        right = size - 1;

        // While there are still cells to fill
        while (top <= bottom && left <= right) {
            // Fill the top row from left to right
            for (int i = left; i <= right; ++i) board[top][i] = area--;
            top++;  // Move the top boundary down

            // Fill the right column from top to bottom
            for (int i = top; i <= bottom; ++i) board[i][right] = area--;
            right--;  // Move the right boundary left

            // Fill the bottom row from right to left
            if (top <= bottom) {
                for (int i = right; i >= left; --i) board[bottom][i] = area--;
                bottom--;  // Move the bottom boundary up
            }

            // Fill the left column from bottom to top
            if (left <= right) {
                for (int i = bottom; i >= top; --i) board[i][left] = area--;
                left++;  // Move the left boundary right
            }
        }
    }

    // Prints the current state of the board, marking the knight's position and visited squares
    void pBoard(int knightX, int knightY) {
        cout << "\nCurrent Board State:\n";
        // Loop through each cell on the board and print its value
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == knightX && j == knightY)
                    cout << " K ";  // Mark the knight's position with 'K'
                else if (find(history.begin(), history.end(), board[i][j]) != history.end())
                    cout << " . ";  // Mark visited squares with '.'
                else
                    cout << setw(3) << board[i][j] << " ";  // Print the number on unvisited squares
            }
            cout << endl;
        }
        cout << endl;
    }

    // Finds the coordinates of a specific number on the board
    pair<int, int> fPos(int num) {
        // Loop through the entire board to find the coordinates of the number
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == num)
                    return { i, j };  // Return the coordinates (row, column)
            }
        }
        return { -1, -1 };  // Return invalid coordinates if the number is not found
    }

    // Function that simulates the knight's tour on the board
    void kTour() {
        bool hasMoves = true;   // Flag to check if the knight has valid moves
        vector<int> currMoves;  // Vector to hold the valid moves for the knight
        history.push_back(position);  // Add the starting position to the history

        // Find the starting position of the knight (in this case, number 1)
        pair<int, int> pos = fPos(1);  // Find the position of the number 1 on the board
        int x = pos.first;  // x-coordinate of the knight
        int y = pos.second; // y-coordinate of the knight

        int moveCount = 0;  // Track the number of moves the knight has made

        // While the knight still has valid moves
        while (hasMoves) {
            currMoves.clear();  // Clear the list of current valid moves
            history.push_back(position);  // Add the current position to the history

            // List of all possible knight moves (8 directions)
            vector<pair<int, int>> moves = {
                {x + 2, y + 1}, {x + 2, y - 1}, {x - 2, y + 1}, {x - 2, y - 1},
                {x + 1, y + 2}, {x + 1, y - 2}, {x - 1, y + 2}, {x - 1, y - 2}
            };

            // Check all the possible moves and add valid ones to currMoves
            for (const auto& move : moves) {
                int newX = move.first;
                int newY = move.second;

                // Check if the new position is within bounds and not visited
                if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
                    int square = board[newX][newY];
                    if (find(history.begin(), history.end(), square) == history.end()) {
                        currMoves.push_back(square);  // Add valid move to the list
                    }
                }
            }

            // If there are valid moves, choose the move with the smallest number
            if (!currMoves.empty()) {
                position = *min_element(currMoves.begin(), currMoves.end());  // Pick the move with the smallest number
                pos = fPos(position);  // Get the new coordinates of the move
                x = pos.first;
                y = pos.second;
                moveCount++;  // Increment the move count

                // Print the knight's current move and the updated board
                cout << "Knight moved to " << position << " | Total moves: " << moveCount << endl;
                pBoard(x, y);
            }
            else {
                // If no valid moves are available, stop the simulation
                cout << "\nNo more legal moves available." << endl;
                cout << "Knight moved a total of " << moveCount << " times." << endl;
                hasMoves = false;
            }
        }
    }
};
