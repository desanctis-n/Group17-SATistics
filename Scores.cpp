#include "Scores.h"

using namespace std;

Scores::Report::Report() =default;
Scores::Scores() {
    generateFromFile();
}

// ----------------------------- FILE IO ---------------------------- //


void Scores::generateFromFile() {
    chrono::high_resolution_clock time;
    auto start = time.now();
    ifstream file;
    file.open("school_scores.csv");
    if (file.is_open()) {
        const int NUMCOLS = 99;
        const int NUMROWS = 578;
        const int NUMCLASSMEMBERS = 4;
        string garbage;
        string temp;
        array<string*, NUMCOLS> labels;
        assignNames(file, labels);
        for(int i = 0; i < NUMROWS - 1; i++) {
            pair<int, string> key = getKey(file);
            dataSet.emplace(key, new Report);
            for (int j = 0; j < NUMCLASSMEMBERS; j++)
                assignDataMember(file, key, j);
            assignDataMap(file, key, labels);
            getline(file, garbage, '\n');
        }
    }
    else
        throw runtime_error("Could not open file.");
    auto end = time.now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
}
pair<int, string> Scores::getKey(ifstream &file) {
    string garbage;
    string temp;
    getline(file, garbage, '\"');
    getline(file, temp, '\"');
    int year = stoi(temp);
    getline(file, garbage, '\"');
    getline(file, temp, '\"');
    return make_pair(year, temp);
}
void Scores::assignDataMember(ifstream &file, const pair<int, string> &key, const int &switcher) {
    string garbage;
    string temp;
    getline(file, garbage, '\"');
    getline(file, temp, '\"');
    switch (switcher) {
        case 0:
            dataSet[key]->stateName = temp;
            break;
        case 1:
            dataSet[key]->totalMath = stoi(temp);
            break;
        case 2:
            dataSet[key]->totalTestTakers = stoi(temp);
            break;
        case 3:
            dataSet[key]->totalVerbal = stoi(temp);
        default:
            break;
    }
}
void Scores::assignDataMap(std::ifstream &file, const pair<int, string> &key, const array<std::string*, 99> &names) {
    string garbage;
    string temp;
    const int NUMCOLS = 99;
    const int NUMGPACOLS = 18;
    const int NUMCLASSMEMBERS = 4;
    for (int j = NUMCLASSMEMBERS + 2; j < NUMCOLS; j++) {
        getline(file, garbage, '\"');
        getline(file, temp, '\"');
        dataSet[key]->criteriaToValue.emplace(*names[j], stof(temp));
    }
}
void Scores::assignNames(std::ifstream &file, array<string*, 99> &labels) const {
    string garbage;
    string temp;
    for (int i = 0; i < 99; i++) {
        getline(file, garbage, '\"');
        getline(file, temp, '\"');
        labels[i] = new string(temp);
    }
}


// ----------------------------- VECTOR MODIFICATION ---------------------------- //


void Scores::modifyDisplayVector(const int &year, const string& stateCode) {

}
void Scores::heapSort(const std::string &sortCriteria) {

}
