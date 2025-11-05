#include <vector>
#include <string>
#include <iostream>
using namespace std;


int subStringFinder(string shortString, string longString) {

    //base case: string is empty
    if (longString.empty() or shortString.empty()) {
        return 0;
    }

    //if the character is found
    else if (longString.find(shortString[0]) != -1) {
        //checks if its the final element in the string 
        //if so clears the string
        if (longString.find(shortString[0]) == longString.size() - 1) {
            longString.clear();
        }
        //if not shrinks the string
        else {
            longString = longString.substr(longString.find(shortString[0]) + 1, longString.size() - 1);
        }
    }

    //checks to see if it's the final element in the string
    //if so clears the string
    if (shortString.size() == 1) {
        shortString.clear();
    }
    //if not shrinks the string
    else {
        shortString = shortString.substr(1, shortString.size() - 1);
    }

    //recalls it's self using new strings and returns current total when done
    return subStringFinder(shortString, longString) + 1;

}



int main() {
    string stringOne, stringTwo, longString, shortString, tempString;
    int max = 0;
    vector<int> subStringLength;


    //Imports strings
    cout << "String 1: ";
    cin >> stringOne;

    cout << "String 2: ";
    cin >> stringTwo;


    //identifies the larger sized string
    if (stringOne.size() > stringTwo.size()) {
        longString = stringOne;
        shortString = stringTwo;
    }
    else {
        longString = stringTwo;
        shortString = stringOne;
    }

    //for each character in shortString subStringFinder is called for each instance except last
    for (int i = 0; i < shortString.size(); i++) {
        tempString = longString;
        while (tempString.find(shortString[i]) != -1) {
            if (tempString.find(shortString[i]) == tempString.size() - 1) {
                subStringLength.push_back(1);
                tempString.clear();
            }
            else {
                tempString = tempString.substr(tempString.find(shortString[i]), tempString.size() - 1);
                subStringLength.push_back(subStringFinder(shortString, tempString));
            }
        }
    }


    //finds max substring length
    for (int i = 0; i < subStringLength.size(); i++) {
        if (max < subStringLength[i]) {
            max = subStringLength[i];
        }
    }
    cout << "Max is : " << max;



}