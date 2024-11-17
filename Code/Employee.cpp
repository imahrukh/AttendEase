#include <iostream>
#include <vector>
#include <string>
#include "AttendanceRecord.cpp"
using namespace std;

class Employee {
    int employeeId;
    string name;
    vector<AttendanceRecord> attendanceRecords;

public:
    Employee(int id, string n) : employeeId(id), name(n) {}

    void addAttendance(string date, float hours) {
        attendanceRecords.emplace_back(date, hours);
    }

    void displayAttendance() {
        cout << "Attendance for Employee: " << name << "\n";
        for (auto& record : attendanceRecords) {
            record.displayRecord();
        }
    }
};
