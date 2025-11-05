#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//Determine if a 9 x 9 Sudoku board is valid.Only the filled cells need to be 
// validated according to the following rules :

//Each row must contain the digits 1 - 9 without repetition.
//Each column must contain the digits 1 - 9 without repetition.
//Each of the nine 3 x 3 sub - boxes of the grid must contain the digits 1 - 9 without repetition.


bool isValidSudoku(const vector<vector<char>>& board) {

    // Loop through each row, column, and 3x3 box
    for (int i = 0; i < 9; i++) {
        bool rowC[9] = { false }; 
        bool colC[9] = { false };
        bool boxC[9] = { false };

        for (int j = 0; j < 9; j++) {
            // Check Row
            if (board[i][j] != '.') {
                int num = board[i][j] - '1'; 
                if (rowC[num]) {
                    return false;
                }
                rowC[num] = true;
            }

            // Check Column 
            if (board[j][i] != '.') {
                int num = board[j][i] - '1';
                if (colC[num]) {
                    return false;
                }
                colC[num] = true;
            }

            // Check 3x3 Box 
            int boxRow = 3 * (i / 3) + j / 3;
            int boxCol = 3 * (i % 3) + j % 3;
            if (board[boxRow][boxCol] != '.') {
                int num = board[boxRow][boxCol] - '1';
                if (boxC[num]) {
                    return false;
                }
                boxC[num] = true;
            }
        }
    }
    return true;
}



void main() {

	// Example 1 (Valid) - From Assignment
    vector<vector<char>> board1 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    // Example 2 (Invalid) - From Assignment
    vector<vector<char>> board2 = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

	// Example 3 (Invalid) - Custom
    vector<vector<char>> board3 = {
        {'.','.','.','.','5','.','.','1','.'},
        {'.','4','.','3','.','.','.','.','.'},
        {'.','.','.','.','.','3','.','.','1'},
        {'8','.','.','.','.','.','.','2','.'},
        {'.','.','2','.','7','.','.','.','.'},
        {'.','1','5','.','.','.','.','.','.'},
        {'.','.','.','.','.','2','.','.','.'},
        {'.','2','.','9','.','.','.','.','.'},
        {'.','.','4','.','.','.','3','.','.'}
	};

	// Example 4 (Valid) - Custom
    vector<vector<char>> board4 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','3','5','7','2','8','9'},
        {'.','.','.','4','1','9','6','3','5'},
        {'.','.','.','6','8','2','1','7','4'}
    };

    cout << "Example 1 Output: " << (isValidSudoku(board1) ? "true" : "false") << endl;
    cout << "Example 2 Output: " << (isValidSudoku(board2) ? "true" : "false") << endl;
	cout << "Example 3 Output: " << (isValidSudoku(board3) ? "true" : "false") << endl;
	cout << "Example 4 Output: " << (isValidSudoku(board4) ? "true" : "false") << endl;

    return;
}