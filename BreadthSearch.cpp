//Gerishom Muholeza 11/21/2025
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//Breadth First Search Challenge
//Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level)

// Tree node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//Breadth First Search Challenge
//Given the root of a binary tree, return the level order traversal
//(from left to right, level by level)
vector<vector<int>> breadthFirstSearch(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        result.push_back(level);
    }

    return result;
}

// Helper function to print the levels
void printLevels(const vector<vector<int>>& levels) {
    cout << "[";
    for (int i = 0; i < levels.size(); i++) {
        cout << "[";
        for (int j = 0; j < levels[i].size(); j++) {
            cout << levels[i][j];
            if (j + 1 < levels[i].size()) cout << ",";
        }
        cout << "]";
        if (i + 1 < levels.size()) cout << ",";
    }
    cout << "]";
}


void main () {

//Example 1:
//Input: root = [3, 9, 20, null, null, 15, 7]
//Output : [[3], [9, 20], [15, 7]]

    TreeNode* ex1 = new TreeNode(3);
    ex1->left = new TreeNode(9);
    ex1->right = new TreeNode(20);
    ex1->right->left = new TreeNode(15);
    ex1->right->right = new TreeNode(7);

    cout << "Example 1 Output: ";
    printLevels(breadthFirstSearch(ex1));
    cout << endl;

//Example 2 :
//	Input : root = [1]
//	Output : [[1]]

    TreeNode* ex2 = new TreeNode(1);

    cout << "Example 2 Output: ";
    printLevels(breadthFirstSearch(ex2));
    cout << endl;

//	Example 3 :
//	Input : root = []
//	Output : []

    TreeNode* ex3 = nullptr;

    cout << "Example 3 Output: ";
    printLevels(breadthFirstSearch(ex3));
    cout << endl;

}



