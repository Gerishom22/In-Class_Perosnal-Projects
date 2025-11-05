#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    // Prompt the user to enter the number of rows
    int rows;
    cout << "Enter the number of rows for Pascal's Triangle: ";
    cin >> rows;

    // Use a 2D vector to store Pascal's Triangle
    vector<vector<int>> triangle(rows);

    // Generate Pascal's Triangle
    for (int i = 0; i < rows; i++) {
        triangle[i].resize(i + 1);  // Each row has i+1 elements
		for (int j = 0; j <= i; j++) { 
			if (j == 0 || j == i) { 
                triangle[i][j] = 1;  // First and last elements are always 1
            }
            else {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j]; // Sum of two above
            }
            cout << triangle[i][j] << " "; // Print value
        }
        cout << endl; // New line after each row
    }

	//What Pascal’s Triangle is(a triangular array of numbers 
	//where each number is the sum of the two numbers directly above it).
	
	//Binomial expansion: The coefficients of the expanded form of (a + b)^n correspond 
	// o the numbers in the nth row of Pascal's Triangle.


		return 0;

}