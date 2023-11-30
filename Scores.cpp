#include "Scores.h"

using namespace std;

Scores::Report::Report() =default;
Scores::Scores() {
    generateFromFile();
}
void Scores::generateFromFile() {
    ifstream file;
    file.open("school_scores.csv");
    if (file.is_open()) {
        string garbage;
        string temp;
        static array<string*, 99> names;
        assignNames(file, names);
        for(int i = 0; i < 577; i++) {
            dataSet.emplace_back(new Report);
            for (int s = 0; s < 6; s++)
                assignDataMember(file, i, s);
            assignDataMap(file, i, 6, names);
            assignDataMap(file, i, 7, names);
            getline(file, garbage, '\n');
        }
    }
    else
        throw runtime_error("Could not open file.");
}
void Scores::assignDataMember(ifstream &file, const int &i, const int &switcher) {
    string garbage;
    string temp;
    getline(file, garbage, '\"');
    getline(file, temp, '\"');
    switch (switcher) {
        case 0:
            dataSet[i]->year = stoi(temp);
            break;
        case 1:
            dataSet[i]->stateCode = temp;
            break;
        case 2:
            dataSet[i]->stateName = temp;
            break;
        case 3:
            dataSet[i]->totalMath = stoi(temp);
            break;
        case 4:
            dataSet[i]->totalTestTakers = stoi(temp);
            break;
        case 5:
            dataSet[i]->totalVerbal = stoi(temp);
            break;
        default:
            break;
    }
}
void Scores::assignDataMap(std::ifstream &file, const int &i, const int &switcher, const array<std::string*, 99> &names) {
    string garbage;
    string temp;
    switch (switcher) {
        case 6:
            for (int j = 6; j < 18; j++) {
                getline(file, garbage, '\"');
                getline(file, temp, '\"');
                dataSet[i]->subjectToAvgGPAs.emplace(*names[j], stof(temp));
            }
            break;
        case 7:
            for (int j = 18; j < 99; j++) {
                getline(file, garbage, '\"');
                getline(file, temp, '\"');
                dataSet[i]->criteriaToScores.emplace(*names[j], stoi(temp));
            }
            break;
        default:
            break;
    }
}
void Scores::assignNames(std::ifstream &file, array<string*, 99> &names) {
    string garbage;
    string temp;
    for (int i = 0; i < 99; i++) {
        getline(file, garbage, '\"');
        getline(file, temp, '\"');
        names[i] = new string(temp);
    }
}
