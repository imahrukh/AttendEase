#include <iostream>
#include <vector>
#include <string>
#include "AttendanceRecord.cpp"
using namespace std;

class Employee {
    int employeeId;
    string name;
    float totalHoursWorked = 0;
    int casualLeaveBalance = 15;
    int earnedLeaveBalance = 21;
    vector<Attendance> attendanceRecords;

public:
    Employee(int id, string n) : employeeId(id), name(n) {}

    void markAttendance(string date, float hours) {
        attendanceRecords.emplace_back(date, hours);
        totalHoursWorked += hours;
    }

    float calculateAttendancePercentage(int totalWorkingHours) const {
        return (totalHoursWorked / totalWorkingHours) * 100;
    }

    void displayAttendance() const {
        cout << "Attendance for Employee: " << name << "\n";
        for (const auto& record : attendanceRecords) {
            record.displayRecord();
        }
    }

    bool hasSufficientLeave(string leaveType, int days) {
        if (leaveType == "Casual" && days <= casualLeaveBalance) return true;
        if (leaveType == "Earned" && days <= earnedLeaveBalance) return true;
        return false;
    }

    void deductLeave(string leaveType, int days) {
        if (leaveType == "Casual") casualLeaveBalance -= days;
        if (leaveType == "Earned") earnedLeaveBalance -= days;
    }

    void displayLeaveBalances() const {
        cout << "Casual Leave Balance: " << casualLeaveBalance << "\n";
        cout << "Earned Leave Balance: " << earnedLeaveBalance << "\n";
    }
};
