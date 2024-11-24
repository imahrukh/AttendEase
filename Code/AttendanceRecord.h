#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <vector>
#include "Attendance.h"

class AttendanceRecord {
private:
    int employeeId;
    std::vector<Attendance> records;  // Collection of attendance entries

public:
    // Constructor
    AttendanceRecord(int empId);

     // Getter for employeeId
    int getEmployeeId() const ;

    // Setter for employeeId
    void setEmployeeId(int empId);

    // Add an attendance record
    void addAttendance(const std::string& date, float hoursWorked) ;

    // Get total hours worked
    float getTotalHoursWorked() const ;

    // Get attendance percentage for a given total expected hours
    float calculateAttendancePercentage(float totalExpectedHours) const ;

    // Display all attendance records
    void displayAllAttendance() const;

    // Get records
    const std::vector<Attendance>& getRecords() const ;

    // Setter for records (you can use this to replace the entire attendance records)
    void setRecords(const std::vector<Attendance>& newRecords); 

    // Add an individual attendance entry to the record
    void addAttendance(const Attendance& attendance);
};

#endif // ATTENDANCERECORD_H