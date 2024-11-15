#include <iostream>
#include <vector>
#include <string>

using namespace std;

class AttendanceRecord {
    string date;
    float hoursWorked;

public:
    AttendanceRecord(string d, float h) : date(d), hoursWorked(h) {}

    void displayRecord() {
        cout << "Date: " << date << ", Hours Worked: " << hoursWorked << "\n";
    }
};