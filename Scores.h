#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <chrono>

using namespace std;

class Scores {
    struct Report {
        pair<int, string> key;
        string stateName;
        int totalMath = 0;
        int totalTestTakers = 0;
        int totalVerbal = 0;
        // backed up by hashtables because we need lookups to be fast. Sorting algorithms will require lookups.
        unordered_map<string, float> criteriaToValue;
        Report();
        bool operator==(const Report &rhs) const;
    };
    map<pair<int, string>, Report*> dataSet;
    static const unordered_map<string, string> getInitials;

    // ------------------------------ FILE IO --------------------------------- //

    void generateFromFile();
    void assignLabels(ifstream &file, vector<string*> &labels) const;
    pair<int, string> getKey(ifstream &file);
    void assignDataMember(ifstream &file, const pair<int, string> &key, const int &switcher);
    void assignDataMap(ifstream &file, const pair<int, string> &key, const vector<string*> &labels);

    // ----------------------- PUBLIC FUNCTIONS AND MEMBERS ------------------------ //
public:
    Scores();
    vector<Report*> displayVector;

    void push_report(const int &year, const string &stateCode);
    void pop_report(const int &year, const string &stateCode);
    void push_all();
    void clear_all();

    set<string> searchStates(const string &searchTerm);

    void heapSort(const string &sortCriteria);
    // return type should not be void since function will return time for operation using chrono
    double quickSort(const string &sortCriteria);
};
