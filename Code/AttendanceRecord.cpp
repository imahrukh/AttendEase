#include "AttendanceRecord.h"
#include "Attendance.h"

AttendanceRecord::AttendanceRecord(int empId) : employeeId(empId) {}

void AttendanceRecord::addAttendance(const std::string& date, float hoursWorked) {
    records.emplace_back(date, hoursWorked);
}

float AttendanceRecord::getTotalHoursWorked() const {
    float total = 0;
    for (const auto& record : records) {
        total += record.getHoursWorked();
    }
    return total;
}

float AttendanceRecord::calculateAttendancePercentage(float totalExpectedHours) const {
    return (getTotalHoursWorked() / totalExpectedHours) * 100;
}

void AttendanceRecord::displayAllAttendance() const {
    std::cout << "Attendance Records for Employee ID: " << employeeId << "\n";
    for (const auto& record : records) {
        record.displayAttendance();
    }
}

const std::vector<Attendance>& AttendanceRecord::getRecords() const {
    return records;
}

int AttendanceRecord::getEmployeeId() const {
    return employeeId;
}


