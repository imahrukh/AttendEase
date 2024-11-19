#include "Employee.h"

// Constructor
Employee::Employee(int id, const string& name) : id(id), name(name) {}

// Get employee ID
int Employee::getId() const {
    return id;
}

// Get employee name
string Employee::getName() const {
    return name;
}

// Mark attendance for a specific date
void Employee::markAttendance(const tm& date) {
    attendanceRecords.push_back(date);
}

// Get attendance records
const vector<tm>& Employee::getAttendanceRecords() const {
    return attendanceRecords;
}