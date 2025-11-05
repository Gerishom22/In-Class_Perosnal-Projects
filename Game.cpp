#include <iostream>;
#include <vector>;
#include <ctime>;
using namespace std;


//1. Functional Requirements

//Game Board :

//AI Integration :
//Implement an AI player that uses a tree structure to evaluate potential moves.
//Use the Minimax algorithm to determine the best possible move for the AI.
//Game Logic :
//Detect winning conditions(when no objects are left).
//End the game and announce the winner.

//will store the state of each pile, all possible children, and which player is the gamestate is comparing to

struct Node {
public:
    vector<int> piles;
    vector<Node> children;
    bool isMaximizingPlayer;

    Node(vector<int> piles, bool isMaximizing) {
        this->piles = piles;
        this->isMaximizingPlayer = isMaximizing;
    }
};

int sum_piles(vector<int> piles) {
    int running_total = 0;
    for (int pile : piles) {
        running_total += pile;
    }
    return running_total;
}

bool isTerminal(vector<int> piles) {
    int sum = 0;

    sum = sum_piles(piles);

    if (sum == 0) {
        return true;
    }
    else {
        return false;
    }
}

int evaluate(Node node) {
    int nimsum = 0;

    for (int pile : node.piles) {
        nimsum = nimsum ^ pile;
    }

    if (nimsum == 0) {
        return -1;
    }
    else {
        return 1;
    }
}

//Gernerate all possible moves for current node
void generateChildren(Node& node) {
    node.children.clear();
    //For each pile, generate new nodes by removing 1 to all objects from that pile
    for (int i = 0; i < node.piles.size(); ++i) {
        for (int j = 1; j <= node.piles[i]; ++j) {
            vector<int> newPiles = node.piles; //Copy current piles
            newPiles[i] -= j;
            Node child(newPiles, !node.isMaximizingPlayer);
            node.children.push_back(child);
        }

    }
}

int minimax(Node node, int depth, bool isMaximizingPlayer) {
    if (isTerminal(node.piles) || depth == 0) {
        return evaluate(node);
    }

    generateChildren(node);

    if (isMaximizingPlayer) {
        int best = -99999999;
        for (Node child : node.children) {
            int value = minimax(child, depth - 1, false);
            best = max(best, value);
        }
        return best;
    }
    else {
        int best = 99999999;
        for (Node child : node.children) {
            int value = minimax(child, depth - 1, true);
            best = min(best, value);
        }
        return best;
    }
}

//AI makes the best move based on minimax evaluation
void ai_best_move(vector<int>& piles) {
    Node root(piles, true);
    generateChildren(root);
    int bestValue = -99999999;
    Node bestMove = root;
    for (Node child : root.children) {
        int moveValue = minimax(child, 5, false);
        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = child;
        }
    }
    piles = bestMove.piles;
}

void playermove(vector<int>& piles) {
    int pileIndex;
    int removeCount;
    bool entered_valid_num = false;

    cout << "Which pile do you want take from: ";
    cin >> pileIndex;
    cout << "How many to remove from pile " << pileIndex << ": ";
    cin >> removeCount;
    while (!entered_valid_num) {
        if (piles[pileIndex - 1] - removeCount < 0) {
            cout << "Cannot take a pile negetive, reselect amount to remove from pile " << pileIndex << ": ";
            cin >> removeCount;
        }
        else {
            piles[pileIndex - 1] -= removeCount;
            entered_valid_num = true;
        }
    }
}

void printPiles(const vector<int>& piles) {
    int pile_number = 1;
    for (int pile : piles) {
        cout << "Pile " << pile_number << ": " << pile << endl;
        pile_number++;
    }
}


void main() {
    srand(time(0));
    cout << "Welcome to the Game of NIM!" << endl;
    vector<int> piles;
    int numPiles;
    bool isPlayerTurn;
    char choice;
    //int pile_sum = 0;

    cout << "How many piles are we playing with: ";
    cin >> numPiles;

    //Decide how piles are generated
    cout << "Would you like random pile sizes? (y/n): ";
    cin >> choice;
    int pileSize;

    for (int i = 0; i < numPiles; ++i) {
        if (choice == 'y' || choice == 'Y') {
            //random gen piles
            pileSize = rand() % 10 + 1;
        }
        else {
            //Get pile sizes from user
            cout << "Enter size of pile " << i + 1 << ": ";
            cin >> pileSize;
        }
        piles.push_back(pileSize);
    }

    //Choose to play PVP or vs AI
    cout << "Would you like to play AI? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {

        //Choose who goes first
        cout << "Do you want to go first? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            isPlayerTurn = true;
            cout << "You will go first." << endl;
        }
        else {
            cout << "AI will go first." << endl;
            isPlayerTurn = false;
        }

        cout << "Game Start:" << endl << "-----------" << endl;
        printPiles(piles);

        while (sum_piles(piles) > 0) {
            cout << endl;
            if (isPlayerTurn) {
                playermove(piles);
                cout << "Piles after your move: " << endl;
                printPiles(piles);
                isPlayerTurn = false;
            }
            else {
                ai_best_move(piles);
                cout << "Piles after AI move: " << endl;
                printPiles(piles);
                //Go to player's turn
                isPlayerTurn = true;
            }
        }
        string player;
        if (sum_piles(piles) == 0) {
            //Have to take negation because it swaps after player turn
            if (!isPlayerTurn) {
                player = "You are";
            }
            else {
                player = "AI is";
            }
            cout << player << " the winner!" << endl << endl;
        }
    }

    //make pvp route
    else {
        int player = 0;
        cout << "Game Start:" << endl << "-----------" << endl;
        printPiles(piles);

        while (sum_piles(piles) > 0) {
            player = player % 2 + 1;
            cout << "Player " << player << " move:" << endl;
            playermove(piles);
            cout << "Piles after your move: " << endl;
            printPiles(piles);
        }
        if (sum_piles(piles) == 0) {
            cout << "Player " << player << "is the winner!" << endl << endl;
        }
    }
}