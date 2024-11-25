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

const std::string& AttendanceRecord::getDate() const {
    if (!records.empty()) {
        return records.front().getDate();  // Return the date of the first record
    }
    static std::string empty = "";
    return empty;  // Return empty if no records exist
}

float AttendanceRecord::getHoursWorked() const {
    if (!records.empty()) {
        return records.front().getHoursWorked();  // Return the hours worked of the first record
    }
    return 0;  // Return 0 if no records exist
}
