#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <string>

using namespace std;

map<int, vector<string>> fileReader(const string fileName){
    ifstream inputFile;
    inputFile.open(fileName);
    map<int, vector<string>> purchases;

    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << endl;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        int key;
        string item;

        // Read the first integer
        if (!(iss >> key)) {
            cerr << "Error reading integer from line: " << line << endl;
            continue;
        }

        // Read the rest of the line as items
        vector<string> items;
        while (iss >> item) {
            items.push_back(item);
        }

        // Add the items to the map
        purchases[key] = items;
    }
    inputFile.close();
    return purchases;
}

double numberOfPurchases(map<int, vector<string>> purchases){
    double numberOfPurchases = *ranges::max_element(views::keys(purchases));
    return numberOfPurchases;
}

map<string, double> occurrence (map<int, vector<string>> purchases){

    double numberOfPurchase = numberOfPurchases(purchases);
    map<string, double> occurrence;

    for(auto value : views::values(purchases)){
        for (int i = 0; i < value.size(); ++i) {
            occurrence[value.at(i)] = 0;
        }
    }

    for(auto value : views::values(purchases)){
        for (int i = 0; i < value.size(); ++i) {
            occurrence[value.at(i)] ++;
        }
    }

    for(auto& value : views::values(occurrence)){
        value = value / numberOfPurchase;
    }

    return occurrence;
}

int main() {

    map<int, vector<string>> purchases = fileReader("shopping.txt");

    for (const auto& pair : purchases) {
        cout << pair.first << ": ";
        for (const auto& word : pair.second) {
            cout << word << " ";
        }
        cout << endl;
    }
    cout <<endl;

    for(const auto& [key, value] : occurrence(purchases)){
        cout << key << " " << value << endl;
    }

    return 0;
}
