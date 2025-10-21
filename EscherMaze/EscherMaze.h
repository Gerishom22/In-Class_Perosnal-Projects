#pragma once

// Gerishom Muholeza
// Blake Dirksen

#include <iostream>
#include <cstdlib> // For rand()
#include <ctime> // For seeding rand()
#include <string>
using namespace std;
// Node Class
template <typename T>
class Node {
private:
T data; // Data held by the node
Node<T>* up;
Node<T>* down;
Node<T>* left;
Node<T>* right;
public:
// Constructor
Node(T data) : data(data), up(nullptr), down(nullptr), left(nullptr),
right(nullptr) {}
// Getters
T getData() const { return data; }
Node<T>* getUp() const { return up; }
Node<T>* getDown() const { return down; }
Node<T>* getLeft() const { return left; }
Node<T>* getRight() const { return right; }
// Setters
void setData(T d) { data = d; }
void setUp(Node<T>* u) { up = u; }
void setDown(Node<T>* d) { down = d; }
void setLeft(Node<T>* l) { left = l; }
void setRight(Node<T>* r) { right = r; }
// Print node data
void print() const { cout << data << " "; }
};
// LinkedList Class
template <typename T>
class LinkedList {
private:
Node<string>* head; // Pointer to the top-left node of the grid
public:
// Constructor
LinkedList() : head(nullptr) {}
// Destructor
~LinkedList() { clear(); }
// Get head node
Node<string>* getHead() {
return head;
}
// Clear all nodes from the grid
void clear() {
while (head) {
Node<string>* row = head;
while (row) {
Node<string>* toDel = row;
row = row->getRight();
delete toDel;
}
head = head->getDown();
}
head = nullptr;
}
// Create a 3x3 grid
void C3x3() {
Node<string>* prevRow = nullptr;
srand(time(nullptr));
// Generate each row
for (int i = 0; i < 3; ++i) {
Node<string>* rowHead = nullptr;
Node<string>* prevNode = nullptr;
for (int j = 0; j < 3; ++j) {
// Create new node with random data
int rand_num = rand() % 3 + 1;
Node<string>* newNode = new Node<string>("*");
if (rand_num == 1) {
newNode->setData("<"); // Monster node
}
else if (rand_num == 2) {
newNode->setData("X"); // Delete node
}
// Ensure the middle node is the player starting point
if (i == 1 && j == 1) {
newNode->setData("^"); // Player starting position
}
if (!rowHead) rowHead = newNode; // Set the head of the current row
if (prevNode) {
prevNode->setRight(newNode);
newNode->setLeft(prevNode);
}
prevNode = newNode;
// Link to the node above if it exists
if (prevRow) {
Node<string>* aboveNode = prevRow;
for (int k = 0; k < j; ++k) {
aboveNode = aboveNode->getRight();
}
aboveNode->setDown(newNode);
newNode->setUp(aboveNode);
}
}
if (!head) head = rowHead; // Set the head of the grid
prevRow = rowHead; // Move to the next row
}
}
// Print the 2D grid
void pGrid() const {
Node<string>* row = head;
while (row) {
Node<string>* current = row;
while (current) {
current->print();
current = current->getRight();
}
cout << endl;
row = row->getDown();
}
}
// Randomize the grid nodes, except for the player position
void randomizeGrid() {
Node<string>* row = head;
srand(time(0));
while (row) {
Node<string>* current = row;
while (current) {
if (current->getData() != "^") { // Avoid changing the middle node
current->setData("*"); // Reset all to default
int rand_num = rand() % 3 + 1;
if (rand_num == 1) current->setData("<");
else if (rand_num == 2) current->setData("X");
}
current = current->getRight();
}
row = row->getDown();
}
}
// Remove a random node from the grid
void rRandom() {
if (!head) {
throw runtime_error("The grid is empty.");
}
srand(time(nullptr)); // Seed random generator
// Count total nodes
int totalNodes = 0;
Node<string>* row = head;
while (row) {
Node<string>* current = row;
while (current) {
totalNodes++;
current = current->getRight();
}
row = row->getDown();
}
// Generate a random index
int randomIndex = rand() % totalNodes;
// Locate and remove the node at random index
row = head;
int index = 0;
while (row) {
Node<string>* current = row;
while (current) {
if (index == randomIndex) {
// Update links to remove the node
if (current->getLeft()) current->getLeft()->setRight(current-
>getRight());
if (current->getRight()) current->getRight()->setLeft(current-
>getLeft());
if (current->getUp()) current->getUp()->setDown(current-
>getDown());
if (current->getDown()) current->getDown()->setUp(current-
>getUp());
// Update head if necessary
if (current == head) {
head = current->getRight() ? current->getRight() : current-
>getDown();
}
delete current; // Delete the node
return;
}
current = current->getRight();
index++;
}
row = row->getDown();
}
}
};

