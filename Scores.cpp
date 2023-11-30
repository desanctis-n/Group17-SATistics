#include "Scores.h"

using namespace std;

Scores::Report::Report() =default;
Scores::Scores() {
    generateFromFile();
}
void Scores::generateFromFile() {
    chrono::high_resolution_clock time;
    auto start = time.now();
    ifstream file;
    file.open("school_scores.csv");
    if (file.is_open()) {
        const int NUMCOLS = 99;
        const int NUMROWS = 578;
        const int NUMCLASSMEMBERS = 6;
        string garbage;
        string temp;
        static array<string*, NUMCOLS> names;
        assignNames(file, names);
        for(int i = 0; i < NUMROWS - 1; i++) {
            dataSet.emplace(i, new Report);
            for (int j = 0; j < NUMCLASSMEMBERS; j++)
                assignDataMember(file, i, j);
            assignDataMap(file, i, false, names);
            assignDataMap(file, i, true, names);
            getline(file, garbage, '\n');
        }
    }
    else
        throw runtime_error("Could not open file.");
    auto end = time.now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
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
        default:
            break;
    }
}
void Scores::assignDataMap(std::ifstream &file, const int &i, const bool &switcher, const array<std::string*, 99> &names) {
    string garbage;
    string temp;
    const int NUMCOLS = 99;
    const int NUMGPACOLS = 18;
    const int NUMCLASSMEMBERS = 6;
    if (!switcher) {
        for (int j = NUMCLASSMEMBERS; j < NUMGPACOLS; j++) {
            getline(file, garbage, '\"');
            getline(file, temp, '\"');
            dataSet[i]->subjectToAvgGPAs.emplace(*names[j], stof(temp));
        }
    }
    else {
        for (int j = NUMGPACOLS; j < NUMCOLS; j++) {
            getline(file, garbage, '\"');
            getline(file, temp, '\"');
            dataSet[i]->criteriaToScores.emplace(*names[j], stoi(temp));
        }
    }
}
void Scores::assignNames(std::ifstream &file, array<string*, 99> &names) {
    string garbage;
    string temp;
    for (int i = 0; i < names.size(); i++) {
        getline(file, garbage, '\"');
        getline(file, temp, '\"');
        names[i] = new string(temp);
    }
}
void Scores::modifyDisplayVector(const Report &report) {

}
