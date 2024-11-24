#include "AttendanceRecord.h"
#include "FileHandler.h"
#include <iostream>

int main() {
    // Vector to hold attendance records for multiple employees
    std::vector<AttendanceRecord> attendanceRecords;

    // Read existing attendance data from file
    FileHandler::readAttendanceData(attendanceRecords, 1);

    // Display all attendance records for employees
    std::cout << "Attendance Records:\n";
    for (const auto& record : attendanceRecords) {
        record.displayAllAttendance();
    }

    // Create or update an AttendanceRecord for employee with ID 1
    AttendanceRecord record(1);
    record.addAttendance("2024-11-03", 8);  // Add attendance for employee 1

    // Use FileHandler to write this record to file
    FileHandler::writeAttendanceData(record);

    // Display the employee ID using getter
    std::cout << "\nEmployee ID: " << record.getEmployeeId() << std::endl;

    // Update the employee ID using setter
    record.setEmployeeId(2);  // Update the employee ID to 2
    std::cout << "Updated Employee ID: " << record.getEmployeeId() << std::endl;

    // Add another attendance record for the new employee ID (2)
    record.addAttendance("2024-11-04", 6);  // Add attendance for employee 2
    FileHandler::writeAttendanceData(record);  // Write updated record to file

    // Display updated attendance for employee 2
    record.displayAllAttendance();

    // Get total hours worked for the employee
    std::cout << "Total Hours Worked: " << record.getTotalHoursWorked() << " hours\n";

    // Calculate and display attendance percentage (assuming 40 hours/week for 2 weeks)
    std::cout << "Attendance Percentage: " 
              << record.calculateAttendancePercentage(80) << "%" << std::endl;

    // Update the attendance data (e.g., for employee 1)
    // Update record for employee ID 1 and save it again
    record.addAttendance("2024-11-05", 7); // Add a new attendance entry for employee 1
    FileHandler::updateAttendanceData(record.getEmployeeId(), record); // Update attendance in file

    return 0;
}
