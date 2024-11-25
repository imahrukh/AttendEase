#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <string>
#include <vector>
#include "Attendance.h"  // Include the Attendance class

class AttendanceRecord {
private:
    int employeeId;
    std::vector<Attendance> records;  // Store attendance entries

public:
    // Constructor
    AttendanceRecord(int empId);

    // Add an attendance record
    void addAttendance(const std::string& date, float hoursWorked);

    // Get total hours worked
    float getTotalHoursWorked() const;

    // Calculate attendance percentage
    float calculateAttendancePercentage(float totalExpectedHours) const;

    // Display all attendance records
    void displayAllAttendance() const;

    // Getter for the attendance records
    const std::vector<Attendance>& getRecords() const;

    // Getter for employee ID
    int getEmployeeId() const;

};

#endif // ATTENDANCERECORD_H
