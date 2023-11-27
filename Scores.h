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
        unordered_map<string, int> incomeToScores;
        unordered_map<string, int> gradeToScores;
        unordered_map<string, int> genderToScores;
        unordered_map<string, int> scoreRanges;

        Report();
    };
    void generateFromFile();
public:
    Scores();
    vector<Report*> dataSet;
    // return type is double since function will return time for operation using chrono
    double quickSort(const string &sortCriteria);
    double heapSort(const string &sortCriteria);
};