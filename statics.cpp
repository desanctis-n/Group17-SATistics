#include "Scores.h"

 unordered_map<string, string> Scores::getInitials {{
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
vector<string> Scores::labels{
    {"Year"},
    {"State.Code"},
    {"State.Name"},
    {"Total.Math"},
    {"Total.Test-takers"},
    {"Total.Verbal"},
    {"Academic Subjects.Arts/Music.Average GPA"},
    {"Academic Subjects.Arts/Music.Average Years"},
    {"Academic Subjects.English.Average GPA"},
    {"Academic Subjects.English.Average Years"},
    {"Academic Subjects.Foreign Languages.Average GPA"},
    {"Academic Subjects.Foreign Languages.Average Years"},
    {"Academic Subjects.Mathematics.Average GPA"},
    {"Academic Subjects.Mathematics.Average Years"},
    {"Academic Subjects.Natural Sciences.Average GPA"},
    {"Academic Subjects.Natural Sciences.Average Years"},
    {"Academic Subjects.Social Sciences/History.Average GPA"},
    {"Academic Subjects.Social Sciences/History.Average Years"},
    {"Family Income.Between 20-40k.Math"},
    {"Family Income.Between 20-40k.Test-takers"},
    {"Family Income.Between 20-40k.Verbal"},
    {"Family Income.Between 40-60k.Math"},
    {"Family Income.Between 40-60k.Test-takers"},
    {"Family Income.Between 40-60k.Verbal"},
    {"Family Income.Between 60-80k.Math"},
    {"Family Income.Between 60-80k.Test-takers"},
    {"Family Income.Between 60-80k.Verbal"},
    {"Family Income.Between 80-100k.Math"},
    {"Family Income.Between 80-100k.Test-takers"},
    {"Family Income.Between 80-100k.Verbal"},
    {"Family Income.Less than 20k.Math"},
    {"Family Income.Less than 20k.Test-takers"},
    {"Family Income.Less than 20k.Verbal"},
    {"Family Income.More than 100k.Math"},
    {"Family Income.More than 100k.Test-takers"},
    {"Family Income.More than 100k.Verbal"},
    {"GPA.A minus.Math"},
    {"GPA.A minus.Test-takers"},
    {"GPA.A minus.Verbal"},
    {"GPA.A plus.Math"},
    {"GPA.A plus.Test-takers"},
    {"GPA.A plus.Verbal"},
    {"GPA.A.Math"},
    {"GPA.A.Test-takers"},
    {"GPA.A.Verbal"},
    {"GPA.B.Math"},
    {"GPA.B.Test-takers"},
    {"GPA.B.Verbal"},
    {"GPA.C.Math"},
    {"GPA.C.Test-takers"},
    {"GPA.C.Verbal"},
    {"GPA.D or lower.Math"},
    {"GPA.D or lower.Test-takers"},
    {"GPA.D or lower.Verbal"},
    {"GPA.No response.Math"},
    {"GPA.No response.Test-takers"},
    {"GPA.No response.Verbal"},
    {"Gender.Female.Math"},
    {"Gender.Female.Test-takers"},
    {"Gender.Female.Verbal"},
    {"Gender.Male.Math"},
    {"Gender.Male.Test-takers"},
    {"Gender.Male.Verbal"},
    {"Score Ranges.Between 200 to 300.Math.Females"},
    {"Score Ranges.Between 200 to 300.Math.Males"},
    {"Score Ranges.Between 200 to 300.Math.Total"},
    {"Score Ranges.Between 200 to 300.Verbal.Females"},
    {"Score Ranges.Between 200 to 300.Verbal.Males"},
    {"Score Ranges.Between 200 to 300.Verbal.Total"},
    {"Score Ranges.Between 300 to 400.Math.Females"},
    {"Score Ranges.Between 300 to 400.Math.Males"},
    {"Score Ranges.Between 300 to 400.Math.Total"},
    {"Score Ranges.Between 300 to 400.Verbal.Females"},
    {"Score Ranges.Between 300 to 400.Verbal.Males"},
    {"Score Ranges.Between 300 to 400.Verbal.Total"},
    {"Score Ranges.Between 400 to 500.Math.Females"},
    {"Score Ranges.Between 400 to 500.Math.Males"},
    {"Score Ranges.Between 400 to 500.Math.Total"},
    {"Score Ranges.Between 400 to 500.Verbal.Females"},
    {"Score Ranges.Between 400 to 500.Verbal.Males"},
    {"Score Ranges.Between 400 to 500.Verbal.Total"},
    {"Score Ranges.Between 500 to 600.Math.Females"},
    {"Score Ranges.Between 500 to 600.Math.Males"},
    {"Score Ranges.Between 500 to 600.Math.Total"},
    {"Score Ranges.Between 500 to 600.Verbal.Females"},
    {"Score Ranges.Between 500 to 600.Verbal.Males"},
    {"Score Ranges.Between 500 to 600.Verbal.Total"},
    {"Score Ranges.Between 600 to 700.Math.Females"},
    {"Score Ranges.Between 600 to 700.Math.Males"},
    {"Score Ranges.Between 600 to 700.Math.Total"},
    {"Score Ranges.Between 600 to 700.Verbal.Females"},
    {"Score Ranges.Between 600 to 700.Verbal.Males"},
    {"Score Ranges.Between 600 to 700.Verbal.Total"},
    {"Score Ranges.Between 700 to 800.Math.Females"},
    {"Score Ranges.Between 700 to 800.Math.Males"},
    {"Score Ranges.Between 700 to 800.Math.Total"},
    {"Score Ranges.Between 700 to 800.Verbal.Females"},
    {"Score Ranges.Between 700 to 800.Verbal.Males"},
    {"Score Ranges.Between 700 to 800.Verbal.Total"},
};
