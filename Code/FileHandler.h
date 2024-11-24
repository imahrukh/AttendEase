#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "Employee.h"
#include "Leave.h"

// Class to handle file reading and writing
class FileHandler {
public:
    static void readEmployeeData(std::vector<Employee>& employees);
    static void writeEmployeeData(const Employee& employee);
    static void readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords, int employeeId);
    static void writeAttendanceData(const AttendanceRecord& record);
    static void readLeaveData(std::vector<Leave*>& leaveRecords);
    static void writeLeaveData(const Leave& leave);
    static void updateLeaveStatus(int employeeId, const std::string& leaveType, const std::string& status);
    static void updateAttendanceData(int employeeId, const AttendanceRecord& record);

private:
    static const std::string employeeFile;
    static const std::string attendanceFile;
    static const std::string leaveFile;
};

#endif // FILEHANDLER_H