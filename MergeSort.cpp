#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//struct to hold each row of the csv file
struct Row {
    int value;
    int weight;
    double ratio;
};
void merge(vector<Row>& data, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<Row> Left(n1); //left
    vector<Row> Mid(n2); //middle
    //split left hand side
    for (int i = 0; i < n1; i++) {
        Left[i] = data[p + i];
    }
    for (int j = 0; j < n2; j++) {
        Mid[j] = data[q + 1 + j];
    }
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (Left[i].ratio <= Mid[j].ratio) {
            data[k] = Left[i];
            i++;
        }
        else {
            data[k] = Mid[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        data[k] = Left[i];
        i++;
        k++;
    }
    while (j < n2) {
        data[k] = Mid[j];
        j++;
        k++;
    }
}
void mergeSort(vector<Row>& data, int left, int right) {
    //l = left hand index. Starting out, l=0
    //r = right hand index. Starting out r should be the final index
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}
vector<Row> readCSV(string filename) {
    ifstream file;
    file.open(filename);
    string line;
    vector<Row> data;
    if (!file.is_open()) {
        cout << "Error";
    }
    else {
        while (getline(file, line)) {
            stringstream stream(line);
            string name, value_col, weight_col;
            getline(stream, name, ',');
            getline(stream, value_col, ',');
            getline(stream, weight_col, ',');
            int value = stoi(value_col);
            int weight = stoi(weight_col);
            double ratio = double(value) / double(weight);
            Row newRow = { value, weight, ratio };
            data.push_back(newRow);
        }
        file.close();
    }
    return data;
}
void main() {
    vector<Row> cave;
    cave = readCSV("treasureHunt.csv");
    Row temp, bag = { 0,0,0 };
    int curr_index = cave.size() - 1, weight_limit;
    cout << "What is the bags weight limit? \n";
    cin >> weight_limit;
    //sorts in ascending order based on ratio of value/weight
    mergeSort(cave, 0, cave.size() - 1);
    while (bag.weight < weight_limit and curr_index > -1) {
        //check to see if highest ratio treasure will fit into the bag
        if (bag.weight + cave[curr_index].weight < weight_limit) {
            bag.weight += cave[curr_index].weight;
            bag.value += cave[curr_index].value;
        }
        curr_index--;
    }

    //output results
    cout << "Bag ending weight: " << bag.weight << "\n";
    cout << "Bag ending value: " << bag.value;
}

