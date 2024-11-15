#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee {
    int employeeId;
    std::string name;
    std::vector<AttendanceRecord> attendanceRecords;

public:
    Employee(int id, std::string n) : employeeId(id), name(n) {}

    void addAttendance(std::string date, float hours) {
        attendanceRecords.emplace_back(date, hours);
    }

    void displayAttendance() {
        std::cout << "Attendance for Employee: " << name << "\n";
        for (const auto& record : attendanceRecords) {
            record.displayRecord();
        }
    }
};
