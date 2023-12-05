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
    ifstream file;
    file.open("school_scores.csv");
    if (file.is_open()) {
        const int NUMCOLS = 99;
        const int NUMROWS = 578;
        const int NUMCLASSMEMBERS = 4;
        string garbage;
        string temp;
        getline(file, garbage);
        for(int i = 0; i < NUMROWS - 1; i++) {
            pair<int, string> key = getKey(file);
            dataSet.emplace(key, new Report);
            dataSet[key]->key = key;
            for (int j = 0; j < NUMCLASSMEMBERS; j++)
                assignDataMember(file, key, j);
            assignDataMap(file, key);
            getline(file, garbage, '\n');
        }
    }
    else
        throw runtime_error("Could not open file.");
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
void Scores::assignDataMap(std::ifstream &file, const pair<int, string> &key) {
    string garbage;
    string temp;
    const int NUMCOLS = 99;
    const int NUMGPACOLS = 18;
    const int NUMCLASSMEMBERS = 4;
    for (int j = NUMCLASSMEMBERS + 2; j < NUMCOLS; j++) {
        getline(file, garbage, '\"');
        getline(file, temp, '\"');
        dataSet[key]->criteriaToValue.emplace(labels[j], stof(temp));
    }
}

// ----------------------------- VECTOR MODIFICATION ---------------------------- //


bool Scores::push_report(const int &year, const string& stateCode) {
    bool inVector = false;
    if (dataSet.at(make_pair(year, stateCode)) != nullptr) {
        Report* temp = dataSet.at(make_pair(year, stateCode));
        for (const auto &report: displayVector)
            if (report == temp)
                inVector = true;
        if (!inVector)
            displayVector.push_back(temp);
    }
    return !inVector;
}
bool Scores::pop_report(const int &year, const string &stateCode) {
    if (dataSet.at(make_pair(year, stateCode)) != nullptr) {
        Report *temp = dataSet[make_pair(year, stateCode)];
        auto iter = displayVector.begin();
        for (; iter != displayVector.end(); ++iter)
            if (*iter == temp) {
                displayVector.erase(iter);
                return true;
            }
    }
    return false;
}
void Scores::push_all() {
    displayVector.clear();
    for (const auto &report : dataSet)
        displayVector.push_back(report.second);
}
void Scores::pop_all() {
    displayVector.clear();
}

// ----------------------------- PRIVATE MEMBER ACCESS ----------------------------- //


int Scores::getSize() const {
    return displayVector.size();
}
const map<pair<int, string>, Scores::Report*>& Scores::getDataSet() const {
    return dataSet;
}
const vector<Scores::Report*>& Scores::getDisplayVector() const {
    return displayVector;
}
const Scores::Report& Scores::getReport(const int &index) const {
    return *displayVector[index];
}


// ----------------------------------- DEBUGGING ---------------------------------- //


void Scores::print(const string& sortCriteria) {
    for (int i = 0; i < displayVector.size(); i++) {
        cout << i << ": " << displayVector[i]->key.first;
        cout << ", " << displayVector[i]->stateName;
        cout << ": " << displayVector[i]->criteriaToValue.at(sortCriteria);
        cout << endl;
    }
}
void Scores::print(const int &index, const string &sortCriteria) {
    cout << displayVector[index]->key.first << ", " << displayVector[index]->stateName << ": " << displayVector[index]->criteriaToValue.at(sortCriteria)<< endl;
}

// ----------------------------- SEARCHING AND SORTING ---------------------------- //


set<string> Scores::searchStates(const string &searchTerm) {
    set<string> results;
    for (const auto &rep : dataSet) {
        bool validSearch = true;
        for (int i = 0; i < searchTerm.size(); i++) {
            if (searchTerm[i] != rep.second->stateName[i] || searchTerm.size() > rep.second->stateName.size())
                validSearch = false;
        }
        if (validSearch)
            results.emplace(rep.second->stateName);
    }
    return results;
}
double Scores::quickSort(const string &sortCriteria) {
    auto start = chrono::high_resolution_clock::now();
    vector<Report*> reports;
    for (const auto &rep : displayVector)
        reports.push_back(rep);
    quickSortHelper(reports, 0, reports.size() - 1, sortCriteria);
    displayVector = reports;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    return static_cast<double>(duration.count()) * 0.000001;
}
double Scores::heapSort(string sortCriteria) {
    auto start = chrono::high_resolution_clock::now();
    Heap heap;
    heap.arr = displayVector;
    heap.size = displayVector.size();
    displayVector = heap.sortHeap(sortCriteria);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    return static_cast<double>(duration.count()) * 0.000001;
}