// Game Class
class Game {
private:
int moves{ 4 }; // Player's remaining moves
int coins{ 0 }; // Coins collected
Node<string>* character; // Pointer to the player's current position
Node<string>* header; // Pointer to the grid's head
Node<string>* current; // Pointer to the current node being interacted with
public:
// Start the game
void playGame() {
printKey();
LinkedList<string> G;
G.C3x3();
header = G.getHead();
cout << endl;
G.pGrid();
character = findCharacter(); // Locate the player's starting position
while (moves != 0) {
string move;
cout << "Which way do you want to move?" << endl;
cin >> move;
if (move == "w" || move == "a" || move == "s" || move == "d") {
string theMove = movement(move);
nodeDecision(theMove);
if (theMove != "<") { // Avoid randomizing if player loses
G.randomizeGrid();
header = G.getHead();
cout << endl;
G.pGrid();
}
}
else {
cout << "Not a valid move, try again" << endl;
}
}
cout << "The game is over, you ran into " << coins << " coins!" << endl;
}
// Handle the player's interaction with the current node
void nodeDecision(string move) {
if (move == "<") {
moves = 0;
cout << "You ran into a monster and lost :(" << endl;
}
else if (move == "*") {
cout << "You ran into a coin!" << endl;
coins++;
}
else if (move == "X") {
if (current) {
deleteNode(current); // Delete the node to the left
current = character;
}
moves--;
}
}
// Delete a node from the grid
void deleteNode(Node<string>* node) {
if (!node) return;
if (node->getData() == "^") {
cout << "Cannot delete the middle node!" << endl;
return;
}
// Update neighbors
if (node->getLeft()) node->getLeft()->setRight(node->getRight());
if (node->getRight()) node->getRight()->setLeft(node->getLeft());
if (node->getUp()) node->getUp()->setDown(node->getDown());
if (node->getDown()) node->getDown()->setUp(node->getUp());
if (node == header) {
header = node->getRight() ? node->getRight() : node->getDown();
}
delete node; // Delete the node
}
// Move the player in the specified direction
string movement(string move) {
Node<string>* moveTo = character;
// Move based on direction
if (move == "w") {
moveTo = character->getUp();
if (character->getUp() == NULL) {
moveTo = character->getRight()->getUp();
}
else if (character->getRight()->getUp() == NULL) {
moveTo = character->getLeft()->getUp();
}
}
if (move == "s") {
moveTo = character->getDown();
if (character->getDown() == NULL) {
moveTo = character->getRight()->getDown();
}
else if (character->getRight()->getDown() == NULL) {
moveTo = character->getLeft()->getDown();
}
}
if (move == "a") {
moveTo = character->getLeft();
}
if (move == "d") {
moveTo = character->getRight();
}
current = moveTo;
return current->getData(); // Return the type of node
}
Node<string>* findCharacter() {
Node<string>* row = header;
while (row) {
Node<string>* current = row;
while (current) {
if (current->getData() == "^") {
return current;
}
current = current->getRight();
}
cout << endl;
row = row->getDown();
}
}
void printKey() {
cout << "Delete the nodes to win!" << endl;
cout << "Monster: <" << endl;
cout << "Delete : X" << endl;
cout << "Coins : *" << endl;
cout << endl << "{W,A,S,D} for basic omnidirectonal movement" << endl;
}
};