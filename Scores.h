#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <chrono>
#include "quickSort.h"

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
    class Heap {
    private:
        int size = 0;
    public:
        vector<Report *> arr;
        Heap();
        vector<Report *> extractMax(Report *&val, string &sortCriteria);
        vector<Report *> insertHeap(Report *val, string &sortCriteria);
        vector<Report *> sortHeap(string &sortCriteria);
    };
    map<pair<int, string>, Report*> dataSet;
    vector<Report*> displayVector;

    // --- MENU --- //
    static void printMenu();
    void switchOpt(int &userOpt);
    void option1_2(bool opt1);
    void option3_4(bool opt3);
    void option5_6(bool opt5);

    // ------------------------------ FILE IO --------------------------------- //

    void generateFromFile();
    pair<int, string> getKey(ifstream &file);
    void assignDataMember(ifstream &file, const pair<int, string> &key, const int &switcher);
    void assignDataMap(ifstream &file, const pair<int, string> &key);

    // ----------------------- PUBLIC FUNCTIONS AND MEMBERS ------------------------ //
public:
    Scores();
    static unordered_map<string, string> getInitials;
    static vector<string> labels;
    void SATistics();

    // ----------------------- VECTOR MODIFICATION ------------------------ //

    void push_report(const int &year, const string &stateCode);
    void pop_report(const int &year, const string &stateCode);
    void push_all();
    void pop_all();

    // ----------------------- PRIVATE MEMBER ACCESS ------------------------ //

    int getSize();
    const Report& getReport(const int &index);
    void print(string& sortCriteria);
    void print(const int &index, string& sortCriteria);

    // ----------------------- SEARCHING AND SORTING ------------------------ //

    set<string> searchStates(const string &searchTerm);
    void heapSort(string sortCriteria);
    // return type should not be void since function will return time for operation using chrono
    double quickSort(const string &sortCriteria);
};
