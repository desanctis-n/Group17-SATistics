#include "Scores.h"

using namespace std;

Scores::Report::Report() =default;
Scores::Scores() {
    generateFromFile();
}

bool Scores::Report::operator==(const Scores::Report &rhs) const {
    return key == rhs.key;
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
        vector<string*> labels(NUMCOLS);
        assignLabels(file, labels);
        for(int i = 0; i < NUMROWS - 1; i++) {
            pair<int, string> key = getKey(file);
            dataSet.emplace(key, new Report);
            dataSet[key]->key = key;
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
void Scores::assignDataMap(std::ifstream &file, const pair<int, string> &key, const vector<std::string*> &labels) {
    string garbage;
    string temp;
    const int NUMCOLS = 99;
    const int NUMGPACOLS = 18;
    const int NUMCLASSMEMBERS = 4;
    for (int j = NUMCLASSMEMBERS + 2; j < NUMCOLS; j++) {
        getline(file, garbage, '\"');
        getline(file, temp, '\"');
        dataSet[key]->criteriaToValue.emplace(*labels[j], stof(temp));
    }
}
void Scores::assignLabels(std::ifstream &file, vector<string*> &labels) const {
    string garbage;
    string temp;
    for (int i = 0; i < 99; i++) {
        getline(file, garbage, '\"');
        getline(file, temp, '\"');
        labels[i] = new string(temp);
    }
}


// ----------------------------- VECTOR MODIFICATION ---------------------------- //


void Scores::push_report(const int &year, const string& stateCode) {
    Report* temp = dataSet[make_pair(year, stateCode)];
    bool inVector = false;
    for (const auto &report : displayVector)
        if (report == temp)
            inVector = true;
    if (!inVector)
        displayVector.push_back(temp);
}
void Scores::pop_report(const int &year, const std::string &stateCode) {
    Report* temp = dataSet[make_pair(year, stateCode)];
    auto iter = displayVector.begin();
    for (; iter != displayVector.end(); ++iter)
        if (*iter == temp)
            displayVector.erase(iter);
}
void Scores::heapSort(const std::string &sortCriteria) {

}
