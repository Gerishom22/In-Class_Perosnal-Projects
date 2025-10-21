#include <iostream>
#include "GreatE.h"

using namespace std;

int main() {
    int boardSize = 62;  // Define the size of the board 
    Table t1(boardSize);  // Create a Table object with the specified board size

    t1.kTour();  // Start the knight's tour simulation

    return 0;
}
