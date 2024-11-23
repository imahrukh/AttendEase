#include "AttendanceRecord.h"

// Constructor
AttendanceRecord::AttendanceRecord(int empId) : employeeId(empId) {}

// Add an attendance record
void AttendanceRecord::addAttendance(const std::string& date, float hoursWorked) {
    records.emplace_back(date, hoursWorked);
}

// Get total hours worked
float AttendanceRecord::getTotalHoursWorked() const {
    float total = 0;
    for (const auto& record : records) {
        total += record.getHoursWorked();
    }
    return total;
}

// Get attendance percentage for a given total expected hours
float AttendanceRecord::calculateAttendancePercentage(float totalExpectedHours) const {
    return (getTotalHoursWorked() / totalExpectedHours) * 100;
}

// Display all attendance records
void AttendanceRecord::displayAllAttendance() const {
    std::cout << "Attendance Records for Employee ID: " << employeeId << "\n";
    for (const auto& record : records) {
        record.displayAttendance();
    }
}

// Get records
const std::vector<Attendance>& AttendanceRecord::getRecords() const {
    return records;
}