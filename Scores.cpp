#include "Scores.h"

using namespace std;

Scores::Scores() {
    generateFromFile();
}
void Scores::generateFromFile() {

    ifstream file;
    file.open("src/school_scores.csv");
    if (file.is_open()) {
        // int i = 0;
        // while (!file.eof()) {
        //     dataSet.emplace_back();
        //     string temp;
        //     getline(file, temp, '\"');
        //     dataSet[i]->year = stoi(temp);
        //     getline(file, temp, '\"');
        //     dataSet[i]->stateCode = temp;
        //     getline(file, temp, '\"');
        //     dataSet[i]->stateName = temp;
        //     getline(file, temp, '\"');
        //     dataSet[i]->year = stoi(temp);
        // }
        string temp;
        getline(file, temp);
        dataSet.emplace_back();
        dataSet[0]->stateCode = temp;
        }
    else
        throw runtime_error("Could not open file.");
}