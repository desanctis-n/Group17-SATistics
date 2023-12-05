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

    // ---------- REPORT --------- //

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

    // ----------- HEAP ---------- //

    class Heap {
        void heapify(vector<Report*>& arr, int n, int i, string& sortCriteria);
    public:
        int size = 0;
        vector<Report *> arr;
        Heap();
        vector<Report *> extractMax(Report *&val, string &sortCriteria);
        vector<Report *> insertHeap(Report *val, string &sortCriteria);
        vector<Report *> sortHeap(string &sortCriteria);
    };


    // --------------- PRIVATE DATA MEMBERS --------------- //

    map<pair<int, string>, Report*> dataSet;
    vector<Report*> displayVector;

    // --------------------- MENU (TERMINAL APPLICATION) ------------------------ //


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
    const static unordered_map<string, string> getInitials;
    const static vector<string> labels;
    void SATistics();

    // ----------------------- VECTOR MODIFICATION ------------------------ //

    bool push_report(const int &year, const string &stateCode);
    bool pop_report(const int &year, const string &stateCode);
    void push_all();
    void pop_all();

    // ----------------------- PRIVATE MEMBER ACCESS ------------------------ //

    int getSize() const;
    const Report& getReport(const int &index) const;
    const map<pair<int, string>, Report*> &getDataSet() const;
    const vector<Report*> &getDisplayVector() const;

    // ----------------------------- DEBUGGING ------------------------------ //

    void print(const string &sortCritera) ;
    void print(const int &index, const string &sortCriteria);

    // ----------------------- SEARCHING AND SORTING ------------------------ //

    set<string> searchStates(const string &searchTerm);
    double heapSort(string sortCriteria);
    double quickSort(const string &sortCriteria);
    // return type should be double since function will return time for operation using chrono
    void quickSortHelper(vector<Report*>& arr, int low, int high, const string &sortCriteria);
    int partition(vector<Report*>& arr, int low, int high, const string &sortCriteria);
};
