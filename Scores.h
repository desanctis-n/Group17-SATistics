#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

class Scores {
    struct Report {
        string stateName;
        int totalMath = 0;
        int totalTestTakers = 0;
        int totalVerbal = 0;
        // backed up by hashtables because we need lookups to be fast. Sorting algorithms will require lookups.
        unordered_map<string, float> criteriaToValue;
        Report();
    };
    map<pair<int, string>, Report*> dataSet;

    // ------------------------------ FILE IO --------------------------------- //

    void generateFromFile();
    void assignNames(ifstream &file, array<string*, 99> &labels) const;
    pair<int, string> getKey(ifstream &file);
    void assignDataMember(ifstream &file, const pair<int, string> &key, const int &switcher);
    void assignDataMap(ifstream &file, const pair<int, string> &key, const array<string*, 99> &labels);

    // ----------------------- PUBLIC FUNCTIONS AND MEMBERS ------------------------ //
public:
    Scores();
    vector<Report*> displayVector;

    void modifyDisplayVector(const int &year, const string& stateCode);
    void heapSort(const string &sortCriteria);
    // return type should not be void since function will return time for operation using chrono
    double quickSort(const string &sortCriteria);


};
