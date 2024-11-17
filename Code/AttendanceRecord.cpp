#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Attendance {
    string date;
    float hoursWorked;

public:
    Attendance(string d, float h) : date(d), hoursWorked(h) {}

    float getHoursWorked() const {
        return hoursWorked;
    }

    string getDate() const {
        return date;
    }

    void displayRecord() const {
        cout << "Date: " << date << ", Hours Worked: " << hoursWorked << "\n";
    }
};
