#include "Scores.h"
using namespace std;

int main() {
    Scores data;
//    cout << endl;
//    cout << "Welcome to SATistics!" << endl;
//    cout << endl;
//    data.SATistics();
//    cout << endl;
//    cout << "Thank you for using SATistics!" << endl;
//    cout << "Created by Nicholas DeSanctis, Marvin Howell Aguirre, and Matthew Nobleza" << endl;

    //data.push_report(2005, Scores::getInitials["Alabama"]);
    data.push_report(2006, Scores::getInitials.at("Florida"));
    data.push_report(2006, Scores::getInitials.at("Alaska"));
    data.push_report(2008, Scores::getInitials.at("Florida"));
    //data.push_report(2007, Scores::getInitials.at("Florida"));


//    data.push_report(2006, Scores::getInitials.at("New York"));
//    data.push_report(2006, Scores::getInitials.at("Texas"));
    int x = 6;
    //cout << data.getReport(0).criteriaToValue["Academic Subjects.English.Average GPA"] <<endl;
    cout << Scores::labels[8] << endl;

    data.print(Scores::labels[8]);
    data.heapSort("Academic Subjects.English.Average GPA");
    cout << endl;
    data.print(Scores::labels[8]);
    data.getReport(0);




//    int x = 5;
//
//    data.push_report(2005, "FL");
//    //cout << data.displayVector[0]->stateName << endl;
//    data.push_report(2005, "AK");
//    data.push_report(2005, "NY");
//    data.push_report(2005, "CA");
//    data.push_report(2005, "AL");
//    data.push_report(2005, "FL");
//
//    int z = 5;
//    data.pop_report(2005, "AK");
//    data.pop_report(2007, "NY");
//    data.pop_report(2005, "CA");
//
//    int y = 5;
//
//
//    // Testing search function. User will type in a search bar to find states they want to add.
//    set<string> r = data.searchStates("Alabama");
//    vector<string> names;
//    for (const auto &i : r) {
//        names.push_back(i);
//    }
//    auto name = Scores::getInitials.find("Wyoming");
//    data.push_report(2005, name->second);
//    //data.print();
//
//
//    //data.print();
//    //data.print(0);
//    data.heapSort("Academic Subjects.Social Sciences/History.Average Years");
//
//    data.print();
//    int f = 5;
//    cout << endl;
//
//    data.heapSort("Score Ranges.Between 700 to 800.Verbal.Total");
//    data.print();
//    //cout << data.dataSet[0]->year << endl;
    return 0;
}
