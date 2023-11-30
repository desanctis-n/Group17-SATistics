#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

class Scores {
    struct Report {
        int year = 0;
        string stateCode;
        string stateName;

        int totalMath = 0;
        int totalTestTakers = 0;
        int totalVerbal = 0;

        // backed up by hashtables because we need lookups to be fast. Sorting algorithms will require lookups.
        unordered_map<string, float> subjectToAvgGPAs;
        unordered_map<string, int> criteriaToScores;

        Report();
    };
    void assignDataMember(ifstream &file, const int &i, const int &switcher);
    void assignDataMap(ifstream &file, const int &i, const int &switcher, const array<string*, 99> &names);
    static void assignNames(ifstream  &file, array<string*, 99> &names);
    void generateFromFile();
public:
    Scores();
    vector<Report*> dataSet;
    // return type is double since function will return time for operation using chrono
    double quickSort(const string &sortCriteria);
    double heapSort(const string &sortCriteria);
};
