#include "Scores.h"
#include "quickSort.h"

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
void Scores::pop_report(const int &year, const string &stateCode) {
    Report* temp = dataSet[make_pair(year, stateCode)];
    auto iter = displayVector.begin();
    for (; iter != displayVector.end(); ++iter)
        if (*iter == temp)
            displayVector.erase(iter);
}
void Scores::push_all() {
    displayVector.clear();
    for (const auto &report : dataSet)
        displayVector.push_back(report.second);
}
void Scores::clear_all() {
    displayVector.clear();
}


// ----------------------------- PRIVATE MEMBER ACCESS ----------------------------- //


int Scores::getSize() {
    return displayVector.size();
}
const Scores::Report& Scores::getReport(const int &index) {
    return *displayVector[index];
}
void Scores::print() {
    for (const auto& i : displayVector)
        cout << i->key.first << ", " << i->stateName << endl;
}
void Scores::print(const int &index) {
    cout << displayVector[index]->key.first << ", " << displayVector[index]->stateName << endl;
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
    if (results.empty())
        cout << "No states match the criteria. Maybe you forgot to capitalize?" << endl;
    return results;
}
void Scores::heapSort(const string &sortCriteria) {

}
double Scores::quickSort(const string &sortCriteria) {
    // Makes vector of pairs
    // First: original index of Report inside the data set
    // Second: value from criteria that is being sorted
    vector<pair<int, float>> dataVector;
    for (int i = 0; i < getSize(); i++) {
        Report r = getReport(i);
        float value = r.criteriaToValue[sortCriteria];
        dataVector.push_back({i, value});
    }

    // Start timer
    auto start = chrono::high_resolution_clock::now();

    // Calls the actual quick sort function
    quickSorts<pair<int, float>>(dataVector, 0, dataVector.size() - 1, [sortCriteria](const pair<int, float>& a, const pair<int, float>& b) -> bool {
        return a.second < b.second;
    });

    // Stop timer
    auto stop = chrono::high_resolution_clock::now();

    // Counts with start and stop
    // Nanoseconds for more precision
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    // Nanoseconds converted into milliseconds
    return static_cast<double>(duration.count()) * 0.000001;
}


// ----------------------------- STATE NAME -> STATE CODE ---------------------------- //


const unordered_map<string, string> Scores::getInitials {{
  {"Alaska", "AK"},
  {"Alabama", "AL"},
  {"Arkansas", "AR"},
  {"Arizona", "AZ"},
  {"California", "CA"},
  {"Colorado", "CO"},
  {"Connecticut", "CT"},
  {"District Of Columbia", "DC"},
  {"Delaware", "DE"},
  {"Florida", "FL"},
  {"Georgia", "GA"},
  {"Hawaii", "HI"},
  {"Iowa", "IA"},
  {"Idaho", "ID"},
  {"Illinois", "IL"},
  {"Indiana", "IN"},
  {"Kansas", "KS"},
  {"Kentucky", "KY"},
  {"Louisiana", "LA"},
  {"Massachusetts", "MA"},
  {"Maryland", "MD"},
  {"Maine", "ME"},
  {"Michigan", "MI"},
  {"Minnesota", "MN"},
  {"Missouri", "MO"},
  {"Mississippi", "MS"},
  {"Montana", "MT"},
  {"North Carolina", "NC"},
  {"North Dakota", "ND"},
  {"Nebraska", "NE"},
  {"New Hampshire", "NH"},
  {"New Jersey", "NJ"},
  {"New Mexico", "NM"},
  {"Nevada", "NV"},
  {"New York", "NY"},
  {"Ohio", "OH"},
  {"Oklahoma", "OK"},
  {"Oregon", "OR"},
  {"Pennsylvania", "PA"},
  {"Puerto Rico", "PR"},
  {"Rhode Island", "RI"},
  {"South Carolina", "SC"},
  {"South Dakota", "SD"},
  {"Tennessee", "TN"},
  {"Texas", "TX"},
  {"Utah", "UT"},
  {"Virginia", "VA"},
  {"Virgin Islands", "VI"},
  {"Vermont", "VT"},
  {"Washington", "WA"},
  {"Wisconsin", "WI"},
  {"West Virginia", "WV"},
  {"Wyoming", "WY"}}
};
